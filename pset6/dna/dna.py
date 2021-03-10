import sys, csv

def main():
    argc = len(sys.argv)
    #if argc != 2:
    #    print("Usage: ./dna.py <db_file> <sequence_file>")
    #    sys.exit(1)


    # Get strs and str consecutive occurence in sequence
    with open(sys.argv[1]) as dbstream:
        csvdb = csv.reader(dbstream)
        header = next(csvdb)
        strs = []
        str_occ = {}
        for i in range(len(header) - 1):
            strs.append(header[i + 1])
            str_occ[header[i + 1]] = str_reps(header[i + 1], sys.argv[2])
        #print(str_occ)

    # Get csv database in a dict for easy access
    with open(sys.argv[1]) as dbstream:
        csvdb = csv.DictReader(dbstream)
        dbl = []
        for row in csvdb:
            dbl.append(row)
        #print(dbl[0])

    str_reps("AGATC", sys.argv[2])

    # Check
    match = False
    for i in range(len(dbl)):
        match_no = 0
        for str_ in strs:
            cp = dbl[i][str_]
            cmpl = str_occ[str_]
            if int(dbl[i][str_]) == str_occ[str_]:
                match_no += 1
        if match_no == len(strs):
            match = True
            print(dbl[i]['name'])

    if match == False:
        print("No match")

# Implementation not complete yet (counts occurences RN, NOT consecutive occurences)
def str_reps(str_seq, seqfile):
    str_len = len(str_seq)
    repcount = 0
    consecutive = 0
    pos = 0
    with open(seqfile, "r") as seqstr:
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