#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void credit();

int main() {
	int user_choice;

	do	// Main menu
	{
		cout << "Welcome!\n\n"
			<< "*** Game Menu ***\n"
			<< "[1] Start Game\n"
			<< "[2] Settings\n"
			<< "[3] Burger Menus\n"
			<< "[4] Instructions\n"
			<< "[5] Credits\n"
			<< "[6] Exit\n"
			<< "*****************\n"
			<< "Option(1 - 6) : ";
		cin >> user_choice;
		while (!cin) { //ignore any character
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		}
		system("cls");
		switch (user_choice) {
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: credit(); break;
		case 6: break;
		default: cout << "Invalid input, please input again. \n\n"; break;
		}
	} while (user_choice != 6);
	cout << "Good bye!" << "\n";
	return 0;
}

void credit() {
	string line(50, '-');
	cout << left << setw(15) << "Name" << setw(15) << "Student ID" << setw(10) << "Class" << "Tutorial\n"
		<< line << "\n"
		<< left << setw(15) << "Ng Ho Tin" << setw(15) << "18188135A" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "xxxxxxxxxx" << setw(15) << "18xxxxxxA" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "xxxxxxxxxx" << setw(15) << "18xxxxxxA" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "xxxxxxxxxx" << setw(15) << "18xxxxxxA" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "xxxxxxxxxx" << setw(15) << "18xxxxxxA" << setw(10) << "203" << "Group A\n";
	system("pause");
	system("cls");
}