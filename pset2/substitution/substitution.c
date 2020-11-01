// Implements a simple substituition cipher. Usage: ./substitution key
// key must be 26 unique characters long alphabetic.
// author: github.com/dst27
// October 2020


#include <stdio.h>
#include <string.h>
#include <cs50.h>

int hasAlphabeticChars(string sequence);
string flattenSequence(string sequence);
int hasUniqueLetters(string sequence);
string sub_crypt(char *input, string key);


int main(int argc, string argv[])
{
    if (argc != 2) // returns with exit code 1 if number of command line arguments is not 1
    {
        printf("⚠ requires exactly one argument to use as key! ⚠\nUsage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) // returns with exit code 1 if number of chars in argument != 26.
    {
        printf("⚠ key is not 26 characters long!\n");
        return 1;
    }
    else if (hasAlphabeticChars(argv[1]) == 0) // return with exit code 1 if all 26 chars are not alphabetic
    {
        printf("⚠ key has non alphabetic characters!\n");
        return 1;
    }
    else if (hasUniqueLetters(argv[1]) == 0) // return with exit code 1 if all 26 letters in key are not unique
    {
        printf("⚠ key has character duplication!\n");
        return 1;
    }
    
    
    char *plaintext = get_string("plaintext: ");
    printf("ciphertext: %s\n", sub_crypt(plaintext, flattenSequence(argv[1])));

    return 0;
}



int hasAlphabeticChars(string sequence) // returns 1 if each char in sequence is alphabetic, 0 otherwise
{
    for (int i = 0, c = strlen(sequence); i < c; i++)
    {
        if (!((sequence[i] >= 'A' && sequence[i] <= 'Z') || (sequence[i] >= 'a' && sequence[i] <= 'z')))
        {
            return 0;
        }
    }
    return 1;
}

string flattenSequence(string sequence) // returns sequence flattened to uppercase
{
    string flatSequence = sequence; // ⚠ likely needs modifying, currently sequence modified when flatSequence is
    for (int i = 0; i < 26; i++)
    {
        if (sequence[i] >= 'a' && sequence[i] <= 'z')
        {
            flatSequence[i] = sequence[i] - 32;
        }
    }
    return flatSequence;
}


int hasUniqueLetters(string sequence) // returns 1 if each character in sequence is unique, 0 otherwise
{
    char standardSequence[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //get_string("Enter: ");
    for (int i = 0; i < 26; i++)
    {
        if (standardSequence[flattenSequence(sequence)[i] - 65] != '0')
        {
            standardSequence[flattenSequence(sequence)[i] - 65] = '0';
        }
        else // return with code 0 if duplicate letter found
        {
            return 0;
        }
    }
    return 1;
}

string sub_crypt(char *input, string key) // returns input string encrypted with key string using simple substitution
{
    char *output = input;
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