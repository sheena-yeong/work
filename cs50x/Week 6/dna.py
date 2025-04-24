import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument")
        sys.exit(1)

    # TODO: Read database file into a variable
    rows = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
    """
    rows (list of dictionaries)
    [
    {'name': 'Alice', 'AGATC': '2', 'AATG': '8'. 'TATC': '3'},
    {'name': 'Bob', 'AGATC': '4', 'AATG': '1'. 'TATC': '5'},
    ]
    """

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], encoding="utf-8") as f:
        read_data = f.read()

    """
    read_data (list)
    AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATTAAAGGAGATCAGATCAGATCAGATCTATCTATCTATCTATCTATCAGAAAAGAGTAAATAGTTAAAGAGTAAGATATTGAATTAATGGAAAATATTGTTGGGGAAAGGAGGGATAGAAGG
    """

    # TODO: Find longest match of each STR in DNA sequence
    STR_list = reader.fieldnames
    STR_list.remove("name")

    """
    STR_list (list)
    ['AGATC', 'AATG', 'TATC']
    """

    DNA_info = {}  # Create a dictionary to store longest match

    for STR in STR_list:
        DNA_info[STR] = longest_match(read_data, STR)  # Add to dictionary the longest_match

    print(DNA_info)

    """
    DNA_info (dictionary)
    AGATC, AATG, TATC
    Longest Match of AGATC, Longest Match of AATG, Longest Match of TATC
    """

    # TODO: Check database for matching profiles
    # Check for every person, for every STR, if it matches
    for people in rows:
        match = True
        for STR in DNA_info:
            if int(people[STR]) != DNA_info[STR]:
                match = False
                break
        if match == True:
            print(people["name"])
            sys.exit(0)

    print("No Match")

    return


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
