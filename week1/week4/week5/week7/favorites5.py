# favorites5.py
# Task: Count languages using a single dictionary instead of separate variables.

import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)

    counts = {}  # language -> count

    for row in reader:
        favorite = row["language"]
        
        # TODO: If favorite is already in counts, increment counts[favorite] by 1
        if favorite in counts:
            counts[favorite] += 1
        
        # TODO: Otherwise, set counts[favorite] = 1
        else:
            counts[favorite] = 1

    # TODO: Print each key-value pair in counts
    # Format: "Python: 196"
    for language in counts:
        print(f"{language}: {counts[language]}")
