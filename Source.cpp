#include <iostream>
#include <string>

using namespace std;

int main() {
	string user_choice="1";
	cout << "123456";
	do	// Main meun
	{

		if (user_choice != "1" && user_choice != "2"  && user_choice != "3"  && user_choice != "4"  && user_choice != "5")	// Data validation
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
