function getCookie(cname) {
    var name = cname + "=";
    var decodedCookie = decodeURIComponent(document.cookie);
    var ca = decodedCookie.split(';');
    for (var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}

function randomHsl() {
    return 'hsla(' + (Math.random() * 360) + ', 100%, 50%, 1)';
}

function getRandomColor() {
    var letters = '0123456789ABCDEF';
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

function setTheme(color) {
    document.querySelector('meta[name="theme-color"]').setAttribute('content', color);
    document.documentElement.style.setProperty('--theme-color', color);
    document.cookie = `theme-color=${color};SameSite=Lax`;
}

function changeTheme() {
    // var randcol = randomHsl();
    var randcol = getRandomColor();
    setTheme(randcol);
}

function toggleDark() {
    if(getCookie('darkEnabled') == 'true') {
        document.cookie = 'darkEnabled=false';
        document.querySelector('body').classList.remove('dark');
    } else {
        document.cookie = 'darkEnabled=true';
        document.querySelector('body').classList.add('dark');
    }
}

if (getCookie('theme-color') != '') {
    setTheme(getCookie('theme-color'));
}

document.addEventListener('DOMContentLoaded', (event) => {
    if (getCookie('darkEnabled') == 'true') {
        document.querySelector('body').classList.add('dark')
    }
})