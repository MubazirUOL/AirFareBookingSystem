import mysql.connector
import sys

# Expect: airlineID
if len(sys.argv) < 1:
    print("Usage: python displayAirplanesInfo.py <airlineID>")
    sys.exit(1)

airlineID = int(sys.argv[1])

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="airfaredb"
    )

    cursor = conn.cursor()
    sql = "SELECT * FROM airplane WHERE airlineID = %s"
    cursor.execute(sql, (airlineID,))
    results = cursor.fetchall()
    
    if results:
        print("All Airplanes:\n")
        print("Airplane ID\tAirline ID\t   Model Name\t      Rows\t  Columns")
        print("--------------------------------------------------------------------------")
        for r in results:
            print(f"""{r[0]:^5}{r[1]:^30}{r[2]:^10}{r[3]:^20}{r[4]:^10}\n--------------------------------------------------------------------------""")

    else:
        print("No Airplanes records found.")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()