import sys
import mysql.connector

# Validate input arguments
if len(sys.argv) < 4:
    print("Usage: python createPassengerInfo.py <cnic> <name> <contact> <lastFlight>")
    sys.exit(1)

# Read values from C++ command-line arguments
cnic = sys.argv[1]
name = sys.argv[2]
contact = sys.argv[3]
lastFlight = sys.argv[4]
try:
    # Connect to MySQL
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="airfaredb"
    )

    cursor = conn.cursor()

    # Insert data into airline table
    sql = "INSERT INTO passenger (cnic, name, contact, lastFlight) VALUES (%s, %s, %s, %s)"
    cursor.execute(sql, (cnic, name, contact, lastFlight))

    # Commit the transaction
    conn.commit()

    print("Passenger record inserted successfully!")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    # Always close cursor and connection
    if cursor:
        cursor.close()
    if conn:
        conn.close()
