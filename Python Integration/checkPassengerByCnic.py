import sys
import mysql.connector

if len(sys.argv) < 2:
    print("ERROR")
    sys.exit(1)

inp = int(sys.argv[1])

conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="airfaredb"
)

cursor = conn.cursor()

cursor.execute(
    "SELECT id, cnic, name, contact, lastFlight FROM passenger WHERE cnic=%s",
    (inp,)
)

row = cursor.fetchone()

if row:
    print("FIND")
    print(f"ID: {row[0]}")
    print(f"CNIC: {row[1]}")
    print(f"Name: {row[2]}")
    print(f"Contact: {row[3]}")
    print(f"Last Flight: {row[4]}")
else:
    print("NOT_FOUND")

cursor.close()
conn.close()
