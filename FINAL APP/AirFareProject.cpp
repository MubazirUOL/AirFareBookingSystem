/* AIRFARE BOOKING SYSTEM - GROUP PROJECT OOP */
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

class Module {
	public:
	    virtual void create() = 0;
	    virtual void readByID() = 0;
	    virtual void display() = 0;
	    std::string showFormatDate(const std::string& dd, const std::string& mm, const std::string& yyyy) {
	        return dd + "/" + mm + "/" + yyyy;
	    }
	    std::string showFormatTime(const std::string& h, const std::string& m, const std::string& t) {
	        return h + ":" + m + " " + t;
	    }
	    virtual ~Module() = default;  // Always good to have a virtual destructor
	};

class Airline : public Module {
private:
    int id;
    string title;
    string country;
    string code;

public:
    void create() {
        try {
            cout << "Enter Airline Title:\t";
            getline(cin, title);
            if (title == "0" || title.empty())
                return;

            cout << "Enter Country Name:\t";
            cin >> country;
            if (country == "0" || country.empty())
                return;

            cout << "Enter Airline Code:\t";
            cin >> code;
            if (code == "0" || code.empty())
                return;

            if (title.empty() || country.empty() || code.empty())
                throw invalid_argument("ERROR: Airline details cannot be empty.");

            saveToDatabase();
            getch();
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            getch();
        }
        catch (const exception& e) {
            cout << "Unexpected error: " << e.what() << endl;
            getch();
        }
    }

