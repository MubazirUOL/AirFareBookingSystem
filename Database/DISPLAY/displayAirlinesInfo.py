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

    cursor.execute("SELECT * FROM airline")

    results = cursor.fetchall()

    if results:
        print("All Airlines:\n")
        print("Airline ID\t\tTitle\t\t     Country")
        print("-------------------------------------------------------")
        for r in results:
            print(f"""  {r[0]:^5}{r[1]:^40}{r[2]}\n-------------------------------------------------------""")
    else:
        print("No Airline records found.")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()