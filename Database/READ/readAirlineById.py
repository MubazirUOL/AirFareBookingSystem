import sys
import mysql.connector

# Expect: airlineID
if len(sys.argv) < 1:
    print("Usage: python readairlineById.py <airlineID>")
    sys.exit(1)

airlineID = int(sys.argv[1])

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="testdb"
    )

    cursor = conn.cursor()

    sql = "SELECT * FROM airline WHERE id = %s"
    cursor.execute(sql, (airlineID,))

    result = cursor.fetchone()

    if result:
        print("Airline Found:")
        print("-------------------------------------------------------")
        print(f"AirlineID       : {result[0]}")
        print(f"Airline         : {result[1]}")
        print(f"Country         : {result[2]}")
        print(f"Register date   : {result[3]}")
        print("-------------------------------------------------------")
    else:
        print("No airline found with this ID")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()