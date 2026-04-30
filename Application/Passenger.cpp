#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdexcept>

using namespace std;

#include <string>
#include "Module.h"

using namespace std;

class Passenger : public Module {
	private:
	    int id;
	    string cnic;
	    string name;
	    string contact;
	    string lastFlight;
	
	public:
	    string showToday();
	    void create() override;
	    void readByID() override;
	    void readByName();
	    void display() override;
	    void updateLastFlight();
	    void saveToDatabase();
	    bool checkOrCreate();
	    int getID();
	    string getName();
};

string Passenger::showToday() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    string dd   = to_string(st.wDay);
    string mm   = to_string(st.wMonth);
    string yyyy = to_string(st.wYear);
    if(st.wDay / 10 == 0)
    	dd = "0" + dd;
    if(st.wMonth / 10 == 0)
    	mm = "0" + mm;
    return dd + "/" + mm + "/" + yyyy;
}

void Passenger::create() {
    cout << "Enter Passenger CNIC:\t";
    cin >> cnic;
    if(cnic == "0")
    	return;

    cout << "Enter Passenger Name:\t";
    cin.ignore();
    getline(cin, name);
    if(name == "0")
    	return;

    cout << "Enter Contact Number:\t";
    cin >> contact;
    if(contact == "0")
    	return;

    lastFlight = showToday();
    if(cnic == "" || name == "" || contact == "" || lastFlight == "")
    {
    	cout << "ERROR..." << endl;
    	return;
	}
    saveToDatabase();
    getch();
}

void Passenger::readByID() {
    cout << "Enter Passenger-ID:\t#";
    cin >> id;
    string command = "python \"Database\\readPassengerById.py\" " + to_string(id);
	system(command.c_str());
	getch();
}

void Passenger::readByName() {
    cout << "Enter Name: ";
    cin >> name;
    if(name == "")
    	return;
	string command = "python \"Database\\readPassengerByName.py\" \"" +
	name + "\"";
    system(command.c_str());
    cout << "Continue: ";
    getch();
}

void Passenger::display() {
    string command = "python \"Database\\displayPassengersInfo.py\" \"";
    system(command.c_str());
    cout << "Continue: ";
    getch();
}

void Passenger::updateLastFlight() {
	cout << "Passenger CNIC to be updated: -> " << cnic << endl;
    lastFlight = showToday();
    string command = "python \"Database\\updatePassengerLastFlight.py\" " + cnic + " " + lastFlight;
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Updated Successfully!" << endl;
    } else {
        cout << "Python script failed with code " << result << endl;
    }
}

void Passenger::saveToDatabase() {
    string command =
        "python \"Database\\createPassengerInfo.py\" \"" +
        cnic + "\" \"" +
        name + "\" \"" +
        contact + "\" \"" +
        lastFlight + "\"";

    system(command.c_str());
    cout << "Continue: ";
}

int Passenger::getID() {
	return id;
}

string Passenger::getName() {
	return name;
}

bool Passenger::checkOrCreate() {
    cout << "Enter Passenger-CNIC:\t#";
    cin >> cnic;

    string command = "python \"Database\\checkPassengerByCnic.py\" " + cnic;

    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        cout << "Failed to run Python script\n";
        return false;
    }

    char buffer[256];
    string output = "";

    while (fgets(buffer, sizeof(buffer), pipe))
        output += buffer;

    _pclose(pipe);

    // ---- Decision ----
    if (output.find("FIND") != string::npos)
    {
        cout << "Passenger already exists.\n";
        cout << output << endl;
        return true;
    }
    else if (output.find("NOT_FOUND") != string::npos)
    {
        cout << "Passenger not found. Creating new passenger...\n";
        return false;
    }
    else
    {
        cout << "Unexpected error from Python\n";
    }
    getch();
    return false;
}