#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt for name, store in in_name
    string in_name = get_string("What is your name?");

    // Print to stdout
    printf("hello, %s\n");
    
    // Return with exit code 0
    return 0;
}