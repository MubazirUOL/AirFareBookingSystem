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

    cursor.execute("SELECT * FROM passenger")

    results = cursor.fetchall()

    if results:
        print("All Passengers:\n")
        print("PassengerID\t  CNIC\t\t  Passenger Name\t     Contact\t       Last Flight")
        print("------------------------------------------------------------------------------------------")
        for r in results:
            print(f"""  {r[0]:^5}{r[1]:^25}{r[2]:<20}{r[3]:^25}{r[4]:^15}\n------------------------------------------------------------------------------------------""")
    else:
        print("No Passenger records found.")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()