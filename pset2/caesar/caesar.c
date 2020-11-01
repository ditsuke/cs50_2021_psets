#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int stringtoint(string input);
string stringCrypt(string input, int key); // returns input encrypted with key using Caesar's Algorithm.


int main(int argc, string argv[]) // needs int arg[0]; used as encryption key
{
    if (argc != 2) // checks if no more than 1 command line argument is present, returns if exit code 1 if false
    {
        printf("Usage: ./caesar key\n");
        return 1;
    } 
    else 
    {
        for (int i = 0, c = strlen(argv[1]); i < c; i++) // iterates over each character of argv[1] to check if argv[1] is an integer.
        {
            if (!(argv[1][i] <= '9' && argv[1][i] >= '0'))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    
    string rawstring = get_string("plaintext: "); // gets user input
    printf("ciphertext: %s\n", stringCrypt(rawstring, stringtoint(argv[1]))); // prints out encrypted string
    return 0;
}

string stringCrypt(string input, int key) // returns input encrypted with key using Caesar's Algorithm (WIP, not working)
{
    string output = input;
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        if (input[i] >= 'A' && input[i]  <= 'Z')
        {
            output[i] = (((input[i] - 65 + key) % 26) + 65);
        }
        else if (input[i] >= 'a' && input[i]  <= 'z')
        {
            output[i] = (((input[i] - 97 + key) % 26) + 97);
        }
    }
    return output;
}

int stringtoint(string input) // converts an array (string) of chars (0,9) into an integer
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