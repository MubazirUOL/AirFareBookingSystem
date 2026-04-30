import sys
import mysql.connector

# Validate input arguments
if len(sys.argv) < 6:
    print("Usage: python createAirplaneInfo.py <airlineID> <name> <seatRow> <seatColumn> <originDate> <operateStatus>")
    sys.exit(1)

# Read values from C++ command-line arguments
airlineID = int(sys.argv[1])
name = sys.argv[2]
seatRow = int(sys.argv[3])
seatColumn = int(sys.argv[4])
originDate = sys.argv[5]
operateStatus = int(sys.argv[6])

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
    sql = "INSERT INTO airplane (airlineID, name, seatRow, seatColumn, originDate, operateStatus) VALUES (%s, %s, %s, %s, %s, %s)"
    cursor.execute(sql, (airlineID, name, seatRow, seatColumn, originDate, operateStatus))

    # Commit the transaction
    conn.commit()

    print("Airplane record inserted successfully!")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    # Always close cursor and connection
    if cursor:
        cursor.close()
    if conn:
        conn.close()
