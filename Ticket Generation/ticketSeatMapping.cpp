#include <iostream>

using namespace std;

int even = 0;
string checkSeatBooked()
{
	bool booked = true;
	booked = even%2 == 0? true: false;
	even++;
	if(booked)
	{
		return "*";
	}
	return "";
}

void mapAirplane(int row, int column)
{
	char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int dash = 0;
	dash = (column * 17) - (column - 1);
	cout << string(dash, '-') << endl;
	for(int i=0; i < row; i++)
	{
		for(int j = 1; j <= column; j++)
		{
			cout << "|\t" << alphabet[i] << j << checkSeatBooked() << "\t|";
			if(j == column)
			{
				cout << endl;
			}
		}
		cout << string(dash, '-') << endl;
	}
}

int main()
{
	int a, b;
	cout << "Enter Row: ";
	cin >> a;
	cout << "Enter Column: ";
	cin >> b;
	mapAirplane(a, b);
}