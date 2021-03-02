/* *************************************
 * Encrypt strings using the Caesar encryption algorithm
 * Usage: ./caesar key
 * (key must be an integer)
 * author: github.com/dst27
 * October 2020
 * *************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Function prototypes
int stringtoint(string input);
string stringCrypt(string input, int key);

// Driver Code
// Needs int arg[1] to be used as encryption key
int main(int argc, string argv[])
{
    // Returns with exit code 1 argument count is not 2 (1 arg)
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Iterate over each character of argv[1] to validate input
    for (int i = 0, c = strlen(argv[1]); i < c; i++)
    {
        // Return with exit code 1 if any char is not a number
        if (!(argv[1][i] <= '9' && argv[1][i] >= '0'))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Get user input
    string rawstring = get_string("plaintext: ");

    // Print encrypted string to stdout
    printf("ciphertext: %s\n", stringCrypt(rawstring, stringtoint(argv[1])));
    return 0;
}

// Encrypts "input" using Caesar's Algorithm with "key" as key
string stringCrypt(string input, int key)
{
    string output = input;
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            output[i] = (((input[i] - 65 + key) % 26) + 65);
        }
        else if (input[i] >= 'a' && input[i] <= 'z')
        {
            output[i] = (((input[i] - 97 + key) % 26) + 97);
        }
    }
    return output;
}

// Convert an array of chars ['0','9'] into an integer
int stringtoint(string input)
{
    int output = 0;
    for (int c = strlen(input), i = c - 1; i >= 0; i--)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            output = output + (((int)input[i] - 48) * (int)pow(10, c - (i + 1)));
        }
        else
        {
            return 1;
        }
    }
    return output;
}