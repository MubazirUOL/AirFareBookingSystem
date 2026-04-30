#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <windows.h>
#include <conio.h>
/* ENTITY CLASSES */
#include "Airline.cpp"
#include "Airplane.cpp"
#include "Flight.cpp"
#include "Passenger.cpp"
#include "Ticket.cpp"

using namespace std;

class Interface {   
	private:
		bool privillege;
	public:
		Interface()
		{
			SetConsoleTitle("AirFare Booking System - ABS"); 												// to set console title
			HWND hwnd = GetConsoleWindow(); 																// to get console window
			HICON icon = (HICON)LoadImage(NULL,"airplane.ico",IMAGE_ICON,32, 32,LR_LOADFROMFILE);			// to set console icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
			SendMessage(hwnd, WM_SETICON, ICON_BIG,   (LPARAM)icon);
			ShowWindow(hwnd, SW_MAXIMIZE); 																	// to maximize console window
		}
		void appThread();
	protected:
		/* INTERFACE FUNCTIONS */
		void setColor() {
			system("color 4F");
		}
	 	void getTime() {
			time_t now = time(0);          														// to get current time
    		char* dt = ctime(&now);        														// to convert time to string
    		cout << "\t\t\t     " << dt;														// to display time on screeen
		}
		void setDefault() {
			setColor();
			getTime();
		}
		void setSubColor() {
			system("color 3F");		// BLUE COLOUR BACKGROUND		
		}
		void setThirdColor() {
			system("color 2F");
		}
		void clear() {
			system("cls");
		}
		void create() {
			cout << "Creating Interface..." << endl;
		}
		void readByID() {
			cout << "Reading Variables..." << endl;
		}
		void display() {
		    cout << "Loading: ";
		
		    int total = 50;              // length of bar
		    int delay = 5000 / total;    // total time = 5 seconds
		
		    for (int i = 0; i <= total; i++) {
		        cout << "\rLoading: [";
		
		        for (int j = 0; j < i; j++)
		            cout << "#";
		
		        for (int j = i; j < total; j++)
		            cout << " ";
		
		        cout << "] " << (i * 2) << "%";
		        cout.flush();
		
		        this_thread::sleep_for(chrono::milliseconds(delay));
		    }
		
		    cout << endl << "Successful! Press Enter: ";
		}
		void setup() {
			/*
			cout << "Getting Things Started..." << endl;
			setColor();
			create();
			display();
			getch();
			clear();
			*/
		}
		char mainMenu();
		bool adminLogin();
		string inputPassword();
		/* ENTITY MODULES */
		void flightModule(bool);
		void passengerModule();
		void airlineModule();
		void bookingModule();
		void ticketModule(bool);
		void adminModule();
};

void Interface::appThread() {
	setup();
	while(true)
	{
		char select = mainMenu();
		clear();
		if(select == '1')
		{
			cout << "-> Flights Module\a" << endl;
			flightModule(false);
		}
		else if(select == '2')
		{
			cout << "Passengers Module\a" << endl;
			passengerModule();
		}
		else if(select == '3')
		{
			cout << "Airline Module\a" << endl;
			airlineModule();
		}
		else if(select == '@')
		{
			cout << "Admins Module\a" << endl;
			adminModule();
		}
		else if(select == 'e')
		{
			cout << "Exiting Application\a" << endl;
			/* END CREDITS HERE */
			cout << "With Combined Efforts of All Group Members, We created a system of understanding and value." << endl;
			cout << "Lead by Syed Mubazir Haider\a" << endl;
			cout << "Exit App -> ";
			getch();
			ExitProcess(0);
		}
		else
		{
			continue;
		}
		clear();
	}
}

char Interface::mainMenu() {
	setDefault();
	cout << string(81, '-') << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t     AIR-FARE BOOKING SYSTEM\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
	cout << string(81, '-') << endl << endl;
	cout << "\t\t\t\t    MAIN MENU" << endl;
	cout << " Type @ -> Admin\t\t\t\t\t\t  Type e -> Exit" << endl;
	cout << string(81, '-') << endl << endl;
	cout << "\t\t\t\t1. Flights Dashboard" << endl << endl;
	cout << "\t\t\t\t2. Passenger Records" << endl << endl;
	cout << "\t\t\t\t3. Airline Information" << endl << endl;
	cout << endl << endl << endl << endl << endl << endl;
	char option = getch();
	return option;
}

