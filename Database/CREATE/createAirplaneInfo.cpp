#include <cstdlib>
#include <string>
using namespace std;
int main() {
	
    string airlineID = "3";
    string name = "PK-110";
    string seatRow = "10";
    string seatColumn = "8";
    string originDate = "2025-12-17";
    string operateStatus = "1";

    // Build the command to call Python script with arguments
    string command = "python createAirplaneInfo.py " + airlineID + " " + name + " " + seatRow + " " + seatColumn + " " + originDate + " " + operateStatus;

    // Execute the Python script
    system(command.c_str());

    return 0;
}
