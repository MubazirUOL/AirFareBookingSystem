import sys
import mysql.connector

# Expect: ticketID
if len(sys.argv) < 1:
    print("Usage: python readTicketById.py <ticketID>")
    sys.exit(1)

ticketID = int(sys.argv[1])

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="airfaredb"
    )

    cursor = conn.cursor()

    sql = "SELECT * FROM ticket WHERE id = %s"
    cursor.execute(sql, (ticketID,))

    result = cursor.fetchone()

    if result:
        print("Ticket Found:")
        print("-------------------------------------------------------")
        print(f"Ticket ID    : {result[0]}")
        print(f"Flight ID    : {result[1]}")
        print(f"Passenger ID : {result[2]}")
        print(f"Seat         : {result[3]}")
        print(f"Price        : {result[4]}")
        print(f"Booked Date  : {result[5]}")
        print("-------------------------------------------------------")
    else:
        print("No ticket found with this ID")

except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()