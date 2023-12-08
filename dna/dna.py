import csv
from sys import argv


def main():
    # TODO: Check for command-line usage
    while True:
        k = len(argv)
        if len(argv) == 3:
            break
        else:
            print("fuck you")
            return
            break

    datafile = argv[1]
    sequencefile = argv[2]

    # TODO: Read database file into a variable
    data_file = open(datafile, "r")
    reader = csv.reader(data_file)
    database = []
    for row in reader:
        database.append(row)

    readerasdict = csv.DictReader(open(datafile, "r"))
    dictdatabase = []

    for row in readerasdict:
        dictdatabase.append(row)

    # TODO: Read DNA sequence file into a variable
    seq_file = open(sequencefile, "r")
    sequence = seq_file.read()

    # getting the list of str included in the given database
    strlst = database[0]
    strlst.pop(0)
    # print(strlst)

    # TODO: Find longest match of each STR in DNA sequence
    ddt = dict()
    for str in strlst:
        longest_run = longest_match(sequence, str)
        ddt[str] = longest_run

    # print(ddt)
    # TODO: Check database for matching profiles
    true_count = 0
    match = False
    for person in dictdatabase:
        true_count = 0
        for str in strlst:
            if int(person[str]) == ddt[str]:
                true_count += 1
        if true_count == len(strlst):
            print(person["name"])
            match = True
            break
    if match == False:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
