# Project Challenge 5 — Data Cleaner
# Author: Gemini

import csv

def main():
    input_file = "messy_data.csv"
    output_file = "cleaned_data.csv"
    
    # Tracking statistics for the final report
    stats = {
        "total_rows": 0,
        "cleaned_rows": 0,
        "removed_rows": 0,
        "fixed_formatting": 0
    }

    cleaned_data = []

    try:
        with open(input_file, mode="r", encoding="utf-8") as file:
            reader = csv.DictReader(file)
            
            for row in reader:
                stats["total_rows"] += 1
                
                # 1. Check for missing values (NULL or empty)
                if not row['name'] or row['name'].upper() == "NULL" or not row['language']:
                    stats["removed_rows"] += 1
                    continue
                
                # 2. Clean text formatting (Strip whitespace and title case)
                original_name = row['name']
                row['name'] = row['name'].strip().title()
                row['language'] = row['language'].strip().title()
                
                if original_name != row['name']:
                    stats["fixed_formatting"] += 1

                # 3. Validate Score (Must be a number)
                try:
                    row['score'] = float(row['score'])
                except (ValueError, TypeError):
                    row['score'] = 0.0  # Default score for invalid data
                
                cleaned_data.append(row)
                stats["cleaned_rows"] += 1

        # Write the cleaned data to a new file
        if cleaned_data:
            with open(output_file, mode="w", encoding="utf-8", newline="") as file:
                writer = csv.DictWriter(file, fieldnames=["name", "language", "score"])
                writer.writeheader()
                writer.writerows(cleaned_data)

        # Print the Cleaning Report
        print("\n--- Data Cleaning Report ---")
        print(f"Total rows processed: {stats['total_rows']}")
        print(f"Rows successfully cleaned: {stats['cleaned_rows']}")
        print(f"Rows removed (missing data): {stats['removed_rows']}")
        print(f"Formatting issues fixed: {stats['fixed_formatting']}")
        print(f"\nCleaned data saved to: {output_file}")

    except FileNotFoundError:
        print(f"Error: '{input_file}' not found. Please create it first!")

if __name__ == "__main__":
    main()
