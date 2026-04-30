#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdexcept>
#include <algorithm>
#include <string>
#include "Module.h"
using namespace std;

class Flight:public Module {
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
			cout << "Enter Source City Code:\t\t";
			cin >> source;
			if(source == "0" || source == "")
				return;
			cout << "Enter Destination City Code:\t";
			cin >> destination;
			if(destination == "0" || destination == "")
				return;
			int d, m, y;
			cout << "Enter Date Of Flight:" << endl;
			cout << "Enter Day (1 - 31)\t:";
			cin >> d;
			if(d == 0)
				return;
			cout << "Enter Month (1 - 12):\t";
			cin >> m;
			if(m == 0)
				return;
			cout << "Enter Year (20xx):\t";
			cin >> y;
			if(y == 0)
				return;
				
			if(!(d >= 1 && d <= 31))
			{
				cout << "Wrong Day..." << endl;
				getch();
				return;
			}
			if(!(m >= 1 && d <= 12))
			{
				cout << "Wrong Month..." << endl;
				getch();
				return;
			}
			if(!(y >= 2026))
			{
				cout << "Wrong Year..." << endl;
				getch();
				return;
			}
			
			dateOfFlight = showFormatDate(d,m,y);
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
		void saveToDatabase() {
		    string command =
	        "python \"Database\\createFlightInfo.py\" \"" +
	        to_string(airlineId) + "\" \"" +
	        to_string(airplaneId) + "\" \"" +
	        source + "\" \"" +
	        destination + "\" \"" +
	        dateOfFlight + "\" \"" +
	        takeOffTime + "\"";
		    system(command.c_str());
		    cout << "Continue: ";
		}
		void readByID() override {
			cout << "Enter Flight ID: ";
			cin >> id;
			/* DATA INTEGRATION */
		}
		void display() override {
			string command = "python \"Database\\displayFlightsInfo.py\" \"";
		    system(command.c_str());
		    cout << "Continue: ";
		    getch();
		}
		void displayCurrent() {
			dateOfFlight = showToday();
		    string command =
		        "python \"Database\\displayCurrentFlights.py\" \"" +
		        dateOfFlight + "\"";
		    system(command.c_str());
		}
		void displayByLocation() {
			cout << "Enter Source:\t\t";
			cin >> source;
			if(source == "0")
				return;
			cout << "Enter Destination:\t";
			cin >> destination;
			if(destination == "0")
				return;
		    string command =
		        "python \"Database\\displayFlightsByLocation.py\" \"" +
		        source + "\" \"" +
		        destination + "\"";
		    system(command.c_str());
		}
		string showFormatDate(int dd, int mm, int yyyy) {
			string d , m , y;
			if(dd / 10 == 0)
		    	d = "0" + to_string(dd);
		    else
		    	d = to_string(dd);
		    if(mm / 10 == 0)
		    	m = "0" + to_string(mm);
		    else
		    	m = to_string(mm);
		    y = to_string(yyyy);
			return d + "/" + m + "/" + y;
		}
		string showFormatTime(string h, string m) {
		    return h + ":" + m;
		}
		string showToday() {
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
		void setAirID(int airID) {
			airlineId = airID;
		}
		void setPlaneID(int planeID) {
			airplaneId = planeID;
		}
		int getPlaneID() {
			return airplaneId;
		}
		int getID(){
			return id;
		}
		string getTakeOffTime() {
			return takeOffTime;
		}
		void captureFlight() {
			cout << endl << "Enter 0 to Exit." << endl;
		    cout << "Enter Flight ID:\t#";
		    cin >> id;
		    if(id == 0)
		    	return;
		    string command = "python \"Database\\checkFlightById.py\" " + to_string(id);
		
		    FILE* pipe = _popen(command.c_str(), "r");
		    if (!pipe) {
		        cout << "Failed to execute Python script\n";
		        return;
		    }
		
		    char buffer[256];
		    string line;
		
		    while (fgets(buffer, sizeof(buffer), pipe))
			{
			    line = buffer;
			
			    // Remove \n and \r
			    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
			    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
			
			    size_t pos = line.find('=');
			    if (pos == string::npos) continue;
			
			    string key   = line.substr(0, pos);
			    string value = line.substr(pos + 1);
			
			    // Trim spaces
			    key.erase(remove(key.begin(), key.end(), ' '), key.end());
			    value.erase(remove(value.begin(), value.end(), ' '), value.end());
			
			    if (key == "AIRLINE_ID")
			        airlineId = stoi(value);
			
			    else if (key == "AIRPLANE_ID")
			        airplaneId = stoi(value);
			
			    else if (key == "SOURCE")
			        source = value;
			
			    else if (key == "DESTINATION")
			        destination = value;
			
			    else if (key == "DATE")
			        dateOfFlight = value;
			
			    else if (key == "TIME")
			        takeOffTime = value;
			}

		
		    _pclose(pipe);
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
};