#include <cstdlib>
#include <string>
using namespace std;
int main()
{
    string cnic = "3520222222222";
    string name = "\"Turab Aamer\"";
    string contact = "032465798123";
    string lastFlight = "25/12/2025";

    // Build the command to call Python script with arguments
    string command = "python createPassengerInfo.py " + cnic + " " + name + " " + contact + " " + lastFlight;

    // Execute the Python script
    system(command.c_str());

    return 0;
}
