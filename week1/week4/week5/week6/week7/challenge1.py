# Project Challenge 1 — Frequency Filter
# Author: Gemini

import csv

def main():
    filename = "favorites.csv"
    
    try:
        # 1. Ask the user for the minimum threshold
        min_votes = int(input("Enter minimum vote threshold to display: "))
        
        counts = {}

        # 2. Open and read the CSV file
        # Assuming the CSV has a header and the 'favorite' is in the first column
        with open(filename, mode="r", encoding="utf-8") as file:
            reader = csv.DictReader(file)
            
            for row in reader:
                # We assume the column name is 'item' or 'title' 
                # Adjust 'title' to match your specific CSV header
                item = row.get('title') or row.get('item') or list(row.values())[0]
                
                if item:
                    item = item.strip().title() # Clean up the text
                    if item in counts:
                        counts[item] += 1
                    else:
                        counts[item] = 1

        # 3. Filter and print results
        print(f"\n--- Items with at least {min_votes} votes ---")
        found = False
        
        # Sorting by count (descending) for a better UI
        sorted_counts = sorted(counts.items(), key=lambda x: x[1], reverse=True)

        for item, count in sorted_counts:
            if count >= min_votes:
                print(f"{item}: {count} votes")
                found = True
        
        if not found:
            print("No items met that threshold.")

    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found. Please ensure it exists in this folder.")
    except ValueError:
        print("Error: Please enter a valid whole number for the vote count.")

if __name__ == "__main__":
    main()
