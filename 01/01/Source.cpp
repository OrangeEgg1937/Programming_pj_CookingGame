#include <iostream>
#include <string>
#include <iomanip>
#include<cstdlib>

using namespace std;

class Time
{
public:
	void printTime() {
		cout << hour << ":" << minute << ":" << second << endl;
	}
	void setTime(int h, int m, int s) {
		if (validTime(h,m,s)) {
			hour = h;
			minute = m;
			second = s;
		}
		else
			hour = minute = second = 0;
	}
	int getHour() {
		return hour;
	}
private:
	int hour, minute, second;
	bool validTime(int h, int m, int s) {
		return (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60);
	}
};

class burger 
{
public:
	burger(string, int);

};

int main() {
	string user_choice = "0";
	do	// Main meun
	{

		if (user_choice == "1")	// Data validation
		{
			cout << "Invalid input, try again! (TESTING) \n\n";
		}
		cout << "A good Welcome Message will be designed by someone\n\n";
		cout << "*** Game Menu ***\n";
		cout << "[1] Start Game\n";
		cout << "[2] Settings\n";
		cout << "[3] Burger Menus\n";
		cout << "[4] Instructions\n";
		cout << "[5] Credits\n";
		cout << "[6] Exit\n";
		cout << "*****************\n";
		cout << "Option(1 - 6) : ";
		cin >> user_choice;
		system("cls");

	} while (user_choice != "6");
	return 0;
}