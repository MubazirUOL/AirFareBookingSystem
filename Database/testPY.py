import sys
import mysql.connector
# MySQL connection
conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="123456",
    database="testdb"
)

# Read arguments from C++
# sys.argv[0] = script name
#name = sys.argv[1]
#age = int(sys.argv[2])

# PUT SQL QUERIES HERE
cursor = conn.cursor()

sql = "Select * from passenger;"
cursor.execute(sql)

for row in cursor.fetchall():
    print(row)

cursor.close()
conn.close()