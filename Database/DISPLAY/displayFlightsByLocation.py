import sys
import mysql.connector

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="testdb"
    )

    # Expect: flightID
    if len(sys.argv) < 2:
        print("Usage: python displayFlightInfo.py <Source> <Destination>")
        sys.exit(1)

    From = (sys.argv[1])
    To = (sys.argv[2])

    cursor = conn.cursor()
    
    # Fetch flight details based on source and destination
    sql = "SELECT * FROM flight WHERE source = %s AND destination = %s"
    cursor.execute(sql, (From, To))

    results = cursor.fetchall()

    if results:
        print("Flights from :\n")
        for r in results:
            print(f"""
            Flight ID      : {r[0]}
            Airline ID     : {r[1]}
            Airplane ID    : {r[2]}
            Source         : {r[3]}
            Destination    : {r[4]}
            Date of Flight : {r[5]}
            Take Off Time  : {r[6]}
            -------------------------
            """)
    else:
        print("No Flight records found.")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()