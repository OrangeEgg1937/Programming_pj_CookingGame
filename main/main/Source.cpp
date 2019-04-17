#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#undef max
using namespace std;
void credit();
void burgerMenu();
void settingsMenu();
void instructions();

const int max_type = 10, max_burger = 10;//i change temporary

int min_type = 8, min_burger = 5, max_order = 5, time_limit = 40;

class Countdown
{
public:

	Countdown() {
		Timedue = finishtime = 0;
	}
	void startCount() {

		Timedue = time(0) + time_limit; //Start from time_limit and count down
	}
	void cookCount(int cooking_time)
	{
		finishtime = time(0) + cooking_time;
	}
	int printTime() {
		return Timedue - time(0);
	}
	int printcooktime() {
		return finishtime - time(0);
	}

private:

	int Timedue, finishtime;

};

class Burger
{
public:

	void modify(string define_name, string order, int time, int code) //Set information of each burger
	{
		name = define_name;
		ingredient_order = order;
		cooking_time = time;
		burger_code = code;
	}

	string call_name() //Show burger name 
	{
		return name;
	}

	string call_order() //Show how to cook the butger
	{
		return ingredient_order;
	}

	int call_cooktime()
	{
		return cooking_time;
	}

	int call_burger_code()
	{
		return burger_code;
	}

private:
	string name, ingredient_order;
	int cooking_time, burger_code; // burger_code = -1 means no such burger

};

class Ingredient
{
public:

	void modify(string a, char b)
	{
		name = a;
		short_form = b;
	}

	string display_fullname()
	{
		return name;
	}

	char show_shortname()
	{
		return short_form;
	}

private:
	string name;
	char short_form;
};

class List
{
public:

	List()
	{
		burger_list[0].modify("Cheese burger", "BCFLB", 10, 0);
		burger_list[1].modify("Beef burger", "BCTMLB", 10, 1);
		burger_list[2].modify("Mushroom burger", "BCFMB", 15, 2);
		burger_list[3].modify("Veggie burger", "BTELB", 10, 3);
		burger_list[4].modify("Salmon burger", "BCFSB", 15, 4);
		ingredients_list[0].modify("[B]read", 'B');
		ingredients_list[1].modify("[C]heese", 'C');
		ingredients_list[2].modify("Bee[f]", 'F');
		ingredients_list[3].modify("[L]ettuce", 'L');
		ingredients_list[4].modify("[T]omato", 'T');
		ingredients_list[5].modify("[M]ushroom", 'M');
		ingredients_list[6].modify("[E]gg", 'E');
		ingredients_list[7].modify("[S]almon", 'S');
		for (int i = 5; i < max_type; i++)
		{
			burger_list[i].modify("", "", 0, -1);
		}
		for (int i = 8; i < max_type; i++)
		{
			ingredients_list[i].modify("NO", 'N');
		}
	}

	void modify()
	{

	}

	Burger call_burger(int a)
	{
		return burger_list[a];
	}

	string call_burger_name(int a)
	{
		return burger_list[a].call_name();
	}

	string call_burger_ingredients(int a)
	{
		return burger_list[a].call_order();
	}

	int call_burger_time(int a)
	{
		return burger_list[a].call_cooktime();
	}

	string call_ingredients_fname(int a)
	{
		return ingredients_list[a].display_fullname();
	}

	char call_ingredients_sname(int a)
	{
		return ingredients_list[a].show_shortname();
	}

	void display_forder(int a)
	{
		string temp = burger_list[a].call_order();
		for (int i = 0; i < temp.length(); i++)
		{
			for (int j = 0; j < min_type; j++)
				if (temp[i] == ingredients_list[j].show_shortname())
				{
					cout << ingredients_list[j].display_fullname() << " ";
					break;
				}
		}
	}

private:
	Burger burger_list[max_burger];
	Ingredient ingredients_list[max_type];
};

class Order
{
public:

	void order_start()
	{
		timer.startCount();
	}

	int show_order_time()
	{
		if (status == 0 || status == 1)
		{
			return timer.printTime();
		}
		else
		{
			return end_time;
		}
	}

	void cooking_start()
	{
		timer.cookCount(food.call_cooktime());
		status = 1;
	}

	void process()
	{
		if (timer.printcooktime() <= 0 && status == 1)
		{
			finish();
		}
	}

	void time_stop()
	{
		end_time = timer.printTime();
	}

	void finish()
	{
		if (timer.printTime() >= 0)
		{
			status = 2;
			time_stop();
		}
		else
		{
			status = 3;
			time_stop();
		}
	}

