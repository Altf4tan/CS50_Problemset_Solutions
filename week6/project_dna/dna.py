from csv import DictReader
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py databases/file.csv sequences/file.txt")
        sys.exit(1)

    # Read database file into a variable
    person_list = []
    database_filename = sys.argv[1]
    with open(database_filename) as file:
        reader = DictReader(file)
        for row in reader:
            person_list.append(row)

    # Read DNA sequence file into a variable
    dna_filename = sys.argv[2]
    with open(dna_filename, 'r') as dna_file:
        dna_sequence = dna_file.read().strip()  # .strip() removes any whitespaces

    # Find longest match of each STR in DNA sequence
    with open(database_filename) as f:
        r = DictReader(f)
        # .fieldnames is a list of column names
        headers = r.fieldnames  # e.g. ["name", "AGAT", "AATG", "TATC"]
    subsequences = headers[1:]  # Everything except name ["AGAT", "AATG", "TATC"]
    # Create a dictionary for storing counts
    computed_counts = {}
    # Loop through each STR in your subsequences.
    for subseq in subsequences:
        # Call longest_match to get the max consecutive repeats.
        count = longest_match(dna_sequence, subseq)
        # Store that integer in computed_counts
        computed_counts[subseq] = count

    # Check database for matching profiles
    found_match = False
    for person in person_list:
        is_match = True
        for subseq in subsequences:
            if int(person[subseq]) != computed_counts[subseq]:
                is_match = False
                break
        if is_match:
            print(person["name"])
            found_match = True
            break
    if not found_match:
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