bool Interface::adminLogin() {
    string userDB="admin", passwordDB="1234";
    string userName, password;
    bool auth = false;
    cout << "\t\t\t----------------------------------------------------------------"<<endl;
    cout << "\t\t\t------------------  AirFare Booking System  --------------------"<<endl;
    cout << "\t\t\t----------------------------------------------------------------"<<endl;
    cout << "\t\t\t------------------------- LOGIN PAGE ---------------------------"<<endl;
    cout << "\t\t\t----------------------------------------------------------------"<<endl;
	cout << "\t\t\tEnter your Credentials :"<<endl<<endl;
    cout << "\t\t\tUsername : ";
    cin >> userName;
    password = inputPassword();
    cout << endl;
    if(userName== userDB && password==passwordDB)
	{
        cout << "\t\t\tLogin Successful\a" << endl;
        auth = true;
    }
	else
	{
    	cout << "\t\t\tInvalid Username or Password\a" << endl;
    }
    getch();
    return auth;
}

string Interface::inputPassword() {
	string password = "";
    cout << "\t\t\tPassword : ";
    char ch;
    while ((ch = _getch()) != '\r') {  // Stop at Enter key
        if (ch == '\b') {  // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // remove last * from screen
            }
        } else {
            password.push_back(ch);
            cout << '*'; // show *
        }
    }
    cout << endl;
    return password;
}

void Interface::adminModule() {
	privillege = adminLogin();
	if(privillege)
	{
		cout << "Admin Privellege Accessed..." << endl;
	}
	else
	{
		return;
	}
}

void Interface::passengerModule() {
	while(true)
	{
		clear();
		setColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tPASSENGERS RECORD\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\t1. Enter New Passenger Info" << endl << endl;
		cout << "\t\t\t2. Search Passenger by ID#" << endl << endl;
		cout << "\t\t\t3. Search Passenger by Name" << endl << endl;
		cout << "\t\t\t4. Display All Passengers Records" << endl << endl;
		cout << "\t\t\t5. Manage Passenger Tickets" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Passenger p;
		if(option == '1')
		{
			cout << "-> Entering New Passenger Info" << endl << endl;
			p.create();
		}
		else if(option == '2')
		{
			cout << "-> Searching Passenger by ID#" << endl << endl;
			p.readByID();
		}
		else if(option == '3')
		{
			cout << "-> Searching Passenger by Name" << endl << endl;
			p.readByName();
		}
		else if(option == '4')
		{
			cout << "-> Displaying All Passengers Records" << endl << endl;
			p.display();
		}
		else if(option == '5')
		{
			/*
			cout << "Updating Passengers Flight to Today" << endl << endl;
			Passenger p;
			p.updateLastFlight();
			getch();
			*/
			cout << "-> Opening Tickets Module" << endl << endl;
			ticketModule(false);
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			continue;
		}
	}	
}

void Interface::flightModule(bool auth) {
	while(true)
	{
		clear();
		setSubColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tFLIGHTS DASHBOARD\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		if(auth)
		{
			cout << "\t\t\tA. Add New Flight" << endl << endl;			
		}
		cout << "\t\t\t1. Display Available Flights" << endl << endl;
		cout << "\t\t\t2. Search Flights by Location" << endl << endl;
		cout << "\t\t\t3. Display All Flights Record" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Flight f;
		Airline air;
		Airplane plane;
		if(option == 'A' )
		{
			cout << "Adding New Flight" << endl << endl;
			air.display();
			air.readByID();
			clear();
			plane.setID(air.getID());
			plane.display();
			int planeID;
			cout << "Enter Plane ID: #";
			cin >> planeID;
			f.setAirID(air.getID());
			f.setPlaneID(planeID);
			f.create();
		}
		if(option == '1')
		{
			cout << "Displaying Available Flights" << endl << endl;
			f.displayCurrent();
			bookingModule();
		}
		else if(option == '2')
		{
			cout << "Searching Flights by Location" << endl << endl;
			f.displayByLocation();
			bookingModule();
		}
		else if(option == '3')
		{
			cout << "Displaying All Flights" << endl << endl;
			f.display();
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			continue;
		}
	}	
}

