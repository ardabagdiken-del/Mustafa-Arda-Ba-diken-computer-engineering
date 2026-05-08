# starter.py — Language Poll Analyser
# Project 1 | Easy | 20–25 minutes

import csv

# ── Step 1: Read the CSV and count languages ──────────────────────────────────
counts = {}

try:
    with open("../../week1/favorites.csv", "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            # TODO: Get the language from the row (Assuming the header is 'language')
            language = row["language"]

            # TODO: Update counts — increment if exists, create if new
            if language in counts:
                counts[language] += 1
            else:
                counts[language] = 1

    # ── Step 2: Sort by popularity (most popular first) ───────────────────────────
    # Hint: sorted(counts, key=counts.get, reverse=True)
    sorted_languages = sorted(counts, key=counts.get, reverse=True)

    # ── Step 3: Print the report ──────────────────────────────────────────────────
    print("=== Language Popularity Report ===")

    # TODO: Loop over sorted_languages with enumerate() to get rank numbers (start=1)
    # Format each line like: "1. Python  : 196 students"
    for rank, language in enumerate(sorted_languages, start=1):
        count = counts[language]
        print(f"{rank}. {language:<10} : {count} students")

    # TODO: Print the total number of responses
    total_responses = sum(counts.values())
    print(f"\nTotal responses: {total_responses}")

except FileNotFoundError:
    print("Error: The file '../../week1/favorites.csv' was not found.")
    print("Please ensure the file path is correct.")
