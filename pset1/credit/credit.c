#include <stdio.h>
#include <math.h>
#include <cs50.h>

int DigitCount(long n);
int LuhnCheck(long n);


int main(void)
{
    long n = get_long("Card Number: ");
    long i_2_15 = (int)(n / (long int)pow(10, 13));
    long i_2_16 = (int)(n / (long int)pow(10, 14));
    long i_1_16 = (int)(n / (long int)pow(10, 15));
    long i_1_13 = (int)(n / (long int)pow(10, 12));

    if (n < 0 || (DigitCount(n) != 16 && DigitCount(n) != 15 && DigitCount(n) != 13)
        || LuhnCheck(n) == 1)     // Only allows 13, 15 and 16-digit positive numbers that follow Luhn's Algorith
    {
        printf("INVALID\n");
        return 0;
    }
    else if (i_2_15 == 34 || i_2_15 == 37) // CHECK FOR AMEX CARDS
    {
        printf("AMEX\n");
        return 0;
    }
    else if (i_2_16 == 51 || i_2_16 == 52 || i_2_16 == 53 || i_2_16 == 54 || i_2_16 == 55) // CHECK FOR MASTERCARD CARDS
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else if (i_1_13 == 4 || i_1_16 == 4) // CHECK FOR VISA CARDS
    {
        printf("VISA\n");
        return 0;
    }
    else // REJECT ALL OTHER CARDS
    {
        printf("INVALID\n");
    }
    //printf("DigiCount: %i\n", DigitCount(n));
    //printf("Luhn: %i\n", LuhnCheck(n));
}



int DigitCount(long n) // function counts and returns number of digits in number
{
    int m = 0;
    double t = 0;
    while (n / (long int)pow(10, m) >= 10)
    {
        m++;
    }
    return m + 1;
}

int LuhnCheck(long n) // function checks whether number is compliant with Luhn's Algorithm
{
    long os = 0, e2xadigi = 0, p, s;
    for (p = 1; p <= 16; p = p + 2) //calculates the sum of the odd placed digits
    {
        os = os + (n % (long int)pow(10, p)) / ((long int)pow(10, p - 1));
    }

    for (p = 2; p <= 16; p = p + 2) // calculates the sum of the digits of even placed digits
    {
        e2xadigi = e2xadigi + (2 * ((n % (long int)pow(10, p)) / ((long int)pow(10, p - 1)))) % 10 + (int)(2 * ((n % (long int)pow(10
                   , p)) / ((long int)pow(10, p - 1)))) / 10;
    }
    if ((os + e2xadigi) % 10 != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
