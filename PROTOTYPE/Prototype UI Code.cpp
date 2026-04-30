#include <iostream>
#include <windows.h>
#include <cstring>
#include <ctime>
using namespace std;

void defaultWindowSetting() {
	SetConsoleTitle("AirFare Ticketing"); // to set console title
	HWND hwnd = GetConsoleWindow(); // to get console window
	ShowWindow(hwnd, SW_MAXIMIZE); // to maximize console window
	system("color 4F");	// to color console window
	time_t now = time(0);          // current time as time_t
    char* dt = ctime(&now);        // convert to string
    cout << "\t\t\t     " << dt;	
}
void mainMenu()
{
	cout << string(81, '-') << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t     AIR-FARE BOOKING SYSTEM\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << string(81, '-') << endl << endl;
	cout << "\t\t\t\t    MAIN MENU" << endl << endl;
	cout << string(81, '-') << endl << endl;
	cout << "\t\t\t\t1. Flights Dashboard" << endl << endl;
	cout << "\t\t\t\t2. Passenger Records" << endl << endl;
	cout << "\t\t\t\t3. Airline Information" << endl << endl;
	cout << endl << endl << endl << endl << endl << endl;	
}

int main() {
	// defaultWindowSetting();
	// mainMenuContent();
	/* // One more way to get time using windows.h library
		SYSTEMTIME st;
    	GetLocalTime(&st);
    	cout << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl;
	*/

    return 0;
}