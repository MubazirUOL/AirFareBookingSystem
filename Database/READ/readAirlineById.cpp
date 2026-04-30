#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    string airlineID = "1";
    string command = "python readAirlineById.py " + airlineID;
    system(command.c_str());
    return 0;
}