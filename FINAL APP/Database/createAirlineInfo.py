import sys
import mysql.connector

# Validate input arguments
if len(sys.argv) < 4:
    print("Usage: python insert_airline.py <title> <country> <code>")
    sys.exit(1)

# Read values from C++ command-line arguments
title = sys.argv[1]
country = sys.argv[2]
code = sys.argv[3]

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
    sql = "INSERT INTO airline (title, country, code) VALUES (%s, %s, %s)"
    cursor.execute(sql, (title, country, code))

    # Commit the transaction
    conn.commit()

    print("Airline record inserted successfully!")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    # Always close cursor and connection
    if cursor:
        cursor.close()
    if conn:
        conn.close()
