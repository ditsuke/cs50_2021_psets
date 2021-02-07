#import <stdio.h>
#import <cs50.h>
void stair(int n);
int get_positive_int(void);

int main(void)
{
    int n = get_positive_int();
    stair(n);
    return 0;
}

/* implementing the staircase,  2 nested for () loops, one that does the n rows and the next that takes care of the
   n-m " ", m "#", 2 " ", m "#", and n-m " " in each row */
void stair(int n)
{
    int k, l, m;
    for (m = 0; m < n; m++) // iterates n rows
    {
        for (k = 0; k < n - (m + 1); k++) // this for() loop takes care of the n-m " " each row
        {
            printf(" ");
        }
        for (l = 0; l < m + 1; l++) // this for() loop takes care of the l=m "#" each row
        {
            printf("#");
        }
        printf("  ");
        for (l = 0; l < m + 1; l++) // this for() loop takes care of the l=m "#" each row
        {
            printf("#");
        }
        for (k = 0; k < n - (m + 1); k++) // this for() loop takes care of the n-m " " each row
        {
            printf(" ");
        }
        printf("\n");
    }
}

int get_positive_int(void)
{
    int n = 0;
    while (n < 1)
    {
        n = get_int("Staircase height: ");
    }
    return n;
}