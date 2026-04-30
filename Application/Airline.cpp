#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <stdexcept>
using namespace std;

#include <string>
#include "Module.h"

class Airline:public Module {
	private:
		int id;
		string title;
		string country;
		string code;
	public:
		void create() {
			cout<<"Enter Airline Title:\t";
			getline(cin, title);
			if(title == "0" || title == "")
    			return;
    			
			cout<<"Enter Country Name:\t";
			cin>>country;
			if(country == "0")
    			return;
    			
			cout<<"Enter Airline Code:\t";
			cin>>code;
			if(code == "0")
    			return;
    		
		    if(title == "" || country == "" || code == "")
		    {
		    	cout << "ERROR..." << endl;
		    	return;
			}
		    saveToDatabase();
		    getch();
		}
		void readByID() {
			cout<<"Enter Airline ID: #";
			cin>>id;
		    string command = "python \"Database\\readAirlineById.py\" " + to_string(id);
			system(command.c_str());
		    cout << "Continue: ";
			getch();
		}
		void display() {
			string command = "python \"Database\\displayAirlinesInfo.py\" \"";
		    system(command.c_str());
		    cout << "Continue: ";
		    getch();
		}
		void saveToDatabase() {
		    string command =
		        "python \"Database\\createAirlineInfo.py\" \"" +
		        title + "\" \"" +
		        country + "\" \"" +
		        code + "\"";
		    system(command.c_str());
		    cout << "Continue: ";
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
		        if (key == "TITLE") {
		            title = value;
		        }
		        else if (key == "COUNTRY") {
		            country = value;
		        }
		        else if (key == "CODE") {
		            code = value;
		        }
		    }
		
		    _pclose(pipe);
		
		    cout << "Airline data loaded successfully. Code: " << code << endl;
		}
};