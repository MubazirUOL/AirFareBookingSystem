import mysql.connector
import sys

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="12345678",
        database="testdb"
    )

    cursor = conn.cursor()

    cursor.execute("SELECT * FROM airplane")

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