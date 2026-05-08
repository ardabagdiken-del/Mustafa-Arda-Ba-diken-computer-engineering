# Project Challenge 2 — Two-Column Report
# Author: Gemini

import csv

def main():
    filename = "favorites.csv"
    
    # Nested dictionary structure: { Language: { Problem: Count } }
    data = {}

    try:
        with open(filename, mode="r", encoding="utf-8") as file:
            reader = csv.DictReader(file)
            
            for row in reader:
                # Adjust keys 'language' and 'problem' to match your CSV headers
                lang = row.get('language', 'Unknown').strip().title()
                prob = row.get('problem', 'None').strip()

                if lang not in data:
                    data[lang] = {}
                
                if prob in data[lang]:
                    data[lang][prob] += 1
                else:
                    data[lang][prob] = 1

        # Print the Report Table
        print(f"\n{'LANGUAGE':<15} | {'MOST COMMON PROBLEM':<25}")
        print("-" * 45)

        for lang in sorted(data.keys()):
            # Find the problem with the highest count for this specific language
            problems = data[lang]
            most_common_problem = max(problems, key=problems.get)
            
            print(f"{lang:<15} | {most_common_problem:<25}")

    except FileNotFoundError:
        print(f"Error: '{filename}' not found.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == "__main__":
    main()
