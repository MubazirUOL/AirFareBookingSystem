import sys
import mysql.connector

# Validate input arguments
if len(sys.argv) < 5:
    print("Usage: python createAirplaneInfo.py <airlineID> <model> <rows> <columns>")
    sys.exit(1)

# Read values from C++ command-line arguments
airlineID = int(sys.argv[1])
model = sys.argv[2]
rows = int(sys.argv[3])
columns = int(sys.argv[4])

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
    sql = "INSERT INTO airplane (airlineID, model, totalRows, totalColumns) VALUES (%s, %s, %s, %s)"
    cursor.execute(sql, (airlineID, model, rows, columns))

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
