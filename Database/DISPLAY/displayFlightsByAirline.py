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
    if len(sys.argv) < 1:
        print("Usage: python displayFlightByAirline.py <airlineID>")
        sys.exit(1)

    cursor = conn.cursor()

    airlineID = (sys.argv[1])
    
    # Fetch flight details based on airline ID
    sql = "SELECT * FROM flight WHERE airlineID = %s"
    cursor.execute(sql,(airlineID,))

    results = cursor.fetchall()

    sql = "SELECT title from airline WHERE id = %s"
    cursor.execute(sql,(airlineID,))
    airlineTitle = cursor.fetchone()[0]

    if results:
        print(f"Flights by {airlineTitle}:\n")
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