	void import_foodlist(List a)
	{
		food_list = a;
	}

	void refresh_order()
	{
		food = food_list.call_burger(rand() % (min_burger - 1));
		status = 0;
		check_order = 0;
		end_time = 0;
	}

	void show_full_ingredient_name()
	{
		food_list.display_forder(food.call_burger_code());
	}

	void order_check(int &score)
	{
		if (check_order == 0 && status >= 2)
		{
			switch (status)
			{
			case 2:score = score + 10; break;
			case 3:score = score - 5; break;
			}
			check_order = 1;
		}

	}

	int show_order_status_code()
	{
		return status;
	}

	string show_order_name()
	{
		return food.call_name();
	}

	string show_status()
	{
		switch (status)
		{
		case 0: return "preparing"; break;
		case 1: return "cooking"; break;
		case 2: return "ready to serve"; break;
		case 3: return "fail to serve"; break;
		};
	}

	string show_ingredient_order()
	{
		return food.call_order();
	}

private:
	Burger food;
	List food_list;
	Countdown timer;
	int status = 0, end_time = 0, check_order = 0;  //default 0 = preparing  [0-preparing 1-cooking 2-ready to serve 3-fail to finish order 4-order closed]
};

void SetColor(int color = 7) //for setting font color
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void showTypeofburgers(List a)
{
	string line(110, '-');
	cout << left << setw(20) << "Type of burgers" << setw(28) << "Cooking time (in second)" << "Ingredients orders" << "\n"
		<< line << "\n";
	for (int i = 0; i < min_burger; i++)
	{
		cout << left << setw(20) << a.call_burger_name(i)
			<< setw(28) << a.call_burger_time(i);
		a.display_forder(i);
		cout << "\n";
	}
	cout << "\n";
}

void showIngsymbol(List a) {
	string line(28, '-');
	cout << left << setw(15) << "Ingredients" << setw(10) << "Symbol" << "\n" << line << "\n";
	for (int i = 0; i < min_type; i++)
	{
		cout << setw(15) << a.call_ingredients_fname(i)
			<< a.call_ingredients_sname(i) << "/" << char(a.call_ingredients_sname(i) + 32);
		cout << "\n";
	}
	cout << "\n";
}

/*
void display_order(List a, Countdown timer[],int order[],int status[], int score, int total_order) {
	SetColor();
	cout << "*** Order list ***" << endl;
	for (int i = 1; i <= total_order; i++)
	{
		(timer[i].printTime() < 15)?SetColor(12):SetColor();
		cout << "Order #"<< i ; SetColor();
		cout << ": " << a.call_burger_name(order[i]) << ", ";
		switch (status[i]) {
		case 0: {SetColor(); cout << "preparing, "; SetColor();  break; }
		case 1: {SetColor(14); cout << "cooking, "; SetColor();  break; }
		case 2: {SetColor(11); cout << "ready to serve, "; SetColor();  break; }
		}
		cout << timer[i].printTime() / 60 << "'" << timer[i].printTime() % 60 << "\"" << "    "<< timer[i].printcooktime() << endl;
	}
	SetColor();
	cout << "-----------------------------------------------" << endl;
	for (int i = 1; i <= score / 5; i++) { cout <<"*"; }
	cout<<endl;
	cout << "Score: " << score << endl;
}
*/
/*
void sorting(int order[],int status[],Countdown timer[],int i,int &total_order){ //1 order is expired, the other will be sorted upward.
	for (int j = i; j < total_order; j++)
	{
		order[j] = order[j + 1];
		status[j] = status[j + 1];
		timer[j] = timer[j + 1];
	}
		total_order--;
}

void check_order_expired(List a, Countdown timer[], int order[], int status[], int &total_order, int &score,int i) {
	if (timer[i].printTime() <= 0)
	{
		score -= 5;
		sorting(order, status, timer, i, total_order);
	}
	else if (timer[i].printcooktime() == 0)
	{
		status[i] = 2;
	}
}

void display_process(List a,Countdown timer[],int status[],int order[],char choice) {
	system("CLS");
	cout << "*** Process Order ***" << endl;
	cout << left << setw(22) << "Order #" << ": " << (int)choice - 48 << endl;
	cout << setw(22) << "Burger" << ": " << a.call_burger_name(order[(int)(choice)-48]) << endl;
	cout << setw(22) << "Status" << ": ";
	switch (status[(int)(choice)-48]) {
	case 0: {SetColor(); cout << "preparing" << endl; SetColor(); break; }
	case 1: {SetColor(14); cout << "cooking" << endl; SetColor(); break; }
	case 2: {SetColor(11); cout << "ready to serve" << endl; SetColor(); break; }
	}
	cout << setw(22) << "Remaining Time" << ": "
		<< timer[(int)(choice)-48].printTime() / 60
		<< "'" << timer[(int)(choice)-48].printTime() % 60 << "\"" << endl;
	cout << "Burger Ingredient List:" << endl;
	cout << setw(22) << "Burger Key List" << ": " << a.call_burger_ingredients(order[(int)(choice)-48]) << endl;
}
*/

