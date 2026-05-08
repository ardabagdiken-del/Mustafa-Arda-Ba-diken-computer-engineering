#!/bin/bash
# setup.sh — Initialize all practice databases for Week 8 SQL exercises
# Usage: bash setup.sh

# 'set -e' makes the script stop immediately if any command fails
set -e

echo "🗄️  Week 8 SQL — Database Setup"
echo "================================"

# 1. Check if sqlite3 is installed on the system
if ! command -v sqlite3 &>/dev/null; then
    echo "❌ sqlite3 not found."
    echo "   Please install it to continue:"
    echo "   • Ubuntu/Debian: sudo apt install sqlite3"
    echo "   • macOS:         brew install sqlite"
    echo "   • Windows:       https://www.sqlite.org/download.html"
    exit 1
fi

echo "✅ sqlite3 found: $(sqlite3 --version)"

# 2. Prepare the data directory
mkdir -p data

# 3. Remove old databases if they exist to ensure a fresh start
rm -f data/school.db data/library.db

# 4. Build the databases using the .sql source files
echo ""
echo "📦 Creating school.db..."
# This command pipes the SQL instructions into the sqlite3 engine
sqlite3 data/school.db < data/school.sql
echo "   ✅ school.db created"
echo "      Tables found: $(sqlite3 data/school.db '.tables')"

echo ""
echo "📦 Creating library.db..."
sqlite3 data/library.db < data/library.sql
echo "   ✅ library.db created"
echo "      Tables found: $(sqlite3 data/library.db '.tables')"

# 5. Final output and helpful instructions
echo ""
echo "🎉 Setup complete! You're ready to start."
echo ""
echo "Quick start guide:"
echo "  sqlite3 data/school.db"
echo "  sqlite> .headers on"
echo "  sqlite> .mode column"
echo "  sqlite> SELECT * FROM students LIMIT 5;"
echo ""
echo "Learning Path:"
echo "  01-basics      → exercises/01-basics/"
echo "  02-queries     → exercises/02-queries/"
echo "  03-joins       → exercises/03-joins/"
echo "  04-aggregates  → exercises/04-aggregates/"
echo "  05-subqueries  → exercises/05-subqueries/"
echo "  06-design      → exercises/06-design/"
echo "  07-advanced    → exercises/07-advanced/"
echo ""
echo "Happy coding! 🚀"
