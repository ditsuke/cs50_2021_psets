#include <stdio.h>
#include <math.h>
#include <cs50.h>

float get_cash_input(void);


int main(void)
{
    float n = get_cash_input();
    int nr = (int)n;
    //printf("Pennies owed, rounded = %i\n", nr); //comment out for minimum output
    int a, b, c, d, r;
    a = (int)(nr/25), r = nr%25;
    b = (int)(r/10), r = r%10;
    c = (int)(r/5), r = r%5;
    d = r;
    //printf("Minimum number of coins to pay = %i (%i, %i, %i, %i)\n", a+b+c+d, a, b, c, d); //comment out for mimimum output
    printf("%i\n", a+b+c+d); //outputs only the minumum number and a newline character
    return 0;
}





float get_cash_input(void)
{
    float n = 0;
    while(n<=0)
    {
        n = get_float("Cash owed: "); //dollars
        n = round(n*100); //cents rounded to nearest penny
    }
    return n;
}