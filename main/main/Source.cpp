#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void credit();
void burgerMenu();
void settingsMenu();
void instructions();

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
		case 4: instructions(); break;
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

void instructions() {
	int instruct_choice;
	do {
		cout << "***Game Instructions***\n"
			<< "[1] How to play the game\n"
			<< "[2] Game Rules\n"
			<< "[3] About the Time limit\n"
			<< "[4} How to quit the game\n"
			<< "[5] Back to the Game Menu\n"
			<< "***********************\n"
			<< "Option (1 - 5): ";
		cin >> instruct_choice;
		while (!cin) { //ignore any character
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		}
		system("cls");
		switch (instruct_choice) {
		case 1:
			cout << "\n   How to play the game?\n"
				<< "1. Choose \"[1] Start Game\" at the Game Menu to start the game.\n"
				<< "2. A order list will be shown since the game start.\n"
				<< "   The max number of order is default as 5.\n"
				<< "   You can change it by choosing \"[2] Settings\" at the Game Menu.\n"
				<< "3. Each burger has to go through 3 statuses to complete: preparing, cooking and ready to serve.\n" << "\n"

				<< "  Status: preparing\n"
				<< "- Input the order number to process the order with status \"preparing\".\n"
				<< "- Type the correct order of ingredient following the Burger Ingredient List.\n"
				<< "- You just need to input the first character of each ingredient.\n"
				<< "- If the input is correct, the system returns to the order list.\n"
				<< "- The status of that order will change to \"cooking\".\n" << "\n"

				<< "  Status: cooking\n"
				<< "- When the burger is in the \"cooking\" status, you have to wait until it is done.\n"
				<< "- Tips: You can cook other burgers to save time.\n"
				<< "- If the burger is cooked, the status of the burger will be changed from \"cooking\" to \"ready to serve\".\n\n"

				<< "  Status: ready to serve\n"
				<< "- Type the order number of the order with status \"ready to serve\" to serve the order.\n\n";
			system("pause");
			system("cls");
			break;

		case 2:
			cout << "\n   Game Rules\n\n"
				<< "1. When the game starts, you will initially have 10 marks.\n"
				<< "2. If the order is served on time, 10 marks will be awarded.\n"
				<< "   But if the order cannot be served within the time limit, 5 marks will be deducted.\n"
				<< "3. The game finishes when the score < 0 and you will be returned to the Game Menu.\n\n";
			system("pause");
			system("cls");
			break;

		case 3:
			cout << "\n   Time limit\n\n"
				<< "1. All order of all types of burger are same.\n"
				<< "2. The time limit is defaulted as 40 seconds\n"
				<< "3. You can change it by choosing \"[2] Settings\" at the Game Menu.\n\n";
			system("pause");
			system("cls");
			break;

		case 4:
			cout << "\n   How to quit the game?\n\n"
				<< "You can input ．q・ or ．Q・ in the order list page to quit the game.\n\n";
			system("pause");
			system("cls");
			break;

		case 5: break;
		default: cout << "Invalid input, please input again. \n\n"; break;
		}
	} while (instruct_choice != 5);
	return;
}

void credit() {
	string line(50, '-');
	cout << left << setw(17) << "Name" << setw(15) << "Student ID" << setw(10) << "Class" << "Tutorial\n"
		<< line << "\n"
		<< left << setw(17) << "Ng Ho Tin" << setw(15) << "18188135A" << setw(10) << "203" << "Group A\n"
		<< setw(17) << "Pau Chun Wai" << setw(15) << "18071191A" << setw(10) << "203" << "Group A\n"
		<< setw(17) << "Lee Hei Tung" << setw(15) << "18024104A" << setw(10) << "203" << "Group A\n"
		<< setw(17) << "Ho Kwong Wa" << setw(15) << "18006958A" << setw(10) << "203" << "Group A\n"
		<< setw(17) << "Tam Chi Hong" << setw(15) << "18031710A" << setw(10) << "203" << "Group A\n\n";
	system("pause");
	system("cls");
}