import mysql.connector
import sys


# Expect: passengerID
if len(sys.argv) < 1:
    print("Usage: python displayTicketsByPassengerId.py <ticketID>")
    sys.exit(1)

passengerID = int(sys.argv[1])

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="airfaredb"
    )

    cursor = conn.cursor()

    sql = "SELECT * FROM ticket WHERE passengerID = %s"
    cursor.execute(sql, (passengerID,))

    results = cursor.fetchall()

    if results:
        print(f"All Tickets of ID#{passengerID}\n")
        print("Ticket ID\tFlight ID\tPassenger ID\tSeat\t\tPrice\t\tDate of Booking\t\tStatus")
        for r in results:
            print(f"""  {r[0]}\t\t  {r[1]}\t\t {r[2]}\t\t {r[3]}\t\t {r[4]}\t\t  {r[5]}\t\t  {r[6]}\t\n---------------------------------------------------------------------------------------------------------------------""")
    else:
        print("No Ticket records found.")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()