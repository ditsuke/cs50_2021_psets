#include <stdio.h>
#include <cs50.h>

// Function prototypes
void stair(int n);
int get_int_in_range(int lower, int upper);

int main(void)
{
    int n = get_int_in_range(1, 8);
    stair(n);
    return 0;
}

/* *************************************
 * Implementing the staircase using nested for() loops.
 * One does the n rows and 3 nested ones that take care
 * of the n-m spaces " ", m sharps "#", 2 spaces "  "
 * and another m Sharps "#" on each row
 * *************************************/

void stair(int n)
{
    int k, l, m;

    // Iterate n times
    for (m = 0; m < n; m++)
    {
        // Print n-m spaces " " on each row
        for (k = 0; k < n - (m + 1); k++)
        {
            printf(" ");
        }

        // Print l=m sharps "#" on each row
        for (l = 0; l < m + 1; l++)
        {
            printf("#");
        }

        // Two spaces between left and right staircases
        printf("  ");

        // Print l=m sharps "#" on each row
        for (l = 0; l < m + 1; l++)
        {
            printf("#");
        }

        // Move cursor to next line
        printf("\n");
    }
}

int get_int_in_range(int lower, int upper)
{
    int n = 0;

    // Keep asking for input until a 1 <= n <= 8
    while (n < lower || n > upper)
    {
        n = get_int("Staircase height: ");
    }
    return n;
}