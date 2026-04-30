import sys
import mysql.connector

# Expect: airplaneID
if len(sys.argv) < 1:
    print("Usage: python readairplaneById.py <airplaneID>")
    sys.exit(1)

airplaneID = int(sys.argv[1])

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="testdb"
    )

    cursor = conn.cursor()

    sql = "SELECT * FROM airplane WHERE id = %s"
    cursor.execute(sql, (airplaneID,))

    result = cursor.fetchone()

    if result:
        print("Airplane Found:")
        print("-------------------------------------------------------")
        print(f"Airplane ID     : {result[0]}")
        print(f"Airline ID      : {result[1]}")
        print(f"Airplane Model  : {result[2]}")
        print(f"Dimensions      : {result[3]} x {result[4]}")
        print(f"Origin Date     : {result[5]}")
        print(f"Operate Status  : {result[6]}")
        print("-------------------------------------------------------")
    else:
        print("No airplane found with this ID")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()