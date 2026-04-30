#include <cstdlib>
#include <string>
using namespace std;
int main()
{
	/*string source = "\"New York\"";        // wrap in quotes if space*/
    string airlineID = "3";
    string airplaneID = "6";
    string source = "LHR";
    string destination = "SGD";
    string dateOfFlight = "20-Dec-2025";
    string takeOffTime = "14:00";
    string arrivalTime = "Evi";
    string flightStatus = "1";

    // Build the command to call Python script with arguments
    string command = "python createFlightInfo.py " + airlineID + " " + airplaneID + " " + source + " " + destination + " " + dateOfFlight + " " + takeOffTime + " " + arrivalTime + " " + flightStatus;

    // Execute the Python script
    system(command.c_str());

    return 0;
}
