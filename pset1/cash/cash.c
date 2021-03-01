#include <stdio.h>
#include <math.h>
#include <cs50.h>

int get_cash_input(void);

int main(void)
{
    // Stores dollar input converted to cents rounded to the nearest penny
    int n_round = get_cash_input();
    
    // c_x stores number of coins of value 'x' cents
    int c_25, c_10, c_5, c_1;
    c_1 = n_round;

    c_25 = c_1 / 25, c_1 %= 25;
    c_10 = c_1 / 10, c_1 %= 10;
    c_5 = c_1 / 5, c_1 %= 5;

    // Print the minimum number of coins as computed
    printf("%i\n", c_25 + c_10 + c_5 + c_1);
    return 0;
}

int get_cash_input(void)
{
    // Stores input in pennies
    float n = 0;

    // Keep asking for input until n > 0 is entered
    while (!(n > 0))
    {
        // Input in dollars
        n = get_float("Cash owed: ");

        // Convert to Cents, round to nearest penny
        n = round(n * 100);
    }

    return n;
}