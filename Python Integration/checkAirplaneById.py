import sys
import mysql.connector

if len(sys.argv) < 2:
    print("ERROR")
    sys.exit(1)

airplane_id = int(sys.argv[1])

conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="airfaredb"
)

cursor = conn.cursor()

# Escape reserved keywords rows and columns using backticks
cursor.execute(
    "SELECT airlineID, model, totalRows, totalColumns FROM airplane WHERE id=%s",
    (airplane_id,)
)

row = cursor.fetchone()

if row:
    print(f"AIRLINE_ID={row[0]}")
    print(f"MODEL={row[1]}")
    print(f"ROWS={row[2]}")
    print(f"COLUMNS={row[3]}")

cursor.close()
conn.close()
