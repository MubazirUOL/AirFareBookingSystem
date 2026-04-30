import sys
from displayFlightsByLocation import To
import mysql.connector

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="testdb"
    )

    # Expect: passengerID, newDate
    if len(sys.argv) < 2:
        print("Usage: python updatePassengerLastFlight.py <passengerID > <newDate>")
        sys.exit(1)

    passengerID = sys.argv[1]
    newDate = sys.argv[2]

    cursor = conn.cursor()
    
    # Fetch passenger's last flight details 
    sql = "UPDATE passenger SET lastFlight = %s WHEWRE passengerID = %s;"
    cursor.execute(sql,(newDate, passengerID))
    conn.commit()
except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()