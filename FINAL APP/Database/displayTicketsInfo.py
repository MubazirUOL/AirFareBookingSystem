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

    cursor.execute("SELECT * FROM ticket")

    results = cursor.fetchall()

    if results:
        print("All Ticket:\n")
        print("Ticket ID\tFlight ID\tPassenger ID\tSeat\t\tPrice\t\tDate of Booking\t\tStatus\n---------------------------------------------------------------------------------------------------------------------")
        for r in results:
            print(f"""  {r[0]}\t\t  {r[1]}\t\t {r[2]}\t\t {r[3]}\t\t {r[4]}\t\t  {r[5]}\t\t  {r[6]}\n---------------------------------------------------------------------------------------------------------------------""")
    else:
        print("No Ticket records found.")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()