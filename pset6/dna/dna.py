import sys
import csv


def main():
    argc = len(sys.argv)

    # Check for incorrect usage
    if argc != 3:
        print("Usage: ./dna.py <db_file> <sequence_file>")
        sys.exit(1)
    else:
        db_file = sys.argv[1]
        sequence_file = sys.argv[2]

    # Get STRs and their consecutive occurences in sequence
    with open(db_file) as db_stream:
        db_csv = csv.reader(db_stream)
        STRs = next(db_csv)[1::]
        str_occurence = {}
        for i in range(len(STRs)):
            str_occurence[STRs[i]] = str_repetitions(STRs[i], sequence_file)


    # Get CSV database as a list of people
    with open(db_file) as db_stream:
        db_csv_dict = csv.DictReader(db_stream)
        people = []
        for row in db_csv_dict:
            people.append(row)

    # Check for matches of sequence STRs for each person in people
    for person in people:
        str_matches = 0
        for str_ in STRs:
            if int(person[str_]) == str_occurence[str_]:
                str_matches += 1
        if str_matches == len(STRs):
            print(person['name'])
            sys.exit(0)

    print("No match")


# Return the number of consecutive occurences of the STR (str_seq) in the Sequence file (seq_file)
def str_repetitions(str_sequence, sequence_file):
    str_length = len(str_sequence)
    repetitions = 0
    consecutive_matches = 0
    pos = 0

    # Read sequence_file into a buffer string
    with open(sequence_file) as sequence_stream:
        buffer = sequence_stream.read()
        buffer_len = len(buffer)

    i = 0
    while i < buffer_len:
        cc = buffer[i]
        i += 1
        if cc == str_sequence[pos]:
            pos += 1
            if pos == str_length:
                repetitions += 1
                if repetitions > consecutive_matches:
                    consecutive_matches = repetitions
                pos = 0
        else:
            i = i - pos
            pos = 0
            repetitions = 0

    return consecutive_matches


main()
