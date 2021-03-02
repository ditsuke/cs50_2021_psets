import re


def main():
    # Get and store input
    intext = input("Text: ")

    # Store Coleman-Liau Index rounded to nearest int
    grade = round(ColemanLiau_I(intext))

    # Print text grade as per spec
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade " + str(grade))


def ColemanLiau_I(text):
    wor = len(text.split(" "))                  # Number of words
    sen = len(re.split("\.|\?|!", text)) - 1    # Number of sentences
    let = len(re.findall("[A-Za-z]", text))     # Number of letters

    # Compute index using the Coleman-Liau formula
    index = 0.0588 * let * 100 / wor - 0.296 * sen * 100 / wor - 15.8
    return index


main()