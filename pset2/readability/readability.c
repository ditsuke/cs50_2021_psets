/* *************************************
 * A Program to calculate the Coleman-Liau Index of a given text.
 * Usage: ./readability
 * author: github.com/dst27
 * October 2020
 * *************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Function prototypes
int countLetters(string input);
int countWords(string input);
int countSentences(string input);
int ColemanLiau_I(string text);

int main(void)
{
    // Stores input string
    string s = get_string("Enter string: ");

    // Stores grade of text as given by the Coleman-Liau formula.
    int textgrade = ColemanLiau_I(s);

    // Print text grade to stdout as per problem spec
    if (textgrade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (textgrade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", textgrade);
    }
    return 0;
}

// Counts the number of letters in input string
int countLetters(string input)
{
    // Stores number of letters found
    int lCount = 0;

    // Iterate over input string
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        // Increment lcount for each Latin Alphabet found
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            lCount++;
        }
    }
    // Return computed letter count
    return lCount;
}

// Counts the number of words in input string
int countWords(string input)
{
    // Stores number of words found
    int wCount = 0;

    // Iterate over string
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        // Increment wCount for each Latin alphabet encountered that precedes a space,
        // a comma, or a period.
        if (((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) &&
            (input[i + 1] == ' ' || input[i + 1] == ',' || input[i + 1] == '.' || input[i + 1] == '!' || input[i + 1] == '?'
             || input[i + 1] == '\0'))
        {
            wCount++;
        }
    }
    // Return computed word count
    return wCount;
}

// Counts the number sentences in string input
int countSentences(string input)
{
    // Stores sentence count
    int sCount = 0;

    // Iterate over string
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        // Increment sCount for each period, exclamation and question symbol encountered
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            sCount++;
        }
    }
    // Return computed sentence count
    return sCount;
}

// Calculate the Coleman-Liau Index of input text
int ColemanLiau_I(string text)
{
    double index = 0.0588 * (((float)countLetters(text) / countWords(text)) * 100) - 0.296 * (((float)countSentences(text) / 
                   countWords(text)) * 100) - 15.8;

    // Return computed index rounded to nearest int
    return round(index);
}