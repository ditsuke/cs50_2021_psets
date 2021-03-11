import sys, csv

def main():
    argc = len(sys.argv)

    # Return with code 1 if incorrect usage/arg count
    if argc != 3:
        print("Usage: ./dna.py <db_file> <sequence_file>")
        sys.exit(1)


    # Get strs and str consecutive occurence in sequence
    with open(sys.argv[1]) as dbstream:
        csvdb = csv.reader(dbstream)
        header = next(csvdb)
        strs = []
        str_occ = {}
        for i in range(len(header) - 1):
            strs.append(header[i + 1])
            str_occ[header[i + 1]] = str_reps(header[i + 1], sys.argv[2])

    # Get csv database as a list of dicts ("person"s)
    with open(sys.argv[1]) as dbstream:
        csvdb = csv.DictReader(dbstream)
        people = []
        for row in csvdb:
            people.append(row)

    # Check for matches of sequence STRs for each person in people
    for person in people:
        match_no = 0
        for str_ in strs:
            if int(person[str_]) == str_occ[str_]:
                match_no += 1
        if match_no == len(strs):
            print(person['name'])
            sys.exit(0)

        print("No match")

# Max consecutive occurrence of a STR
def str_reps(str_seq, seqfile):
    str_len = len(str_seq)
    repcount = 0
    consecutive = 0
    pos = 0

    with open(seqfile) as seqstr:
        buff = seqstr.read()
    i = 0
    while i < len(buff):
        cc = buff[i]
        i += 1
        if cc == str_seq[pos]:
           pos += 1
           if pos == str_len:
               repcount += 1
               if repcount > consecutive:
                   consecutive = repcount
               pos = 0
        else:
            i = i - pos
            pos = 0
            repcount = 0

    return consecutive

main()