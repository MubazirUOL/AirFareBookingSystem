import sys
import mysql.connector

if len(sys.argv) < 2:
    print("ERROR")
    sys.exit(1)

ticketID = int(sys.argv[1])

conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="airfaredb"
)

cursor = conn.cursor()

# Escape reserved keywords rows and columns using backticks
cursor.execute(
    "SELECT id, flightID, passengerID, seatNo FROM ticket WHERE id=%s",
    (ticketID,)
)

row = cursor.fetchone()

if row:
    print(f"TICKET_ID={row[0]}")
    print(f"FLIGHT_ID={row[1]}")
    print(f"PASSENGER_ID={row[2]}")
    print(f"SEAT={row[3]}")

cursor.close()
conn.close()