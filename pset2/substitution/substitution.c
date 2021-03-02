/* *************************************
 * Implements a simple substituition cipher. 
 * Usage: ./substitution key
 * (Key must be 26 unique characters long alphabetic).
 * author: github.com/dst27
 * October 2020
 * *************************************/

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdbool.h>

// Function prototypes
int hasAlphabeticChars(string sequence);
int hasUniqueLetters(string sequence);
string flattenSequence(string sequence);
string sub_crypt(char *input, string key);


int main(int argc, string argv[])
{
    // returns with exit code 1 if arg_count != 2
    if (argc != 2)
    {
        printf("⚠ requires exactly one argument to use as key! ⚠\nUsage: ./substitution key\n");
        return 1;
    }
    // returns with exit code 1 if argument doesn't have 26 chars
    else if (strlen(argv[1]) != 26)
    {
        printf("⚠ key is not 26 characters long!\n");
        return 1;
    }
    // returns with exit code 1 if argument isn't purely alphabetic
    else if (hasAlphabeticChars(argv[1]) == 0)
    {
        printf("⚠ key has non alphabetic characters!\n");
        return 1;
    }
    // returns with exit code 1 if argument has any duplicate alphabet
    else if (hasUniqueLetters(argv[1]) == 0)
    {
        printf("⚠ key has character duplication!\n");
        return 1;
    }

    // Stores input string
    string plaintext = get_string("plaintext: ");

    // Print encrypted string to stdout
    printf("ciphertext: %s\n", sub_crypt(plaintext, flattenSequence(argv[1])));
    return 0;
}


// Returns true if sequence is purely alphabetic
int hasAlphabeticChars(string sequence)
{
    for (int i = 0, c = strlen(sequence); i < c; i++)
    {
        if (!((sequence[i] >= 'A' && sequence[i] <= 'Z') || (sequence[i] >= 'a' && sequence[i] <= 'z')))
        {
            return false;
        }
    }
    return true;
}

// "Flattens" sequence to uppercase
string flattenSequence(string sequence)
{
    string flatSequence = sequence;
    for (int i = 0; i < 26; i++)
    {
        if (sequence[i] >= 'a' && sequence[i] <= 'z')
        {
            flatSequence[i] = sequence[i] - 32;
        }
    }
    return flatSequence;
}

// Returns true if each character in sequence is unique
int hasUniqueLetters(string sequence)
{
    // Stores standard latin alphabet A-Z
    char standardSequence[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0, c = strlen(sequence); i < c; i++)
    {
        if (standardSequence[flattenSequence(sequence)[i] - 65] != '0')
        {
            standardSequence[flattenSequence(sequence)[i] - 65] = '0';
        }
        // Return false if duplicate letter found
        else
        {
            return false;
        }
    }
    // Return true if all alphabets were unique
    return true;
}

// Encrypts string input with string key using simple substitution
string sub_crypt(string input, string key)
{
    string output = input;
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            output[i] = key[input[i] - 65];
        }
        else if (input[i] >= 'a' && input[i] <= 'z')
        {
            output[i] = key[input[i] - 97] + 32;
        }
        else
        {
            output[i] = input[i];
        }
    }
    return output;
}