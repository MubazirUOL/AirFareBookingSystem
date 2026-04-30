#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    string passengerID = "2";

    string command = "python readPassengerById.py " + passengerID;

    system(command.c_str());

    return 0;
}
