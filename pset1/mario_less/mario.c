#include <stdio.h>
#include <cs50.h>

// Function Prototypes
void stair(int n);
int get_positive_int(int lower, int upper);

int main(void)
{
    // Get as input a positive int
    int h = get_positive_int(1, 8);

    // Call stair() to print stair of height h
    stair(h);
    return 0;
}

/* **************************************
 * Implementing the staircase using nested for() loops.
 * One does the n rows and the 2 nested ones that take 
 * care of the n-m spaces " " and the m sharps "#" in 
 * each row 
 * *************************************/

void stair(int n)
{
    int k, l, m;

    // Iterates n times
    for (m = 0; m < n; m++)
    {
        // Takes care of the n-m " " on each row
        for (k = 0; k < n - (m + 1); k++)
        {
            printf(" ");
        }

        // Takes care of the l=m "#" each row
        for (l = 0; l < m + 1; l++)
        {
            printf("#");
        }

        // Print a newline to goto next line
        printf("\n");
    }
}

int get_positive_int(int lower, int upper)
{
    int n = 0;

    // Keep asking for input until a 1 <= n <= 8 
    while (n < lower || n > upper)
    {
        n = get_int("Staircase height: ");
    }
    return n;
}