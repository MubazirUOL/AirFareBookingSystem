import sys
import mysql.connector

# Expect: passengerName
if len(sys.argv) < 2:
    print("Usage: python readPassengerByName.py <passengerName>")
    sys.exit(1)

passengerName = sys.argv[1]

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="airfaredb"
    )
    
    cursor = conn.cursor(buffered=True)
    sql = "SELECT * FROM passenger WHERE name LIKE %s"
    cursor.execute(sql, (f"%{passengerName}%",))
    results = cursor.fetchall()
    
    if results:
        print("Passengers Found:")
        print("-------------------------------------------------------")
        for result in results:
            print(f"PassengerID : {result[0]}")
            print(f"CNIC #      : {result[1]}")
            print(f"Name        : {result[2]}")
            print(f"Contact     : {result[3]}")
            print(f"Last Flight : {result[4]}")
            print("-------------------------------------------------------")
    else:
        print("No passenger found with this name: " + passengerName)
        
except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()