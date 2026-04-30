import sys
import mysql.connector

if len(sys.argv) < 2:
    sys.exit(1)

flight_id = int(sys.argv[1])

conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="airfaredb"
)

cursor = conn.cursor()

cursor.execute(
    """SELECT airlineId, airplaneId, source, destination,
              dateOfFlight, takeOffTime
       FROM flight WHERE id=%s""",
    (flight_id,)
)

row = cursor.fetchone()

if row:
    print(f"AIRLINE_ID={row[0]}")
    print(f"AIRPLANE_ID={row[1]}")
    print(f"SOURCE={row[2]}")
    print(f"DESTINATION={row[3]}")
    print(f"DATE={row[4]}")
    print(f"TIME={row[5]}")

cursor.close()
conn.close()
