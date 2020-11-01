#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int countLetters(string input);
int countWords(string input);
int countSentences(string input);
int ColemanLiau_I(string text);


int main(void)
{
    string s = get_string("Enter string: ");

    //printf("String has '%i' letters.\n", countLetters(s));        // to debug
    //printf("String has '%i' words.\n", countWords(s));            // to debug
    //printf("String has '%i' sentences.\n", countSentences(s));    // to debug

    int textgrade = ColemanLiau_I(s);
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

int countLetters(string input) // returns the number of letters in input string
{
    int lCount = 0;
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            lCount++;
        }
    }
    return lCount;
}

int countWords(string input) // returns the number of words in input string
{
    int wCount = 0;
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        if (((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) &&
            (input[i + 1] == ' ' || input[i + 1] == ',' || input[i + 1] == '.' || input[i + 1] == '!'
             || input[i + 1] == '?' || input[i + 1] == '\0'))
        {
            wCount++;
        }
    }
    return wCount;
}

int countSentences(string input) // returns the number of sentences in input string
{
    int sCount = 0;
    for (int i = 0, c = strlen(input); i < c; i++)
    {
        if (input[i] == '.' || input[i] == '!' || input[i] == '?') // assumes that ".", "!" and "?" mark the end of a sentence
        {
            sCount++;
        }
    }
    return sCount;
}

int ColemanLiau_I(string text) // calculates the Coleman-Liau Index of input text
{
    double index = 0.0588 * (((float)countLetters(text) / countWords(text)) * 100) - 0.296
                   * (((float)countSentences(text) / countWords(text)) * 100) - 15.8;
    return round(index);
}