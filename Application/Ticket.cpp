#include <iostream>
#include "Module.h"
using namespace std;

class Ticket:Module {
	public:
		int id;
		int flightId;
		int passengerId;
		string seatCode;
		string price;
		string dateOfBooking;
		bool status;
	public:
		void create() override {
			cout << "Generating Ticket for Passenger #" << passengerId << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "FLIGHT ID:\t\t#" << flightId << endl;
			cout << "SEAT CODE:\t\t" << seatCode << endl;
			cout << "BOOKING PRICE:\t\t" << price << endl;
			cout << "DATE OF BOOKING:\t" << dateOfBooking << endl;
			cout << "BOOKING STATUS:\t\t" << status << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "Press 1 to Create: ";
			cin >> id;
			if(id == 1)
				saveToDatabase();
			else
				return;
			getch();
		}
		void saveToDatabase() {
		    string command =
		    "python \"Database\\createTicketInfo.py\" \"" +
		    to_string(flightId) + "\" \"" +
		    to_string(passengerId) + "\" \"" +
		    seatCode + "\" \"" +
		    price + "\" \"" +
		    dateOfBooking + "\" \"" +
		    to_string(status) + "\"";
		
		    system(command.c_str());
		    cout << "Continue: ";
		}
		void readByID() override {
		    cout << "Enter Ticket-ID:\t#";
		    cin >> id;
		    string command = "python \"Database\\readTicketById.py\" " + to_string(id);
			system(command.c_str());
			getch();
		}
		void readByPassengerID() {
		    cout << "Enter Passenger-ID:\t#";
		    cin >> passengerId;
		    string command = "python \"Database\\displayTicketsByPassengerId.py\" " + to_string(passengerId);
			system(command.c_str());
			getch();
		}
		void display() override {
			string command = "python \"Database\\displayTicketsInfo.py\" \"";
		    system(command.c_str());
		    cout << "Continue: ";
		    getch();
		}
		void cancel() {
			cout << "FEATURE UNDER DEVELOPMENT..." << endl;
		}
		void generateTicket(string name, string flightCodeID, string takeOffTime, string ticketNo) {
			// <passengerName> <flightCode-flightID> <seatCode> <date> <time> <ticketNo>
			 // --------- BUILD PYTHON COMMAND ----------
			string command =
			    "python \"Ticket\\ticketGeneration.py\" \"" +
			    name + "\" " +
			    flightCodeID + " " +
			    seatCode + " \"" +
			    dateOfBooking + "\" \"" +
			    takeOffTime + "\" " +
			    ticketNo;
		
		    // --------- EXECUTE ----------
		    int result = system(command.c_str());
		    if (result == 0)
		        cout << "Ticket PDF generated successfully." << endl;
		    else
		        cout << "Error generating ticket." << endl;
		    getch();
		}
		void captureTicket(int input) {
		    id = input;
		    string command = "python \"Database\\checkTicketById.py\" " + to_string(id);
		
		    FILE* pipe = _popen(command.c_str(), "r");
		    if (!pipe) {
		        cout << "Failed to execute Python script\n";
		        return;
		    }
		
		    char buffer[256];
		    string line;
		
		    while (fgets(buffer, sizeof(buffer), pipe)) {
		        line = buffer;
		
		        // Remove newline and carriage return characters
		        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		
		        // Split by '='
		        size_t pos = line.find('=');
		        if (pos == string::npos) continue;
		
		        string key = line.substr(0, pos);
		        string value = line.substr(pos + 1);
		
		        // Trim spaces
		        key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
		        value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
		
		        // Assign to class members
		        if (key == "TICKET_ID") {
		            if (!value.empty()) id = stoi(value);
		        }
		        else if (key == "SEAT") {
		            seatCode = value;
		        }
		        else if (key == "FLIGHT_ID") {
		            if (!value.empty()) flightId = stoi(value);
		        }
		        else if (key == "PASSENGER_ID") {
		            if (!value.empty()) passengerId = stoi(value);
		        }
		    }
		
		    _pclose(pipe);
		
		    cout << "Ticket data loaded successfully. ID# " << id << endl;;
		}
		int getID(){
			return id;
		}
};

