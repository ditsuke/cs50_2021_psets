#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef int64_t longint;

int DigitCount(longint n);
bool LuhnCheck(longint n);

int main(void)
{
    // Input card number
    longint n;

    printf("Card Number: ");
    scanf("%lld", &n);

    // Digit count for n
    int dc = DigitCount(n);
    // First 2 digits of 15 digit number
    int i_2 = (n / (longint)pow(10, dc - 2));
    // First 2 digits of 16 digit number
    int i_1 = (longint)(n / (longint)pow(10, dc - 1));

    // Only allow 13, 15 and 16-digit positive numbers
    if (!(n > 0 && (dc == 16 || dc == 15 || dc == 13)))
    {
        printf("INVALID\n");
        return 0;
    }
    bool lc = LuhnCheck(n);
    // Only allow Luhn compliant numbers
    if (lc == false)
    {
        printf("INVALID\n");
        return 0;
    }
    // CHECK FOR AMEX CARDS
    else if (i_2 == 34 || i_2 == 37)
    {
        printf("AMEX\n");
        return 0;
    }
    // CHECK FOR MASTERCARD CARDS
    else if (i_2 == 51 || i_2 == 52 || i_2 == 53 || i_2 == 54 || i_2 == 55)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    // CHECK FOR VISA CARDS
    else if (i_1 == 4)
    {
        printf("VISA\n");
        return 0;
    }
    // REJECT ALL OTHER CARDS
    else
    {
        printf("INVALID\n");
    }
}

// Returns number of digits in longint n
int DigitCount(longint n)
{
    // Digit count
    int m = 0;

    // Increment m until n / 10^m < 10
    while (n / (longint)pow(10, m) >= 1)
    {
        m++;
    }
    return m;
}

// Checks for compliance of Luhn's Algorithm
bool LuhnCheck(longint n)
{
    int odd_sum = 0, evenx2_sum = 0;
    int dc = DigitCount(n);

    // Sum of the odd placed digits (from end)
    for (longint p = 1, m = n; p <= 16; p = p + 2)
    {
        odd_sum += (n % (longint)pow(10, p)) / ((longint)pow(10, p - 1));
    }

    // Sum of digits of 2x the even placed digits (from end)
    for (int p = 2; p <= 16; p = p + 2)
    {
        evenx2_sum +=
            (2 * ((n % (longint)pow(10, p)) / ((longint)pow(10, p - 1)))) % 10 +
            (int)(2 * ((n % (longint)pow(10, p)) / ((longint)pow(10, p - 1)))) /
            10;
    }
    // Return true if odd_sum + evenx2_sum end with 0 (% 10 == 0)
    if ((odd_sum + evenx2_sum) % 10 == 0)
    {
        return true;
    }
    // Return false otherwise
    else
    {
        return false;
    }
}
