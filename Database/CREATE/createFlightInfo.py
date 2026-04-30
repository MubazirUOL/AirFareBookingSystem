import sys
import mysql.connector

# Validate input arguments
if len(sys.argv) < 8:
    print("Usage: python createFlightInfo.py <airlineID> <airplaneID> <source> <destination> <dateOfFlight> <takeOffTime> <arrivalTime> <flightStatus>")
    sys.exit(1)

# Read values from C++ command-line arguments 
airlineID = int(sys.argv[1])
airplaneID = int(sys.argv[2])
source = sys.argv[3]
destination = sys.argv[4]
dateOfFlight = sys.argv[5]
takeOffTime = sys.argv[6]
arrivalTime = sys.argv[7]
flightStatus = int(sys.argv[8])
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
    sql = "INSERT INTO flight (airlineID, airplaneID, source, destination, dateOfFlight, takeOffTime, arrivalTime, flightStatus) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)"
    cursor.execute(sql, (airlineID, airplaneID, source, destination, dateOfFlight, takeOffTime, arrivalTime, flightStatus))

    # Commit the transaction
    conn.commit()

    print("Flight record inserted successfully!")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    # Always close cursor and connection
    if cursor:
        cursor.close()
    if conn:
        conn.close()
