#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    string ticketID = "4";

    string command = "python readTicketById.py " + ticketID;

    system(command.c_str());

    return 0;
}
