# favorites0_solution.py
# Author: Gemini

import csv

# Open the CSV file for reading
with open("favorites.csv", "r") as file:
    # Create a reader object to iterate over the lines
    reader = csv.reader(file)
    
    # Skip the header row (the first line)
    next(reader)
    
    # Loop through each row in the CSV
    for row in reader:
        # Print the data from the second column (index 1)
        # In many datasets, index 0 is a timestamp and index 1 is the language/title
        print(row[1])
