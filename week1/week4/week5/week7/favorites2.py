# favorites2.py
# Task: Print every language using csv.DictReader instead of csv.reader

import csv

with open("favorites.csv", "r") as file:
    # TODO: Create a csv.DictReader (not csv.reader)
    # This treats each row as an ordered dictionary
    reader = csv.DictReader(file)
    
    # TODO: Loop over rows and print row["language"]
    # Note: We don't need next(reader) because DictReader handles the header for us!
    for row in reader:
        print(row["language"])
