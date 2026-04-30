import sys
import mysql.connector

try:
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="123456",
        database="airfaredb"
    )

    # Expect: passengerCNIC, newDate
    if len(sys.argv) < 2:
        print("Usage: python updatePassengerLastFlight.py <passengerCNIC > <newDate>")
        sys.exit(1)

    passengerCNIC = sys.argv[1]
    newDate = sys.argv[2]

    cursor = conn.cursor()
    
    # Fetch passenger's last flight details 
    sql = "UPDATE passenger SET lastFlight = %s WHERE cnic = %s;"
    cursor.execute(sql,(newDate, passengerCNIC))
    conn.commit()
except mysql.connector.Error as err:
    print(f"Error: {err}")

finally:
    if cursor:
        cursor.close()
    if conn:
        conn.close()