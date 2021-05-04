import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, extend_portfolio, isPositiveInt, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("IEX Cloud API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_portfolio = db.execute(
        "SELECT * FROM portfolio WHERE username = ?", session["user_name"])
    eportfolio = extend_portfolio(user_portfolio)
    user_portfolio = eportfolio[0]
    totalPortfolioValue = eportfolio[1]
    return render_template("index.html", portfolio=user_portfolio, portVal=totalPortfolioValue)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    elif request.method == "POST":
        buy_stock = request.form.get("symbol").strip().upper()
        buy_count = request.form.get("shares").strip()

        # Basic validation of parameters
        if not buy_stock or not buy_count or not isPositiveInt(buy_count):
            return apology("Invalid stock or count! :/")

        # Render apology if Stock to buy not valid
        stock_quote = lookup(buy_stock)
        if not stock_quote:
            return apology("Invalid stock! :|")
        else:
            stock_price = float(stock_quote["price"])
            buy_count = int(buy_count)
            user_balance = float(db.execute(
                "SELECT * from users where id = ?", session["user_id"])[0]["cash"])

        if user_balance < (stock_price * buy_count):
            return apology("You don't have enough money! 🥺")

        user_balance = user_balance - (stock_price * buy_count)

        # Update database
        db.execute("INSERT INTO transactions (userid, type, stock, units, price, total) VALUES (?, ?, ?, ?, ?, ?);", str(
            session["user_id"]), "buy", buy_stock, str(buy_count), str(stock_price), str(buy_count * stock_price))
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_balance, session["user_id"])
        db.execute(
            f"INSERT INTO portfolio (pid, username, stock, count) VALUES ('{session['user_id']}-{buy_stock}', '{session['user_name']}', '{buy_stock}', '{buy_count}') ON CONFLICT(pid) DO UPDATE SET count = count + '{buy_count}'")

        # Update balance var
        session["user_balance"] = round(db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"], 2)

        # Redirect to portfolio
        flash("Successfully bought %s shares of %s @ $%s per share." %
              (buy_count, buy_stock, stock_price))
        return redirect("/")

    return apology("Unhandled Exception")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_tr_history = db.execute(
        "SELECT * FROM transactions WHERE userid = ?", session["user_id"])
    return render_template("history.html", history=user_tr_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["user_name"] = rows[0]["username"]

        # Set user balance
        session["user_balance"] = round(db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"], 2)

        # Redirect user to home page
        flash("You are logged in!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    flash("Successfully logged out :)")
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    elif request.method == "POST":
        # Process and store form data in vars
        stock_symbol = request.form.get("symbol").strip()
        # Basic validation of form data
        if not stock_symbol:
            return apology("What quote I get? [No symbol input]")
        QUOTE = lookup(stock_symbol)
        if not QUOTE:
            return apology("COULD NOT GET QUOTE. WRONG SYMBOL?")
        return render_template("quoted.html", quote=QUOTE)

    return apology("Unhandled Exception")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    elif request.method == "POST":
        reg_username = request.form.get("username").strip()
        reg_password = request.form.get("password")
        reg_password_conf = request.form.get("confirmation")

        # Validate and check against existing db
        if not reg_username:
            return apology("BLANK USERNAME 🤨")
        elif db.execute("SELECT * FROM users WHERE username = ?", reg_username):
            return apology("USERNAME ALREADY EXISTS 😢")
        elif not reg_password or reg_password != reg_password_conf:
            return apology("PASSWORDS BLANK OR DON'T MATCH 😑")
        else:
            # Update db
            db.execute(
                f"INSERT INTO users (username, hash) VALUES (\"{reg_username}\", \"{generate_password_hash(reg_password)}\")")

            # Redirect to login
            flash("Successfully registered as %s" % (reg_username))
            return redirect("/login")

    return apology("Unhandled Exception")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stock_portfolio = db.execute(
        "SELECT * FROM portfolio WHERE username = ?", session["user_name"])

    if request.method == "GET":
        return render_template("sell.html", stocks=stock_portfolio)

    if request.method == "POST":
        # Process form input and get reference from database
        sell_stock = request.form.get("symbol").strip().upper()
        sell_count = request.form.get("shares").strip()
        stock_entry = next(
            (stock for stock in stock_portfolio if stock["stock"] == sell_stock), False)

        # Validate and process form input further
        if not sell_stock or not sell_count or not isPositiveInt(sell_count):
            return apology("Invalid stock or count :|")
        else:
            sell_count = int(sell_count)

        # Check if stock is in user's portfolio
        if not stock_entry:
            return apology("You don't have stock. Hacker?")
        if not (sell_count <= stock_entry["count"]):
            return apology(f"You don't have {sell_count} shares to sell 🤡")
        sell_stock_price = lookup(sell_stock)["price"]

        # Update database
        db.execute(
            f"INSERT INTO transactions (userid, type, stock, units, price, total) VALUES ('{session['user_id']}', 'sell', '{sell_stock}', '{sell_count}', '{sell_stock_price}', '{sell_count * sell_stock_price}')")
        if (sell_count < stock_entry["count"]):
            db.execute(
                f"UPDATE portfolio SET count = count - {sell_count} WHERE username = '{session['user_name']}' AND stock = '{sell_stock}'")
        else:
            db.execute(
                f"DELETE FROM portfolio WHERE username = '{session['username']}' AND stock = '{sell_stock}'")
        db.execute(
            f"UPDATE users SET cash = cash + {sell_count * sell_stock_price} WHERE username = '{session['user_name']}'")

        # Update user balance var
        session["user_balance"] = round(db.execute(
            "SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"], 2)

        # Redirect to portfolio
        flash("Sold %s shares of %s @ $%s" %
              (sell_count, sell_stock, sell_stock_price))
        return redirect("/")

    return apology("Unhandled Exception")


@app.route("/passchange", methods=["GET", "POST"])
@login_required
def passchange():
    """Implement Password Change"""
    if request.method == "GET":
        return render_template("passchange.html")
    elif request.method == "POST":
        p_og = request.form.get("pass")
        p_new = request.form.get("newpass")
        p_newc = request.form.get("newpassconf")
        old_hash = db.execute(
            "SELECT * FROM users WHERE id = ?", session["user_id"])[0]["hash"]

        if not check_password_hash(old_hash, p_og):
            return apology("Old Password Wrong!")
        elif not p_new == p_newc:
            return apology("New Passwords Do Not Match >|<")
        else:
            # Generate hash and update database
            new_hash = generate_password_hash(p_new)
            db.execute("UPDATE users SET hash = ? WHERE id = ?",
                       new_hash, session["user_id"])
            # Redirect to portfolio
            flash("Successfully changed password! 🙂")
            return redirect("/")

    return apology("Unhandled exception")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
