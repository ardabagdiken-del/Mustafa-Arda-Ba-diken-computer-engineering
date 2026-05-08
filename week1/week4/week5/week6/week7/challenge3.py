# Project Challenge 3 — CSV Writer
# Author: Gemini

import csv

def main():
    input_file = "favorites.csv"
    output_file = "language_summary.csv"
    
    counts = {}

    try:
        # 1. Read from the favorites.csv file
        with open(input_file, mode="r", encoding="utf-8") as file:
            reader = csv.DictReader(file)
            for row in reader:
                # Adjust 'language' to match your specific CSV header
                lang = row.get('language', 'Unknown').strip().title()
                
                if lang:
                    counts[lang] = counts.get(lang, 0) + 1

        # 2. Sort the data by vote count (highest to lowest)
        sorted_data = sorted(counts.items(), key=lambda x: x[1], reverse=True)

        # 3. Write the results to language_summary.csv
        with open(output_file, mode="w", encoding="utf-8", newline="") as file:
            writer = csv.writer(file)
            
            # Write the header row
            writer.writerow(["Language", "Votes"])
            
            # Write the data rows
            for lang, votes in sorted_data:
                writer.writerow([lang, votes])

        print(f"Success! Summary written to '{output_file}'.")
        
        # Optional: Print a preview to the console
        print("\n--- Preview of Results ---")
        for lang, votes in sorted_data:
            print(f"{lang}: {votes}")

    except FileNotFoundError:
        print(f"Error: '{input_file}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