    void readByID() {
        try {
            cout << "Enter Airline ID: #";
            cin >> id;
            if (cin.fail() || id <= 0)
                throw invalid_argument("Invalid ID entered.");

            string command = "python \"Database\\readAirlineById.py\" " + to_string(id);
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Failed to execute Python script.");

            cout << "Continue: ";
            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void display() {
        try {
            string command = "python \"Database\\displayAirlinesInfo.py\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Failed to execute Python script.");

            cout << "Continue: ";
            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            getch();
        }
    }

    void saveToDatabase() {
        try {
            string command =
                "python \"Database\\createAirlineInfo.py\" \"" +
                title + "\" \"" +
                country + "\" \"" +
                code + "\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Failed to execute Python script.");

            cout << "Continue: ";
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    int getID() {
        return id;
    }

    string getCode() {
        return code;
    }

    void captureAirline(int input) {
        id = input;
        string command = "python \"Database\\checkAirlineById.py\" " + to_string(id);

        try {
            FILE* pipe = _popen(command.c_str(), "r");
            if (!pipe)
                throw runtime_error("Failed to execute Python script via pipe.");

            char buffer[256];
            string line;

            while (fgets(buffer, sizeof(buffer), pipe)) {
                line = buffer;

                // Remove newline and carriage return characters
                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                // Split by '='
                size_t pos = line.find('=');
                if (pos == string::npos) continue;

                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                key.erase(remove(key.begin(), key.end(), ' '), key.end());
                value.erase(remove(value.begin(), value.end(), ' '), value.end());

                if (key == "TITLE") title = value;
                else if (key == "COUNTRY") country = value;
                else if (key == "CODE") code = value;
            }

            int closeStatus = _pclose(pipe);
            if (closeStatus != 0)
                throw runtime_error("Error closing Python pipe.");

            cout << "Airline data loaded successfully. Code: " << code << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
};

class Airplane : public Module {
private:
    int id;
    int airlineId;
    string model;
    int rows;
    int columns;

public:
    void create() {
        try {
            cout << "Enter Airline ID:\t";
            cin >> airlineId;
            if (cin.fail() || airlineId <= 0)
                throw invalid_argument("Invalid Airline ID.");

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Model Title:\t";
            getline(cin, model);
            if (model.empty() || model == "0")
                throw invalid_argument("Model cannot be empty.");

            cout << "Enter Total Rows:\t";
            cin >> rows;
            if (cin.fail() || rows <= 0)
                throw invalid_argument("Rows must be a positive number.");

            cout << "Enter Total Columns:\t";
            cin >> columns;
            if (cin.fail() || columns <= 0)
                throw invalid_argument("Columns must be a positive number.");

            saveToDatabase();
            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void readByID() {
        cout << "NOT AVAILABLE..." << endl;
    }

    void display() {
        try {
            string command = "python \"Database\\displayAirplanesInfo.py\" " + to_string(airlineId);
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Failed to execute Python script.");

            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            getch();
        }
    }

    void saveToDatabase() {
        try {
            string command =
                "python \"Database\\createAirplaneInfo.py\" \"" +
                to_string(airlineId) + "\" \"" +
                model + "\" \"" +
                to_string(rows) + "\" \"" +
                to_string(columns) + "\"";

            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Failed to execute Python script.");

            cout << "Continue: ";
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void setID(int aid) {
        airlineId = aid;
    }

    int getID() {
        return id;
    }

    int getAirlineID() {
        return airlineId;
    }

    void mapAirplane() {
        try {
            if (rows <= 0 || columns <= 0)
                throw invalid_argument("Rows and columns must be positive to map airplane.");

            char alphabet[26] = {
                'A','B','C','D','E','F','G','H','I','J','K','L',
                'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
            };

            int dash = (columns * 17) - (columns - 1);
            cout << string(dash, '-') << endl;

            for (int i = 0; i < rows; i++) {
                for (int j = 1; j <= columns; j++) {
                    if (i >= 26) throw out_of_range("Too many rows to map (max 26).");
                    cout << "|\t" << alphabet[i] << j << "\t|";
                }
                cout << endl << string(dash, '-') << endl;
            }
        }
        catch (const exception& e) {
            cout << "Error in mapping airplane: " << e.what() << endl;
        }
    }

    void captureAirplane(int input) {
        id = input;
        string command = "python \"Database\\checkAirplaneById.py\" " + to_string(id);

        try {
            FILE* pipe = _popen(command.c_str(), "r");
            if (!pipe)
                throw runtime_error("Failed to execute Python script via pipe.");

            char buffer[256];
            string line;

            while (fgets(buffer, sizeof(buffer), pipe)) {
                line = buffer;

                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                size_t pos = line.find('=');
                if (pos == string::npos) continue;

                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                key.erase(remove(key.begin(), key.end(), ' '), key.end());
                value.erase(remove(value.begin(), value.end(), ' '), value.end());

                if (key == "AIRLINE_ID") {
                    if (!value.empty()) airlineId = stoi(value);
                }
                else if (key == "MODEL") {
                    model = value;
                }
                else if (key == "ROWS") {
                    if (!value.empty()) rows = stoi(value);
                }
                else if (key == "COLUMNS") {
                    if (!value.empty()) columns = stoi(value);
                }
            }

            int closeStatus = _pclose(pipe);
            if (closeStatus != 0)
                throw runtime_error("Error closing Python pipe.");

            cout << "Airplane data loaded successfully.\n";
        }
        catch (const exception& e) {
            cout << "Error in captureAirplane: " << e.what() << endl;
        }
    }
};

class Passenger : public Module {
private:
    int id;
    string cnic;
    string name;
    string contact;
    string lastFlight;

public:
    string showToday() {
        SYSTEMTIME st;
        GetLocalTime(&st);

        string dd   = to_string(st.wDay);
        string mm   = to_string(st.wMonth);
        string yyyy = to_string(st.wYear);

        if (st.wDay < 10) dd = "0" + dd;
        if (st.wMonth < 10) mm = "0" + mm;

        return dd + "/" + mm + "/" + yyyy;
    }

    void create() override {
        try {
            cout << "Enter Passenger CNIC:\t";
            cin >> cnic;
            if (cin.fail() || cnic.empty() || cnic == "0")
                throw invalid_argument("Invalid CNIC.");

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Passenger Name:\t";
            getline(cin, name);
            if (name.empty() || name == "0")
                throw invalid_argument("Name cannot be empty.");

            cout << "Enter Contact Number:\t";
            cin >> contact;
            if (contact.empty() || contact == "0")
                throw invalid_argument("Contact cannot be empty.");

            lastFlight = showToday();
            saveToDatabase();
            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void readByID() override {
        try {
            cout << "Enter Passenger-ID:\t#";
            cin >> id;
            if (cin.fail() || id <= 0)
                throw invalid_argument("Invalid Passenger ID.");

            string command = "python \"Database\\readPassengerById.py\" " + to_string(id);
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void readByName() {
        try {
            cout << "Enter Name: ";
            cin >> name;
            if (name.empty())
                throw invalid_argument("Name cannot be empty.");

            string command = "python \"Database\\readPassengerByName.py\" \"" + name + "\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            cout << "Continue: ";
            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void display() override {
        try {
            string command = "python \"Database\\displayPassengersInfo.py\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            cout << "Continue: ";
            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            getch();
        }
    }

    void updateLastFlight() {
        try {
            if (cnic.empty())
                throw invalid_argument("CNIC not set.");

            lastFlight = showToday();
            string command = "python \"Database\\updatePassengerLastFlight.py\" " + cnic + " " + lastFlight;
            int result = system(command.c_str());

            if (result != 0)
                throw runtime_error("Python script failed with code " + to_string(result));
            
            cout << "Updated Successfully!" << endl;
        }
        catch (const exception& e) {
            cout << "Error updating last flight: " << e.what() << endl;
        }
    }

    void saveToDatabase() {
        try {
            if (cnic.empty() || name.empty() || contact.empty() || lastFlight.empty())
                throw invalid_argument("Passenger data incomplete.");

            string command =
                "python \"Database\\createPassengerInfo.py\" \"" +
                cnic + "\" \"" +
                name + "\" \"" +
                contact + "\" \"" +
                lastFlight + "\"";

            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            cout << "Continue: ";
        }
        catch (const exception& e) {
            cout << "Error saving passenger: " << e.what() << endl;
        }
    }

    bool checkOrCreate() {
        try {
            cout << "Enter Passenger-CNIC:\t#";
            cin >> cnic;
            if (cnic.empty())
                throw invalid_argument("CNIC cannot be empty.");

            string command = "python \"Database\\checkPassengerByCnic.py\" " + cnic;
            FILE* pipe = _popen(command.c_str(), "r");
            if (!pipe)
                throw runtime_error("Failed to run Python script.");

            char buffer[256];
            string output;

            while (fgets(buffer, sizeof(buffer), pipe))
                output += buffer;

            int closeStatus = _pclose(pipe);
            if (closeStatus != 0)
                throw runtime_error("Error closing Python pipe.");

            if (output.find("FIND") != string::npos) {
                cout << "Passenger already exists.\n";
                cout << output << endl;
                return true;
            } 
            else if (output.find("NOT_FOUND") != string::npos) {
                cout << "Passenger not found. Creating new passenger...\n";
                return false;
            }
            else {
                throw runtime_error("Unexpected output from Python script.");
            }
        }
        catch (const exception& e) {
            cout << "Error in checkOrCreate: " << e.what() << endl;
            getch();
            return false;
        }
    }

    int getID() {
        return id;
    }

    string getName() {
        return name;
    }
};

class Flight : public Module {
private:
    int id;
    int airlineId;
    int airplaneId;
    string source;
    string destination;
    string dateOfFlight;
    string takeOffTime;

public:
    void create() override {
        try {
            cout << "Enter Source City Code:\t\t";
            cin >> source;
            if (source.empty() || source == "0")
                throw invalid_argument("Invalid Source City Code.");

            cout << "Enter Destination City Code:\t";
            cin >> destination;
            if (destination.empty() || destination == "0")
                throw invalid_argument("Invalid Destination City Code.");

            int d, m, y;
            cout << "Enter Date Of Flight:" << endl;
            cout << "Enter Day (1 - 31)\t:";
            cin >> d;
            cout << "Enter Month (1 - 12):\t";
            cin >> m;
            cout << "Enter Year (>=2026):\t";
            cin >> y;

            if (cin.fail() || d < 1 || d > 31 || m < 1 || m > 12 || y < 2026)
                throw invalid_argument("Invalid date input.");

            dateOfFlight = showFormatDate(d, m, y);

            string hour, minute;
            cout << "Enter Take Off Time:" << endl;
            cout << "Enter Hour (0 - 23): ";
            cin >> hour;
            cout << "Enter Minute (00/15/30/45): ";
            cin >> minute;

            takeOffTime = showFormatTime(hour, minute);

            saveToDatabase();
            getch();
        }
        catch (const exception& e) {
            cout << "Error in flight creation: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void saveToDatabase() {
        try {
            string command =
                "python \"Database\\createFlightInfo.py\" \"" +
                to_string(airlineId) + "\" \"" +
                to_string(airplaneId) + "\" \"" +
                source + "\" \"" +
                destination + "\" \"" +
                dateOfFlight + "\" \"" +
                takeOffTime + "\"";

            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Failed to execute Python script.");

            cout << "Continue: ";
        }
        catch (const exception& e) {
            cout << "Error saving flight: " << e.what() << endl;
        }
    }

    void readByID() override {
        try {
            cout << "Enter Flight ID: ";
            cin >> id;
            if (cin.fail() || id <= 0)
                throw invalid_argument("Invalid Flight ID.");

            // Data integration can go here
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void display() override {
        try {
            string command = "python \"Database\\displayFlightsInfo.py\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            cout << "Continue: ";
            getch();
        }
        catch (const exception& e) {
            cout << "Error displaying flights: " << e.what() << endl;
            getch();
        }
    }

    void displayCurrent() {
        try {
            dateOfFlight = showToday();
            string command = "python \"Database\\displayCurrentFlights.py\" \"" + dateOfFlight + "\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");
        }
        catch (const exception& e) {
            cout << "Error displaying current flights: " << e.what() << endl;
        }
    }

    void displayByLocation() {
        try {
            cout << "Enter Source:\t\t";
            cin >> source;
            if (source == "0")
                throw invalid_argument("Invalid source.");

            cout << "Enter Destination:\t";
            cin >> destination;
            if (destination == "0")
                throw invalid_argument("Invalid destination.");

            string command =
                "python \"Database\\displayFlightsByLocation.py\" \"" +
                source + "\" \"" +
                destination + "\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");
        }
        catch (const exception& e) {
            cout << "Error displaying flights by location: " << e.what() << endl;
        }
    }

    string showFormatDate(int dd, int mm, int yyyy) {
        string d = (dd < 10 ? "0" : "") + to_string(dd);
        string m = (mm < 10 ? "0" : "") + to_string(mm);
        string y = to_string(yyyy);
        return d + "/" + m + "/" + y;
    }

    string showFormatTime(string h, string m) {
        return h + ":" + m;
    }

    string showToday() {
        SYSTEMTIME st;
        GetLocalTime(&st);
        string dd = (st.wDay < 10 ? "0" : "") + to_string(st.wDay);
        string mm = (st.wMonth < 10 ? "0" : "") + to_string(st.wMonth);
        string yyyy = to_string(st.wYear);
        return dd + "/" + mm + "/" + yyyy;
    }

    void setAirID(int airID) { airlineId = airID; }
    void setPlaneID(int planeID) { airplaneId = planeID; }
    int getPlaneID() { return airplaneId; }
    int getID() { return id; }
    string getTakeOffTime() { return takeOffTime; }

    void captureFlight() {
        try {
            cout << endl << "Enter 0 to Exit." << endl;
            cout << "Enter Flight ID:\t#";
            cin >> id;
            if (id == 0)
                return;

            string command = "python \"Database\\checkFlightById.py\" " + to_string(id);
            FILE* pipe = _popen(command.c_str(), "r");
            if (!pipe)
                throw runtime_error("Failed to execute Python script via pipe.");

            char buffer[256];
            string line;

            while (fgets(buffer, sizeof(buffer), pipe)) {
                line = buffer;

                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                size_t pos = line.find('=');
                if (pos == string::npos) continue;

                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                key.erase(remove(key.begin(), key.end(), ' '), key.end());
                value.erase(remove(value.begin(), value.end(), ' '), value.end());

                if (key == "AIRLINE_ID") airlineId = stoi(value);
                else if (key == "AIRPLANE_ID") airplaneId = stoi(value);
                else if (key == "SOURCE") source = value;
                else if (key == "DESTINATION") destination = value;
                else if (key == "DATE") dateOfFlight = value;
                else if (key == "TIME") takeOffTime = value;
            }

            int closeStatus = _pclose(pipe);
            if (closeStatus != 0)
                throw runtime_error("Error closing Python pipe.");

            system("cls");
            cout << "---------------------------------------------------------------------------------" << endl;
            cout << "Flight-ID#:\t\t" << id << endl;
            cout << "Airline-ID#:\t\t" << airlineId << endl;
            cout << "Airplane-ID#:\t\t" << airplaneId << endl;
            cout << "Source:\t\t\t" << source << endl;
            cout << "Destination\t\t" << destination << endl;
            cout << "Date Of Flight:\t\t" << dateOfFlight << endl;
            cout << "Take Off Time\t\t" << takeOffTime << endl;
            cout << "---------------------------------------------------------------------------------" << endl;
        }
        catch (const exception& e) {
            cout << "Error capturing flight: " << e.what() << endl;
        }
    }
};

class Ticket : public Module {
public:
    int id;
    int flightId;
    int passengerId;
    string seatCode;
    string price;
    string dateOfBooking;
    bool status;

    void create() override {
        try {
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

            if (cin.fail() || id != 1)
                throw invalid_argument("Ticket creation canceled or invalid input.");

            saveToDatabase();
            getch();
        }
        catch (const exception& e) {
            cout << "Error creating ticket: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void saveToDatabase() {
        try {
            string command =
                "python \"Database\\createTicketInfo.py\" \"" +
                to_string(flightId) + "\" \"" +
                to_string(passengerId) + "\" \"" +
                seatCode + "\" \"" +
                price + "\" \"" +
                dateOfBooking + "\" \"" +
                to_string(status) + "\"";

            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Failed to execute Python script.");

            cout << "Continue: ";
        }
        catch (const exception& e) {
            cout << "Error saving ticket: " << e.what() << endl;
        }
    }

    void readByID() override {
        try {
            cout << "Enter Ticket-ID:\t#";
            cin >> id;
            if (cin.fail() || id <= 0)
                throw invalid_argument("Invalid Ticket ID.");

            string command = "python \"Database\\readTicketById.py\" " + to_string(id);
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            getch();
        }
        catch (const exception& e) {
            cout << "Error reading ticket: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void readByPassengerID() {
        try {
            cout << "Enter Passenger-ID:\t#";
            cin >> passengerId;
            if (cin.fail() || passengerId <= 0)
                throw invalid_argument("Invalid Passenger ID.");

            string command = "python \"Database\\displayTicketsByPassengerId.py\" " + to_string(passengerId);
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            getch();
        }
        catch (const exception& e) {
            cout << "Error reading tickets: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getch();
        }
    }

    void display() override {
        try {
            string command = "python \"Database\\displayTicketsInfo.py\"";
            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Python script failed.");

            cout << "Continue: ";
            getch();
        }
        catch (const exception& e) {
            cout << "Error displaying tickets: " << e.what() << endl;
            getch();
        }
    }

    void cancel() {
        cout << "FEATURE UNDER DEVELOPMENT..." << endl;
    }

    void generateTicket(string name, string flightCodeID, string takeOffTime, string ticketNo) {
        try {
            string command =
                "python \"Database\\ticketGeneration.py\" \"" +
                name + "\" " +
                flightCodeID + " " +
                seatCode + " \"" +
                dateOfBooking + "\" \"" +
                takeOffTime + "\" " +
                ticketNo;

            int result = system(command.c_str());
            if (result != 0)
                throw runtime_error("Error generating ticket PDF.");
            
            cout << "Ticket PDF generated successfully." << endl;
            getch();
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            getch();
        }
    }

    void captureTicket(int input) {
        try {
            id = input;
            string command = "python \"Database\\checkTicketById.py\" " + to_string(id);
            FILE* pipe = _popen(command.c_str(), "r");
            if (!pipe)
                throw runtime_error("Failed to execute Python script via pipe.");

            char buffer[256];
            string line;

            while (fgets(buffer, sizeof(buffer), pipe)) {
                line = buffer;

                line.erase(remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(remove(line.begin(), line.end(), '\r'), line.end());

                size_t pos = line.find('=');
                if (pos == string::npos) continue;

                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                key.erase(remove(key.begin(), key.end(), ' '), key.end());
                value.erase(remove(value.begin(), value.end(), ' '), value.end());

                if (key == "TICKET_ID" && !value.empty()) id = stoi(value);
                else if (key == "SEAT") seatCode = value;
                else if (key == "FLIGHT_ID" && !value.empty()) flightId = stoi(value);
                else if (key == "PASSENGER_ID" && !value.empty()) passengerId = stoi(value);
            }

            int closeStatus = _pclose(pipe);
            if (closeStatus != 0)
                throw runtime_error("Error closing Python pipe.");

            cout << "Ticket data loaded successfully. ID# " << id << endl;
        }
        catch (const exception& e) {
            cout << "Error capturing ticket: " << e.what() << endl;
        }
    }

    int getID() {
        return id;
    }
};

class Interface {   
	private:
		bool privillege;
	public:
		Interface()
		{
			SetConsoleTitle("AirFare Booking System - ABS"); 												// to set console title
			HWND hwnd = GetConsoleWindow(); 																// to get console window
			HICON icon = (HICON)LoadImage(NULL,"airplane.ico",IMAGE_ICON,32, 32,LR_LOADFROMFILE);			// to set console icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
			SendMessage(hwnd, WM_SETICON, ICON_BIG,   (LPARAM)icon);
			ShowWindow(hwnd, SW_MAXIMIZE); 																	// to maximize console window
		}
		void appThread();
	protected:
		/* INTERFACE FUNCTIONS */
		void setColor() {
			system("color 4F");
		}
	 	void getTime() {
			time_t now = time(0);          														// to get current time
    		char* dt = ctime(&now);        														// to convert time to string
    		cout << "\t\t\t     " << dt;														// to display time on screeen
		}
		void setDefault() {
			setColor();
			getTime();
		}
		void setSubColor() {
			system("color 3F");		// BLUE COLOUR BACKGROUND		
		}
		void setThirdColor() {
			system("color 2F");
		}
		void clear() {
			system("cls");
		}
		void create() {
			cout << "Creating Interface..." << endl;
		}
		void readByID() {
			cout << "Reading Variables..." << endl;
		}
		void display() {
		    cout << "Loading: ";
		
		    int total = 50;              // length of bar
		    int delay = 5000 / total;    // total time = 5 seconds
		
		    for (int i = 0; i <= total; i++) {
		        cout << "\rLoading: [";
		
		        for (int j = 0; j < i; j++)
		            cout << "#";
		
		        for (int j = i; j < total; j++)
		            cout << " ";
		
		        cout << "] " << (i * 2) << "%";
		        cout.flush();
		
		        this_thread::sleep_for(chrono::milliseconds(delay));
		    }
		
		    cout << endl << "Successful! Press Enter: ";
		}
		void setup() {
			cout << "Getting Things Started..." << endl;
			setColor();
			create();
			display();
			getch();
			clear();
		}
		char mainMenu();
		bool adminLogin();
		string inputPassword();
		/* ENTITY MODULES */
		void flightModule(bool);
		void passengerModule();
		void airlineModule();
		void bookingModule();
		void ticketModule(bool);
		void adminModule();
};

void Interface::appThread() {
	setup();
	while(true)
	{
		char select = mainMenu();
		clear();
		if(select == '1')
		{
			cout << "-> Flights Module\a" << endl;
			flightModule(false);
		}
		else if(select == '2')
		{
			cout << "Passengers Module\a" << endl;
			passengerModule();
		}
		else if(select == '3')
		{
			cout << "Airline Module\a" << endl;
			airlineModule();
		}
		else if(select == '@')
		{
			cout << "Admins Module\a" << endl;
			adminModule();
		}
		else if(select == 'e')
		{
			cout << "Exiting Application\a" << endl;
			/* END CREDITS HERE */
			cout << "With Combined Efforts of All Group Members, We created a system of understanding and value." << endl;
			cout << "Lead by Syed Mubazir Haider\a" << endl;
			cout << "Exit App -> ";
			getch();
			ExitProcess(0);
		}
		else
		{
			continue;
		}
		clear();
	}
}

char Interface::mainMenu() {
	setDefault();
	cout << string(81, '-') << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t     AIR-FARE BOOKING SYSTEM\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << string(81, '-') << endl << endl;
	cout << "\t\t\t\t    MAIN MENU" << endl;
	cout << " Type @ -> Admin\t\t\t\t\t\t  Type e -> Exit" << endl;
	cout << string(81, '-') << endl << endl;
	cout << "\t\t\t\t1. Flights Dashboard" << endl << endl;
	cout << "\t\t\t\t2. Passenger Records" << endl << endl;
	cout << "\t\t\t\t3. Airline Information" << endl << endl;
	cout << endl << endl << endl << endl << endl << endl;
	char option = getch();
	return option;
}

bool Interface::adminLogin() {
    string userDB="admin", passwordDB="1234";
    string userName, password;
    bool auth = false;
    cout << "\t\t\t----------------------------------------------------------------"<<endl;
    cout << "\t\t\t------------------  AirFare Booking System  --------------------"<<endl;
    cout << "\t\t\t----------------------------------------------------------------"<<endl;
    cout << "\t\t\t------------------------- LOGIN PAGE ---------------------------"<<endl;
    cout << "\t\t\t----------------------------------------------------------------"<<endl;
	cout << "\t\t\tEnter your Credentials :"<<endl<<endl;
    cout << "\t\t\tUsername : ";
    cin >> userName;
    password = inputPassword();
    cout << endl;
    if(userName== userDB && password==passwordDB)
	{
        cout << "\t\t\tLogin Successful\a" << endl;
        auth = true;
    }
	else
	{
    	cout << "\t\t\tInvalid Username or Password\a" << endl;
    }
    getch();
    return auth;
}

string Interface::inputPassword() {
	string password = "";
    cout << "\t\t\tPassword : ";
    char ch;
    while ((ch = _getch()) != '\r') {  // Stop at Enter key
        if (ch == '\b') {  // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // remove last * from screen
            }
        } else {
            password.push_back(ch);
            cout << '*'; // show *
        }
    }
    cout << endl;
    return password;
}

void Interface::adminModule() {
	privillege = adminLogin();
	if(privillege)
	{
		cout << "Admin Privellege Accessed..." << endl;
	}
	else
	{
		return;
	}
}

void Interface::passengerModule() {
	while(true)
	{
		clear();
		setColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tPASSENGERS RECORD\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\t1. Enter New Passenger Info" << endl << endl;
		cout << "\t\t\t2. Search Passenger by ID#" << endl << endl;
		cout << "\t\t\t3. Search Passenger by Name" << endl << endl;
		cout << "\t\t\t4. Display All Passengers Records" << endl << endl;
		cout << "\t\t\t5. Manage Passenger Tickets" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Passenger p;
		if(option == '1')
		{
			cout << "-> Entering New Passenger Info" << endl << endl;
			p.create();
		}
		else if(option == '2')
		{
			cout << "-> Searching Passenger by ID#" << endl << endl;
			p.readByID();
		}
		else if(option == '3')
		{
			cout << "-> Searching Passenger by Name" << endl << endl;
			p.readByName();
		}
		else if(option == '4')
		{
			cout << "-> Displaying All Passengers Records" << endl << endl;
			p.display();
		}
		else if(option == '5')
		{
			/*
			cout << "Updating Passengers Flight to Today" << endl << endl;
			Passenger p;
			p.updateLastFlight();
			getch();
			*/
			cout << "-> Opening Tickets Module" << endl << endl;
			ticketModule(false);
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			continue;
		}
	}	
}

void Interface::flightModule(bool auth) {
	while(true)
	{
		clear();
		setSubColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tFLIGHTS DASHBOARD\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		if(auth)
		{
			cout << "\t\t\tA. Add New Flight" << endl << endl;			
		}
		cout << "\t\t\t1. Display Available Flights" << endl << endl;
		cout << "\t\t\t2. Search Flights by Location" << endl << endl;
		cout << "\t\t\t3. Display All Flights Record" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Flight f;
		Airline air;
		Airplane plane;
		if(option == 'A' )
		{
			cout << "Adding New Flight" << endl << endl;
			air.display();
			air.readByID();
			clear();
			plane.setID(air.getID());
			plane.display();
			int planeID;
			cout << "Enter Plane ID: #";
			cin >> planeID;
			f.setAirID(air.getID());
			f.setPlaneID(planeID);
			f.create();
		}
		if(option == '1')
		{
			cout << "Displaying Available Flights" << endl << endl;
			f.displayCurrent();
			bookingModule();
		}
		else if(option == '2')
		{
			cout << "Searching Flights by Location" << endl << endl;
			f.displayByLocation();
			bookingModule();
		}
		else if(option == '3')
		{
			cout << "Displaying All Flights" << endl << endl;
			f.display();
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			continue;
		}
	}	
}

void Interface::airlineModule() {
	if(!adminLogin())
	{
		return;
	}
	while(true)
	{
		clear();
		setColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tAIRLINE ADMINISTRATION\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\t1. New Airline Info" << endl << endl;
		cout << "\t\t\t2. New Airplane Info" << endl << endl;
		cout << "\t\t\t3. Show Airline/Airplane Info" << endl << endl;
		cout << "\t\t\t4. Display All Airline Records" << endl << endl;
		cout << "\t\t\t5. Manage Airline Flights" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Airline air;
		Airplane plane;
		if(option == '1')
		{
			cout << "-> Entering New Airline Info" << endl << endl;
			air.create();
		}
		else if(option == '2')
		{
			cout << "Entering New Airplane Info" << endl << endl;
			air.display();
			plane.create();
		}
		else if(option == '3')
		{
			cout << "-> Viewing Airline Info with Airplanes" << endl << endl;
			air.display();
			air.readByID();
			plane.setID(air.getID());
			plane.display();
		}
		else if(option == '4')
		{
			cout << "-> Displaying All Airline Records" << endl << endl;
			air.display();
		}
		else if(option == '5')
		{
			cout << "Opening Flights Module with Create Authority" << endl << endl;
			flightModule(true);
		}
		else if(option == '6')
		{
			plane.mapAirplane();
			getch();
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			continue;
		}
	}	
}

void Interface::bookingModule() {
		Passenger p;
		Airline a;
		Ticket t;
		Flight f;
		Airplane plane;
		f.captureFlight();
		if(f.getID() == 0)
			return;
		cout << "Flight ID # " << f.getID() << endl;
		t.flightId = f.getID();
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\tB. Book Ticket Reservation" << endl << endl;
		cout << "\t\t\tM. Manage Ticket Bookings" << endl << endl;
		cout << "\t\t\tR. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getche();
		if(option == 'B' || option == 'b') {
			cout << endl;
			if(p.checkOrCreate())
			{
				cout << "LETS BOOK TICKET...\a" << endl;
				cout << "Enter Passenger-ID: #";
				cin >> t.passengerId;
				p.updateLastFlight();
			}
			else
			{
				cout << "OOPS! REGISTER YOURSELF QUICK...\a" << endl;
				p.create();
				t.passengerId = p.getID();
			}
			plane.captureAirplane(f.getPlaneID());
			a.captureAirline(plane.getAirlineID());
			clear();
			cout << "Select Seat on Airplane:" << endl;
			plane.mapAirplane();
		    cout << endl << "Enter Seat Code (eg. A12): ";
		    cin >> t.seatCode;
		    cout << "Enter Ticket Price: ";
		    cin >> t.price;
		    clear();
		    t.dateOfBooking = p.showToday();
		    t.status = true;
			cout << "Opening Ticket Module with Create Authority" << endl << endl;
			t.create();
			cout << endl << "Generate Ticket: ";
			getch();
			string nameInput;
			cin.ignore();
			cout << endl << "Please Write Name for Ticket: ";
			getline(cin, nameInput);
			if(nameInput == "")
			{
				cout << endl << "Please Write Name for Ticket: ";
				getline(cin, nameInput);	
			}
			string ticjet = "95472";
			string fglight = a.getCode() + "-" + to_string(f.getID());
			t.generateTicket(nameInput, fglight, f.getTakeOffTime(), ticjet);
		}
		else if(option == 'M' || option == 'm') {
			cout << "Opening Ticket Module" << endl << endl;
			ticketModule(false);
		}
		else if(option == 'R' || option == 'r') {
			return;
		}
		else {
			return;
		}
}

void Interface::ticketModule(bool auth) {
	while(true)
	{
		clear();
		setThirdColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tTICKETING PORTAL\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\t1. Search Ticket By ID#" << endl << endl;
		cout << "\t\t\t2. Search Tickets By Passenger" << endl << endl;
		cout << "\t\t\t3. Cancel Ticket Reservation" << endl << endl;
		cout << "\t\t\t4. Display All Ticket Records" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Ticket t;
		if(option == '1')
		{
			cout << "Searching Ticket By ID#" << endl << endl;
			t.readByID();
		}
		else if(option == '2')
		{
			cout << "Searching Tickets By Passenger ID#" << endl << endl;
			t.readByPassengerID();
		}
		else if(option == '3')
		{
			cout << "Cancelling Ticket Reservation" << endl << endl;
			t.cancel();
		}
		else if(option == '4')
		{
			cout << "Displaying All Ticket Records" << endl << endl;
			t.display();
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			return;
		}
	}	
}

/* Running Environment */
int main()
{
	Interface user;
	user.appThread();
}

/**********************************************************
             REQUIREMENTS TO RUN
1) Windows OS with C++ compiler (C++11+).

2) Python 3.x installed and in system PATH.

3) Database ready (MySQL) with required tables.

4) Database folder containing all Python scripts.
0
5) Permissions to run Python scripts from the C++ program.
**********************************************************/