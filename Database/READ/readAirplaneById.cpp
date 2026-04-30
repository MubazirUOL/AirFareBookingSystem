#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    string airplaneID = "4";

    string command = "python readAirplaneById.py " + airplaneID;

    system(command.c_str());

    return 0;
}
