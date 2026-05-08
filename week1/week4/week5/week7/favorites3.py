# favorites3.py
# Task: Print language directly using a one-liner inside the loop.

import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        # TODO: Complete this version (one-liner inside the loop)
        print(row["language"])
