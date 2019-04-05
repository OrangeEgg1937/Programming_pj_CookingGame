#include <iostream>
#include <string>
#include <iomanip>
#include<cstdlib>

using namespace std;

string Burgertype[10];

class Time
{
public:
	Time() {
		hour = minute = second = 0;
	}
	void printTime() {
		cout << hour << ":" << minute << ":" << second << endl;
	}
	void setTime(int h, int m, int s) {
		if (validTime(h, m, s)) {
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

class Burger
{
public:

	Burger(string define_name, string order, int time)
	{
		name = define_name;
		ingredient_order = order;
		cooking_time = time;
	}

	int time() {
		return cooking_time;
	}
	string call_name() {
		return name;
	}
	string order()
	{
		return ingredient_order;
	}

private:
	string name, ingredient_order;
	int cooking_time;

};

/*void init() {  //testing for global local object
string Burgertype[10] = { "Cheese burger","Beef burger" };
string Burgercode[10] = {"BCBLB","BCTBLB"}
Burger CheeseB, BeefB;

CheeseB.setBurger("Cheese burger", "BCBLB", 10);
BeefB.setBurger("Beef burger", "BCTBLB", 10);
} */

int main() {
	string user_choice = "0";
	Burger list[2]{ { "Cheese burger ", "Bread, cheese, beef, lettuce, bread ",70 },{ "Beef burger ", "Bread, cheese, tomato, beef, lettuce, bread ",30 } };

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