void Interface::airlineModule() {
	if(!adminLogin())
	{
		return;
	}
	while(true)
	{
		clear();
		setColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tAIRLINE ADMINISTRATION\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\t1. New Airline Info" << endl << endl;
		cout << "\t\t\t2. New Airplane Info" << endl << endl;
		cout << "\t\t\t3. Show Airline/Airplane Info" << endl << endl;
		cout << "\t\t\t4. Display All Airline Records" << endl << endl;
		cout << "\t\t\t5. Manage Airline Flights" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Airline air;
		Airplane plane;
		if(option == '1')
		{
			cout << "-> Entering New Airline Info" << endl << endl;
			air.create();
		}
		else if(option == '2')
		{
			cout << "Entering New Airplane Info" << endl << endl;
			air.display();
			plane.create();
		}
		else if(option == '3')
		{
			cout << "-> Viewing Airline Info with Airplanes" << endl << endl;
			air.display();
			air.readByID();
			plane.setID(air.getID());
			plane.display();
		}
		else if(option == '4')
		{
			cout << "-> Displaying All Airline Records" << endl << endl;
			air.display();
		}
		else if(option == '5')
		{
			cout << "Opening Flights Module with Create Authority" << endl << endl;
			flightModule(true);
		}
		else if(option == '6')
		{
			plane.mapAirplane();
			getch();
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			continue;
		}
	}	
}

void Interface::bookingModule() {
		Passenger p;
		Airline a;
		Ticket t;
		Flight f;
		Airplane plane;
		f.captureFlight();
		if(f.getID() == 0)
			return;
		cout << "Flight ID # " << f.getID() << endl;
		t.flightId = f.getID();
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\tB. Book Ticket Reservation" << endl << endl;
		cout << "\t\t\tM. Manage Ticket Bookings" << endl << endl;
		cout << "\t\t\tR. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getche();
		if(option == 'B' || option == 'b') {
			cout << endl;
			if(p.checkOrCreate())
			{
				cout << "LETS BOOK TICKET...\a" << endl;
				cout << "Enter Passenger-ID: #";
				cin >> t.passengerId;
				p.updateLastFlight();
			}
			else
			{
				cout << "OOPS! REGISTER YOURSELF QUICK...\a" << endl;
				p.create();
				t.passengerId = p.getID();
			}
			plane.captureAirplane(f.getPlaneID());
			a.captureAirline(plane.getAirlineID());
			clear();
			cout << "Select Seat on Airplane:" << endl;
			plane.mapAirplane();
		    cout << endl << "Enter Seat Code (eg. A12): ";
		    cin >> t.seatCode;
		    cout << "Enter Ticket Price: ";
		    cin >> t.price;
		    clear();
		    t.dateOfBooking = p.showToday();
		    t.status = true;
			cout << "Opening Ticket Module with Create Authority" << endl << endl;
			t.create();
			cout << endl << "Generate Ticket: ";
			getch();
			string nameInput;
			cin.ignore();
			cout << endl << "Please Write Name for Ticket: ";
			getline(cin, nameInput);
			if(nameInput == "")
			{
				cout << endl << "Please Write Name for Ticket: ";
				getline(cin, nameInput);	
			}
			string ticjet = "95472";
			string fglight = a.getCode() + "-" + to_string(f.getID());
			t.generateTicket(nameInput, fglight, f.getTakeOffTime(), ticjet);
		}
		else if(option == 'M' || option == 'm') {
			cout << "Opening Ticket Module" << endl << endl;
			ticketModule(false);
		}
		else if(option == 'R' || option == 'r') {
			return;
		}
		else {
			return;
		}
}

void Interface::ticketModule(bool auth) {
	while(true)
	{
		clear();
		setThirdColor();
		cout << string(81, '-') << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\tTICKETING PORTAL\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t\t\t\t\t\t\t\t|" << endl;
		cout << string(81, '-') << endl << endl;
		cout << "\t\t\t1. Search Ticket By ID#" << endl << endl;
		cout << "\t\t\t2. Search Tickets By Passenger" << endl << endl;
		cout << "\t\t\t3. Cancel Ticket Reservation" << endl << endl;
		cout << "\t\t\t4. Display All Ticket Records" << endl << endl;
		cout << "\t\t\t0. Return to Main Menu" << endl << endl;
		cout << "Enter -> ";
		char option = getch();
		clear();
		Ticket t;
		if(option == '1')
		{
			cout << "Searching Ticket By ID#" << endl << endl;
			t.readByID();
		}
		else if(option == '2')
		{
			cout << "Searching Tickets By Passenger ID#" << endl << endl;
			t.readByPassengerID();
		}
		else if(option == '3')
		{
			cout << "Cancelling Ticket Reservation" << endl << endl;
			t.cancel();
		}
		else if(option == '4')
		{
			cout << "Displaying All Ticket Records" << endl << endl;
			t.display();
		}
		else if(option == '0')
		{
			return;
		}
		else
		{
			return;
		}
	}	
}

/* Running Environment */
int main()
{
	Interface user;
	user.appThread();
} 