void order_list(Order a[], int score)
{
	cout << "*** Process Order ***" << endl;
	for (int i = 0; i < max_order; i++) // Refresh all order
	{
		cout << "Order #" << i + 1 << ": ";
		cout << a[i].show_order_name() << ", ";
		cout << a[i].show_status() << ", ";
		cout << a[i].show_order_time() / 60 << "'" << a[i].show_order_time() - (a[i].show_order_time() / 60 * 60) << "\"" << endl;
	}
	cout << "----------------------------------------------" << endl;
	cout << "Score: " << score << endl;
	cout << "Enter[U] for update, [Q] for Quit, or [1 - " << max_order << "] for order :" << endl;
}

void show_single_order(Order list[], int i)
{
	bool correct = 0;
	string input;
	{
		do
		{
			cout << "Order #               :" << i + 1 << endl;
			cout << "Burger                :";
			cout << list[i].show_order_name() << endl;
			cout << "Status                :";
			cout << list[i].show_status() << endl;
			cout << "Burger Ingredient List:";
			list[i].show_full_ingredient_name();
			cout << endl << "Burger Key List       :";
			cout << list[i].show_ingredient_order() << endl;
			cout << "Please choose[U] for update, [R] for return, or";
			cout << endl << "type correct key list to start cooking :";

			cin >> input;

			if (input == list[i].show_ingredient_order() && list[i].show_status() == "preparing")
			{
				list[i].cooking_start();
				break;
			}


		} while ((input != "R" && input != "r"));
	}
	system("cls");
}

void game_start(List a)
{
	Order *player_order = new Order[max_order]; // Dynamic memory for order, size of order depends on "max_order"

	char choice[3] = { '0','0','\0' }; //user input and data validation
	int order = 0;
	int score = 10; //default score
	bool pass = 1;

	srand(time(0));

	for (int i = 0; i < max_order; i++) // Refresh all order
	{
		player_order[i].import_foodlist(a);
		player_order[i].refresh_order();
		player_order[i].order_start();
	}

	while (choice[0] != 'r' || choice[0] != 'R')
	{
		do
		{
			for (int i = 0; i < max_order; i++) // Cooking
			{
				player_order[i].process();
				player_order[i].order_check(score);
			}
			for (int i = 0; i < max_order; i++)
			{
				if (player_order[i].show_order_status_code() >= 2)
				{
					if ((rand() % 100 + 1) >= 50)
					{
						player_order[i].refresh_order();
						player_order[i].order_start();
					}
				}
			}


			order_list(player_order, score);

			if (choice[2] != '\0')
			{
				cout << "Wrong input! Please input a valid value!" << endl;
				choice[2] = '\0';
			}

			cin >> choice;
			cin.ignore();
			system("cls");

			if (choice[0] == 'Q' || choice[0] == 'q')
			{
				break;
			}


		} while (choice[0] == 'U' || choice[0] == 'u' || choice[2] != '\0');

		if (choice[1] == '\0')
		{
			choice[1] = '0';
		}
		if (choice[0] == 'Q' || choice[0] == 'q')
		{
			break;
		}

		order = ((int)choice[0] - 48) + (((int)choice[1] - 48) * 10); // Char to integer
		show_single_order(player_order, order - 1);

	}

}

void show_orderlist(List a)
{
	Order *order_list = new Order[max_order];
	for (int i = 0; i < max_order; i++)
	{
		order_list[i].import_foodlist(a);
		order_list[i].refresh_order();
	}
	for (int i = 0; i < max_order; i++)
	{
		cout << order_list[i].show_order_name() << endl;
	}
}

int main() {
	int user_choice;
	List mylist;

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
		case 1: game_start(mylist); break;
		case 2: settingsMenu(); break; //setting()
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
	List mylist;
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
		case 1: showTypeofburgers(mylist); system("pause"); system("cls"); break;
		case 2: showIngsymbol(mylist); system("pause"); system("cls"); break;
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
			cout << "\n   How to play the game?\n\n"
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