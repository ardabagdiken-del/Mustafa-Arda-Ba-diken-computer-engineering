# favorites5_solution.py
# Author: Gemini

import csv

# Open the CSV file for reading
with open("favorites.csv", "r") as file:
    # Use DictReader to access columns by their header names
    reader = csv.DictReader(file)
    
    # Initialize an empty dictionary to store our tallies
    counts = {}

    # Iterate through each row in the CSV
    for row in reader:
        # Access the "language" column specifically
        favorite = row["language"]
        
        # If the language is already in our dictionary, increment its value
        if favorite in counts:
            counts[favorite] += 1
        # If it's the first time we see this language, add it with a value of 1
        else:
            counts[favorite] = 1

# Iterate through the dictionary to print the final results
for favorite in counts:
    print(f"{favorite}: {counts[favorite]}")
