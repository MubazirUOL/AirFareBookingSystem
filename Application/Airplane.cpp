#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstdio> 
#include <conio.h>
#include "Module.h"

using namespace std;

class Airplane:public Module {
	private:
		int id;
		int airlineId;
		string model;
		int rows;
		int columns;
	public:
		void create() {
			cout << "Enter Airline ID:\t";
			cin >> airlineId;
			if(airlineId == 0)
				return;
			cin.ignore();
			cout << "Enter Model Title:\t";
			getline(cin, model);
			if(model == "0")
				return;
			cout << "Enter Total Rows:\t";
			cin >> rows;
			cout << "Enter Total Column:\t";
			cin >> columns;
			saveToDatabase();
			getch();
		}
		void readByID() {
			cout << "NOT AVAILABLE..." << endl;
		}
		void display() {
			string command = "python \"Database\\displayAirplanesInfo.py\" " + to_string(airlineId);
			system(command.c_str());
			getch();
		}
		void saveToDatabase() {
		    string command =
		        "python \"Database\\createAirplaneInfo.py\" \"" +
		        to_string(airlineId) + "\" \"" +
		        model + "\" \"" +
		        to_string(rows) + "\" \"" +
		        to_string(columns) + "\"";
		    system(command.c_str());
		    cout << "Continue: ";
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
			try
			{
				int row = rows;
				int column = columns;
				char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
				int dash = 0;
				dash = (column * 17) - (column - 1);
				cout << string(dash, '-') << endl;
				for(int i=0; i < row; i++)
				{
					for(int j = 1; j <= column; j++)
					{
						cout << "|\t" << alphabet[i] << j << "\t|";
						if(j == column)
						{
							cout << endl;
						}
					}
					cout << string(dash, '-') << endl;
				}
			}
			catch(...)
			{
				cout << "Stop. here. " << endl;
			}
		}
		void captureAirplane(int input) {
		    id = input;
		    string command = "python \"Database\\checkAirplaneById.py\" " + to_string(id);
		
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
		
		    _pclose(pipe);
		
		    cout << "Airplane data loaded successfully.\n";
		}
};