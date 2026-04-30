import mysql.connector
import sys

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="airfaredb"
    )

    cursor = conn.cursor()

    cursor.execute("SELECT * FROM flight")

    results = cursor.fetchall()

    if results:
        print("All Flights:\n")
        print("Flight ID\tAirline ID\tAirplane ID\t      Source\t     Destination\t Flight date\t  Take off")
        print("------------------------------------------------------------------------------------------------------------------")
        for r in results:
            print(f"""  {r[0]:^5}{r[1]:15}{r[2]:^30}{r[3]:^10}{r[4]:^20}{r[5]:^25}{r[6]:^5}\n------------------------------------------------------------------------------------------------------------------""")
    else:
        print("No Flight records found.")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()