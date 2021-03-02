import re
from sys import exit

def main():
    # Get input
    in_cred = input("Number: ")

    # Store input char count
    seq_l = len(in_cred)

    # Bools for checks on ccn
    notNumeric = re.search("[^0-9]", in_cred) != None
    notValidLength = not seq_l in [13, 15, 16]
    notLuhnValid = luhnCheck(in_cred) == False

    # Exit with code 1 if in_cred fails any test
    if notNumeric or notValidLength or notLuhnValid:
        print("INVALID")
        exit(1)

    # Store card signatures for AMEX, MASTERCARD, VISA
    MC_SIG = [51, 52, 53, 54, 55]
    AMEX_SIG = [34, 37]
    VISA_SIG = [4]

    # Store first first digit and first two digits of ccn
    i1, i2 = int(in_cred[0]), int(in_cred[0] + in_cred[1])

    if i2 in MC_SIG:
        print("MASTERCARD")
    elif i2 in AMEX_SIG:
        print("AMEX")
    elif i1 in VISA_SIG:
        print("VISA")
    else:
        print("INVALID")

def luhnCheck(ccn):
    # Sum of odd placed digits and digits of 2x the even placed digits (from end)
    odd_sum = 0
    evenx2_sumd = 0
    # Store max index of string ccn
    ccn_i = len(ccn) - 1

    i = 0
    while i <= ccn_i:
        if ccn_i - 1 - i >= 0:
            x2_p = 2 * int(ccn[ccn_i - 1 - i])
            evenx2_sumd += x2_p % 10 + int(x2_p / 10)
        if ccn_i - i >= 0:
            odd_sum += int(ccn[ccn_i - i])
        i += 2
    return (evenx2_sumd + odd_sum) % 10 == 0

main()