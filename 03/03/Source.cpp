#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void credit();
void burgerMenu();
void settingsMenu();

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
		case 2: settingsMenu(); break;
		case 3: burgerMenu(); break;
		case 4: break;
		case 5: credit(); break;
		case 6: break;
		default: cout << "Invalid input, please input again. \n\n"; break;
		}
	} while (user_choice != 6);
	cout << "Good bye!" << "\n";
	return 0;
}

void settingsMenu() {
	int sett_choice;
	do {
		cout << "*** Settings Menu ***\n"
			<< "[1] Time limit [40 sec]\n"
			<< "[2] Max number of orders [5]\n"
			<< "[3] Return to Game Menu\n"
			<< "*********************\n"
			<< "Option (1 - 3): ";
		cin >> sett_choice;
		while (!cin) { //ignore any character
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		}
		system("cls");
		switch (sett_choice) {
		case 1: break;
		case 2: break;
		case 3: break;
		default: cout << "Invalid input, please input again. \n\n"; break;
		}
	} while (sett_choice != 3);
	return;
}

void burgerMenu() {
	int bmenu_choice;
	do {
		cout << "**** Burger Menu *****\n"
			<< "[1] Types of Burger\n"
			<< "[2] Ingredient Symbols\n"
			<< "[3] Return to Game Menu\n"
			<< "*********************\n"
			<< "Option (1 - 3): ";
		cin >> bmenu_choice;
		while (!cin) { //ignore any character
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		}
		system("cls");
		switch (bmenu_choice) {
		case 1: break;
		case 2: break;
		case 3: break;
		default: cout << "Invalid input, please input again. \n\n"; break;
		}
	} while (bmenu_choice != 3);
	return;
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