import sys
import mysql.connector

if len(sys.argv) < 2:
    print("ERROR")
    sys.exit(1)

airline_id = int(sys.argv[1])

conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="airfaredb"
)

cursor = conn.cursor()

# Escape reserved keywords rows and columns using backticks
cursor.execute(
    "SELECT title, country, code FROM airline WHERE id=%s",
    (airline_id,)
)

row = cursor.fetchone()

if row:
    print(f"TITLE={row[0]}")
    print(f"COUNTRY={row[1]}")
    print(f"CODE={row[2]}")

cursor.close()
conn.close()