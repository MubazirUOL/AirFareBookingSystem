import sys
import mysql.connector

# Validate input arguments
if len(sys.argv) < 7:
    print("Usage: python createTicketInfo.py <flightID> <passengerID> <source> <destination> <seatRow> <seatColumn> <price>")
    sys.exit(1)

# Read values from C++ command-line arguments 
flightID = int(sys.argv[1])
passengerID = int(sys.argv[2])
source = sys.argv[3]
destination = sys.argv[4]
seatRow = int(sys.argv[5])
seatColumn = int(sys.argv[6])
price = int(sys.argv[7])

try:
    # Connect to MySQL
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="testdb"
    )

    cursor = conn.cursor()

    # Insert data into airline table
    sql = "INSERT INTO ticket (flightID, passengerID, source, destination, seatRow, seatColumn, price) VALUES (%s, %s, %s, %s, %s, %s, %s)"
    cursor.execute(sql, (flightID, passengerID, source, destination, seatRow, seatColumn, price))

    # Commit the transaction
    conn.commit()

    print("Ticket record inserted successfully!")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    # Always close cursor and connection
    if cursor:
        cursor.close()
    if conn:
        conn.close()
