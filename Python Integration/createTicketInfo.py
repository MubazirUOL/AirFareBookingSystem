import sys
import mysql.connector

# Validate input arguments
if len(sys.argv) < 6:
    print("Usage: python createTicketInfo.py <flightID> <passengerID> <seatNo> <price> <dateOfBooking> <status>")
    sys.exit(1)

# Read values from C++ command-line arguments 
flightID = int(sys.argv[1])
passengerID = int(sys.argv[2])
seatNo = sys.argv[3]
price = sys.argv[4]
dateOfBooking = sys.argv[5]
status = int(sys.argv[6])

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
    sql = "INSERT INTO ticket (flightID, passengerID, seatNo, price, dateOfBooking, status) VALUES (%s, %s, %s, %s, %s, %s)"
    cursor.execute(sql, (flightID, passengerID, seatNo, price, dateOfBooking, status))

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
