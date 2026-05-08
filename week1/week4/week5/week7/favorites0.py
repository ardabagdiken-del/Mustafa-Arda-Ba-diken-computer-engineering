# favorites0.py
# Task: Print every student's favourite language using csv.reader

import csv

# Open favorites.csv for reading
with open("favorites.csv", "r") as file:
    
    # Create a csv.reader object
    # This reads the file row by row as a list of strings
    reader = csv.reader(file)
    
    # Skip the header row using next()
    # This prevents "language" (the title) from being printed as a result
    next(reader)
    
    # Loop over the remaining rows and print the language column
    for row in reader:
        # The language column is at index 1
        print(row[1])
