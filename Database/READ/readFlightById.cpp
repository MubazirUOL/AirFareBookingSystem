#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    string flightID = "3";

    string command = "python readFlightById.py " + flightID;

    system(command.c_str());

    return 0;
}
