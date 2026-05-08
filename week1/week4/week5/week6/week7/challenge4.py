# Project Challenge 4 — SQL Explorer
# Author: Gemini

import sqlite3

def main():
    db_file = "favorites.db"

    try:
        # Connect to the SQLite database
        connection = sqlite3.connect(db_file)
        # Use Row factory so we can access columns by name
        connection.row_factory = sqlite3.Row
        db = connection.cursor()

        while True:
            print("\n--- SQL Explorer Menu ---")
            print("1. View all languages and their vote counts")
            print("2. Search for problems by specific language")
            print("3. View top 5 most common problems")
            print("4. Exit")
            
            choice = input("\nSelect an option (1-4): ")

            if choice == "1":
                # Aggregate count using SQL
                rows = db.execute("SELECT language, COUNT(*) AS count FROM favorites GROUP BY language ORDER BY count DESC")
                print(f"\n{'Language':<15} | {'Votes':<5}")
                print("-" * 25)
                for row in rows:
                    print(f"{row['language']:<15} | {row['count']:<5}")

            elif choice == "2":
                lang_input = input("Enter language name (e.g., Python): ").strip()
                # Use a placeholder (?) to prevent SQL Injection
                rows = db.execute("SELECT problem, COUNT(*) AS count FROM favorites WHERE language LIKE ? GROUP BY problem ORDER BY count DESC", (lang_input,))
                
                print(f"\nCommon problems in {lang_input.title()}:")
                found = False
                for row in rows:
                    print(f"- {row['problem']} ({row['count']} reports)")
                    found = True
                if not found:
                    print("No data found for that language.")

            elif choice == "3":
                rows = db.execute("SELECT problem, COUNT(*) AS count FROM favorites GROUP BY problem ORDER BY count DESC LIMIT 5")
                print("\nTop 5 Global Problems:")
                for i, row in enumerate(rows, 1):
                    print(f"{i}. {row['problem']} ({row['count']} votes)")

            elif choice == "4":
                print("Closing database connection. Goodbye!")
                break
            else:
                print("Invalid choice, please try again.")

        connection.close()

    except sqlite3.OperationalError:
        print(f"Error: Could not find '{db_file}'. Make sure the database exists.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
