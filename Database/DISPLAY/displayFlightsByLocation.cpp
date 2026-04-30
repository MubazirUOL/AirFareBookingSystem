#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    string command = "python displayFlightsByLocation.py LHR KHI";

    system(command.c_str());

    return 0;
}