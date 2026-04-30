import sys
import os
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import A6
from reportlab.lib import colors

# Create Tickets folder if not exists
TICKETS_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Tickets")
if not os.path.exists(TICKETS_DIR):
    os.makedirs(TICKETS_DIR)

# Validate input arguments
if len(sys.argv) < 7:
    print("Usage: python ticketGeneration.py <passengerName> <flightCode-flightID> <seatCode> <date> <time> <ticketNo>")
    sys.exit(1)

# Read values from C++ command-line arguments
name = sys.argv[1]
flightCode = sys.argv[2]
seatCode = sys.argv[3]
date = sys.argv[4]
time = sys.argv[5]
ticketNo = sys.argv[6]

def generate_ticket(data):
    file_name = f"AirFare_Ticket_{data['ticket_no']}.pdf"
    c = canvas.Canvas(file_name, pagesize=A6)

    width, height = A6

    # ---------- HEADER ----------
    c.setFillColor(colors.red)
    c.rect(0, height - 45, width, 45, fill=1)

    # Logo
    c.drawImage(data["logo"], 10, height - 40, width=30, height=30, mask='auto')

    # Heading
    c.setFillColor(colors.white)
    c.setFont("Helvetica-Bold", 14)
    c.drawCentredString(width / 2 + 10, height - 28, "AirFare Booking System")

    # ---------- BODY ----------
    c.setFillColor(colors.black)
    y = height - 70

    c.setFont("Helvetica", 9)
    c.drawString(20, y, "Passenger")
    c.drawString(120, y, "Flight")
    y -= 12

    c.setFont("Helvetica-Bold", 11)
    c.drawString(20, y, data["name"])
    c.drawString(120, y, data["flight"])

    # Divider
    y -= 15
    c.setStrokeColor(colors.red)
    c.line(15, y, width - 15, y)

    # ---------- DETAILS ----------
    y -= 20
    c.setFont("Helvetica", 9)
    c.drawString(20, y, "Seat")
    c.drawString(80, y, "Date")
    c.drawString(140, y, "Time")

    y -= 12
    c.setFont("Helvetica-Bold", 11)
    c.drawString(20, y, data["seat"])
    c.drawString(80, y, data["date"])
    c.drawString(140, y, data["time"])

    # Divider
    y -= 18
    c.line(15, y, width - 15, y)

    # ---------- TICKET NUMBER ----------
    y -= 20
    c.setFont("Helvetica", 9)
    c.drawString(20, y, "Ticket Number")

    y -= 12
    c.setFont("Helvetica-Bold", 12)
    c.setFillColor(colors.red)
    c.drawString(20, y, data["ticket_no"])

    # ---------- FOOTER ----------
    c.setFillColor(colors.black)
    c.setFont("Helvetica-Oblique", 8)
    c.drawCentredString(width / 2, 20,
                        "Please arrive 30 minutes before departure")

    c.save()
    print(f"Ticket Generated: {file_name}")

fullTicketNo = f"{seatCode}-{ticketNo}"
# --------- EXAMPLE DATA ----------
ticket_data = {
    "name": name,
    "flight": flightCode,
    "seat": seatCode,
    "date": date,
    "time": time,
    "ticket_no": fullTicketNo,
    "logo": "airplane.ico"
}

file_name = os.path.join(TICKETS_DIR, f"AirFare_Ticket_{ticket_data['ticket_no']}.pdf")
# Then pass this file_name to your generate_ticket function
generate_ticket(ticket_data)