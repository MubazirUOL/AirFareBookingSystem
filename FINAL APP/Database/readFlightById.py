import sys
import mysql.connector

# Expect: flightID
if len(sys.argv) < 1:
    print("Usage: python readFlightById.py <flightID>")
    sys.exit(1)

flightID = int(sys.argv[1])

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="testdb"
    )

    cursor = conn.cursor()

    sql = "SELECT * FROM flight WHERE id = %s"
    cursor.execute(sql, (flightID,))

    result = cursor.fetchone()

    if result:
        print("Flight Found:")
        print("-------------------------------------------------------")
        print(f"Flight ID       : {result[0]}")
        print(f"Airline ID      : {result[1]}")
        print(f"Airplane ID     : {result[2]}")
        print(f"From            : {result[3]}")
        print(f"To              : {result[4]}")
        print(f"Date of Flight  : {result[5]}")
        print(f"Take Off Time   : {result[6]}") 
        print(f"Arrival Time    : {result[7]}") # to be adjusted
        print(f"Flight Status   : {result[8]}") # to be adjusted
        print("-------------------------------------------------------")
    else:
        print("No flight found with this ID")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()