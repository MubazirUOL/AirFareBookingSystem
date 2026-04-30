#include <cstdlib>
#include <string>
using namespace std;
int main()
{
	/*string source = "\"New York\"";        // wrap in quotes if space*/
    string flightID = "3";
    string passengerID = "1";
    string source = "LHR";
    string destination = "KHI";
    string seatRow = "4";
    string seatColumn = "8";
    string price = "15000";

    // Build the command to call Python script with arguments
    string command = "python createTicketInfo.py " + flightID + " " + passengerID + " " + source + " " + destination + " " + seatRow + " " + seatColumn + " " + price;

    // Execute the Python script
    system(command.c_str());

    return 0;
}
