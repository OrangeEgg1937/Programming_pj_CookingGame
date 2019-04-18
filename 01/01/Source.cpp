#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <chrono>
#include <thread>
#pragma warning( disable : 4996)

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

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
					fullname_ingredients = ingredients_list[j].display_fullname() + " ";
					break;
				}
		}
	}

	string display_ingredients_fname()
	{
		return fullname_ingredients;
	}

private:
	Burger burger_list[max_burger];
	Ingredient ingredients_list[max_type];
	string fullname_ingredients;
};

class Order
{
public:

	void order_start()
	{
		timer.startCount();
	}

	int timeremain()
	{
		return(timer.printTime());
	}

	int cookingtimeremain()
	{
		return(timer.printcooktime());
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

	void refresh_order(int a)
	{
		srand(time(0) + a);
		food = food_list.call_burger(rand() % (min_burger - 1));
		status = 0;
		check_order = 0;
		end_time = 0;
	}

	void show_full_ingredient_name()
	{
		food_list.display_forder(food.call_burger_code());
	}

	void order_check(int &score, int time)
	{
		if (time < 0)
			status = 3;
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

void show_list(List a) // TEST USE !! REMEMBER TO DEL !!
{
	cout << "Type of burgers\t\t" << "Ingredients orders\t" << "Cooking time (in second)" << endl;
	for (int i = 0; i < min_burger; i++)
	{
		cout << a.call_burger_name(i) << "\t\t";
		cout << a.call_burger_ingredients(i) << "\t\t\t";
		cout << a.call_burger_time(i) << "S";
		cout << endl;
	}

	cout << endl;
	cout << endl;

	cout << setw(25) << "Type of Ingredients" << setw(10) << "Symbol" << endl;

	for (int i = 0; i < min_type; i++)
	{
		cout << setw(25) << a.call_ingredients_fname(i);
		cout << setw(8) << a.call_ingredients_sname(i) << "/" << char(a.call_ingredients_sname(i) + 32);
		cout << endl;
	}

	cout << endl;
	cout << endl;

	cout << "Type of burgers\t\t" << "Ingredients orders(Full Name)" << endl;
	for (int i = 0; i < min_burger; i++)
	{
		cout << a.call_burger_name(i) << "\t\t";
		a.display_forder(i);

		cout << endl;
	}

	cout << endl;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void sorting(Order a[]) { //1 order is expired, the other will be sorted upward.
	Order temp;
	for (int j = 0; j < max_order - 1; j++)
	{
		if (a[j].show_order_status_code() >= 2)
		{
			temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
		}
	}
}

void order_list(Order a[], int score)
{
	sorting(a);
	cout << "*** Process Order ***" << endl;
	for (int i = 0; i < max_order; i++) // Refresh all order
	{
		cout << "Order #" << i + 1 << ": ";
		cout << a[i].show_order_name() << ", ";
		switch (a[i].show_order_status_code()) {
		case 0: SetColor(7); break;
		case 1: SetColor(14); break;
		case 2: SetColor(2); break;
		case 3: SetColor(4); break;
		}
		cout << a[i].show_status() << ", ";
		SetColor();
		if (a[i].show_order_time() >= 0)
		{
			cout << a[i].show_order_time() / 60 << "'" << a[i].show_order_time() - (a[i].show_order_time() / 60 * 60) << "\"" << endl;
		}
		else
		{
			cout << "0'0\"" << endl;
		}
	}
	cout << "----------------------------------------------" << endl;
	cout << "Score: " << score << endl;
	cout << "Enter[U] for update, [Q] for Quit, or [1 - " << max_order << "] for order :" << endl;
}

void show_single_order(Order list[], int i)
{
	bool correct = 1;
	string input;
	{
		do
		{
			input = "";
			cout << "Order #               :" << i + 1 << endl;
			cout << "Burger                :";
			cout << list[i].show_order_name() << endl;
			cout << "Status                :";
			cout << list[i].show_status() << endl;
			cout << "Remaining Time        :";
			if (list[i].show_order_time() >= 0)
			{
				cout << list[i].show_order_time() / 60 << "'" << list[i].show_order_time() - (list[i].show_order_time() / 60 * 60) << "\"" << endl;
			}
			else
			{
				cout << "0'0\"" << endl;
			}
			cout << "Burger Ingredient List:";
			list[i].show_full_ingredient_name();
			cout << endl << "Burger Key List       :";
			cout << list[i].show_ingredient_order() << endl;
			cout << "Please choose[U] for update, [R] for return, or";
			cout << endl << "Type correct key list to start cooking :";
			cin >> input;

			for (int i = 0; i < (input.length()); i++)
			{
				if ((input[i]>='a')&&(input[i]<='z'))
				{
					((input[i] = (char)((int)input[i] - 32)));
				}
			}

			if (input == list[i].show_ingredient_order())
			{
				list[i].cooking_start();
				break;
			}
			else if (input != "U" && input != "u" && input != "R" && input != "r")
			{
				cout << "Invalid input, please input again.\n";
				system("pause");
			}

			system("cls");

		} while ((input != "R" && input != "r"));
	}
	system("cls");
}

void game_start(List a)
{
	Order *player_order = new Order[max_order]; // Dynamic memory for order, size of order depends on "max_order"

	char choice[3] = { '\0','\0','\0' }; //user input and data validation
	int order = 0;
	int score = 10; //default score
	bool pass = 1, checkinput;

	srand(time(0));

	for (int i = 0; i < max_order; i++) // Refresh all order
	{
		player_order[i].import_foodlist(a);
		player_order[i].refresh_order();
		player_order[i].order_start();
	}

	while (choice[0] != 'r' || choice[0] != 'R' || score < 0)
	{
		do
		{
			checkinput = 0;
			int remain_no_of_order = 0;
			for (int i = 0; i < max_order; i++) // Cooking
			{
				player_order[i].process();
				player_order[i].order_check(score, player_order[i].timeremain());
			}
			for (int i = 0; i < max_order; i++)
			{
				if (player_order[i].show_order_status_code() >= 2)
				{
					if ((rand() % 100 + 1) >= 90)
					{
						player_order[i].refresh_order(i);
						player_order[i].order_start();
					}
				}
				else
				{
					remain_no_of_order++;
				}
			}


			order_list(player_order, score);

			if (score >= 0)
			{
				cin >> choice;
				cin.ignore();
			}
			else
			{
				system("pause");
				system("cls");
				break;
			}

		

			if ((choice[0] == 'U' || choice[0] == 'u' || choice[0] == 'Q' || choice[0] == 'q') && (choice[1] == '\0') && (choice[2] == '\0'))
			{
				checkinput = 1;
			}

			if ((choice[0] >= '1' && choice[0] <= '9') && ((int)choice[0] - 48 <= remain_no_of_order) && (choice[1] == '\0') && (choice[2] == '\0'))
			{
				checkinput = 1;
			}

			if ((choice[0] >= '1' && choice[0] <= '9') && (choice[1] >= '0' && choice[1] <= '9') && (((((int)choice[0] - 48) * 10) + ((int)choice[1] - 48)) <= remain_no_of_order) && (choice[2] == '\0'))
			{
				checkinput = 1;
			}
			
			if (not(checkinput))
			{
				cout << "Wrong input! Please input a valid value!" << endl;
				system("pause");
				system("cls");
			}

			if (choice[0] == 'Q' || choice[0] == 'q' || score < 0)
			{
				break;
			}

			system("cls");

		} while (choice[0] == 'U' || choice[0] == 'u' || choice[2] != '\0');

		if (choice[1] == '\0')
		{
			choice[1] = '0';
		}
		if (choice[0] == 'Q' || choice[0] == 'q' || score < 0)
		{
			break;
		}

		if (choice[1] == '\0')
			order = ((int)choice[0] - 48) * 10 + ((int)choice[1] - 48);
		else	order = ((int)choice[0] - 48);


		if (checkinput == 1)
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

void settingsMenu() {
	char sett_choice[2] = { '\0','\0' };
	char time[5] = { '\0', '\0', '\0', '\0', '\0' }, order[4] = { '\0', '\0', '\0', '\0' };
	int  sum;
	bool valid_state = 1;
	do {
		cout << "*** Settings Menu ***\n"
			<< "[1] Time limit [" << time_limit << " sec]\n"
			<< "[2] Max number of orders [" << max_order << "]\n"
			<< "[3] Return to Game Menu\n"
			<< "*********************\n"
			<< "Option (1 - 3): ";
		cin >> sett_choice;
		cin.ignore();
		if (sett_choice[1] == '\0')
		{
			switch (sett_choice[0]) {
			case '1': do {
				system("cls");
				sum = 0;
				int temp = 1;
				int check = 0;
				valid_state = 1;
				for (int i = 0; i <= 4; i++)
				{
					time[i] = '\0';
				}
				cout << "Time limit [1 - 300 sec]: ";
				cin >> time;
				cin.ignore();

				for (int i = 0; i <= 4; i++)
				{
					if ((time[i] != '\0') && ((time[i] < '0') || (time[i] > '9')))
					{
						valid_state = 0;
					}
				}

				for (int i = 1; i <= 4; i++)
				{
					if (time[i] == '\0')
					{
						check = i;
						break;
					}
				}

				for (int i = check - 1; i >= 0; i--)
				{
					if (time[i] != '\0')
					{
						if (i <= check - 2)
							temp *= 10;
						sum += (int(time[i]) - 48) * temp;
					}
					else sum += 0;
				}

				if (sum < 1 || sum > 300 || valid_state == 0)
				{
					cout << "Invalid input, please input again.\n";
					system("pause");
				}
				system("cls");
			} while (sum < 1 || sum > 300 || valid_state == 0);
			time_limit = sum;
			break;
			case '2': do {
				system("cls");
				sum = 0;
				int temp = 1;
				int check = 0;
				valid_state = 1;
				for (int i = 0; i <= 3; i++)
				{
					order[i] = '\0';
				}
				cout << "Max number of orders[1 - 50]: ";
				cin >> order;
				cin.ignore();

				for (int i = 0; i <= 3; i++)
				{
					if ((order[i] != '\0') && ((order[i] < '0') || (order[i] > '9')))
					{
						valid_state = 0;
					}
				}

				for (int i = 1; i <= 3; i++)
				{
					if (order[i] == '\0')
					{
						check = i;
						break;
					}
				}

				for (int i = check - 1; i >= 0; i--)
				{
					if (order[i] != '\0')
					{
						if (i <= check - 2)
							temp *= 10;
						sum += (int(order[i]) - 48) * temp;
					}
					else sum += 0;
				}

				cout << sum;

				if (sum < 1 || sum > 50 || valid_state == 0)
				{
					cout << "Invalid input, please input again.\n";
					system("pause");
				}
				system("cls");
			} while (sum < 1 || sum > 50 || valid_state == 0);
			max_order = sum;
			break;
			case '3': break;
			default: cout << "Invalid input, please input again. \n\n";
				system("pause");
				system("cls");
				break;
			}
		}
		else
		{
			SetConsoleTextAttribute(color, 10);
			cout << endl << "Wrong input!! Try again!!!";
			SetColor();
			system("pause");
			sett_choice[1] = '\0';
			system("cls");
		}
	} while (sett_choice[0] != '3');
	return;
}

void burgerMenu(List a) {
	char bmenu_choice;

	do {
		system("cls");
		cout << "**** Burger Menu *****\n"
			<< "[1] Types of Burger\n"
			<< "[2] Ingredient Symbols\n"
			<< "[3] Return to Game Menu\n"
			<< "*********************\n"
			<< "Option (1 - 3): ";
		cin >> bmenu_choice;
		cin.ignore();
		switch (bmenu_choice) {
		case '1': system("cls");
			cout << "Type of burgers\t" << "|\t" << "Ingredients orders(Full Name)\t\t\t\t" << "|\t" << "Cooking time (in second)" << endl;
			for (int i = 0; i < 112; i++)
			{
				cout << "=";
			}
			cout << endl;
			for (int i = 0; i < min_burger; i++)
			{
				cout << a.call_burger_name(i) << "\t" << "|\t";
				a.display_forder(i);
				if (i == 1)
				{
					cout << " |\t";
				}
				else
				{
					cout << "\t\t" << "|\t";
				}
				cout << a.call_burger_time(i) << "S" << endl;
			}
			system("pause");
			break;
		case '2': system("cls");
			cout << right << setw(25) << "Type of Ingredients" << setw(3) << "|" << setw(9) << "Symbol" << endl;
			for (int i = 0; i < 50; i++)
			{
				cout << "=";
			}
			cout << endl;
			for (int i = 0; i < min_type; i++)
			{
				cout << setw(25) << a.call_ingredients_fname(i)
					<< setw(3) << "|" << setw(7) << a.call_ingredients_sname(i) << "/" << char(a.call_ingredients_sname(i) + 32) << endl;
			}
			system("pause");
			break;
		case '3': break;
		default: cout << "Invalid input, please input again. \n\n"; system("pause"); break;
		}
	} while (bmenu_choice != '3');
	return;
}

void demo() {
	string input;
	int timea = 1, timeb = 10000000;
	cout << "    #############     " << endl;
	cout << "    ##         ##     " << endl;
	cout << "    #  ~~   ~~  #     " << endl;
	cout << "    #  ()   ()  #     " << endl;
	cout << "    (     ^     )     " << endl;
	cout << "     |         |      " << endl;
	cout << "     |  {===}  |      " << endl;
	cout << "      \\       /      " << endl;
	cout << "     /  -----  \\     " << endl;
	cout << "  ---  |%\\ /%|  ---   " << endl;
	cout << " /     |%%%%%|     \\  " << endl;
	cout << "       |%/ \\%|        " << endl;
	gotoxy(30, 0); sleep_for(seconds(timea));
	cout << "Welcome to your burger shop!!" << endl;
	gotoxy(30, 2); sleep_for(seconds(timea));
	cout << "I am Gordon Ramsey" << endl;
	gotoxy(30, 4); sleep_for(seconds(timea));
	cout << "From now on i will be your teacher," << endl;
	gotoxy(30, 6); sleep_for(seconds(timea));
	cout << "after you have attended this course" << endl;
	gotoxy(30, 8); sleep_for(seconds(timea));
	cout << "You will become a good chef like me" << endl;
	gotoxy(30, 10); sleep_for(seconds(timea));
	cout << "So don't let me disappointed ^_^";
	gotoxy(0, 12);
	system("PAUSE");
	system("CLS"); sleep_for(nanoseconds(timeb));
	cout << "*** Order list ***" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #1: Cheese burger, preparing, 0'40\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #2: Beef burger, preparing, 0'40\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #3: Cheese burger, preparing, 0'40\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #4: mushroom burger, preparing, 0'40\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #5: salmon burger, preparing, 0'40\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "-----------------------------------------------" << endl; sleep_for(nanoseconds(timeb));
	cout << "Score: 10" << endl; sleep_for(nanoseconds(timeb));
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order :";
	gotoxy(60, 2); sleep_for(seconds(timea));
	cout << "First, you will access to the page called 'Order list'. ," << endl;
	gotoxy(60, 4); sleep_for(seconds(timea + 1));
	cout << "Let's try to send '1'";
	do {
		gotoxy(58, 8);
		cout << "          ";
		gotoxy(58, 8);
		cin >> input;
		if (input != "1") {
			gotoxy(60, 6);
			cout << "Just type 1 and send it! DON'T YOU KNOW THIS SIMPLE ORDER?";
		}
	} while (input != "1");
	system("CLS"); sleep_for(nanoseconds(timeb));
	cout << "*** Process Order ***" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #               : 1" << endl; sleep_for(nanoseconds(timeb));
	cout << "Burger                : Cheese Burger" << endl; sleep_for(nanoseconds(timeb));
	cout << "Status                : Preparing" << endl; sleep_for(nanoseconds(timeb));
	cout << "Remaining Time        : 0'39\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Burger Ingredient List: [B]read, [C]heese, Bee[f], [L]ettuce, [B]read" << endl; sleep_for(nanoseconds(timeb));
	cout << "Burger Key List       : bcflb" << endl << endl; sleep_for(nanoseconds(timeb));
	cout << "Please choose [U] for update, [R] for return, or " << endl; sleep_for(nanoseconds(timeb));
	cout << "type correct key list to start cooking: " << endl;
	gotoxy(30, 12); sleep_for(seconds(timea));
	cout << "You DID it!!!";
	gotoxy(30, 14); sleep_for(seconds(timea));
	cout << "Here you will navigate to another page called 'Process Order,";
	gotoxy(30, 16); sleep_for(seconds(timea));
	cout << "Let's type in those words in Burger Key List!";
	gotoxy(30, 18); sleep_for(seconds(timea));
	cout << "You can either type in the letter in both whole upper case and lower case.";
	do {
		gotoxy(41, 9);
		cin >> input;
		if ((input != "bcflb") && (input != "BCFLB")) {
			gotoxy(50, 9);
			cout << "OMG! What are you doing???";
			gotoxy(41, 9);
			cout << "     ";
		}
	} while ((input != "bcflb") && (input != "BCFLB"));
	system("CLS"); sleep_for(nanoseconds(timeb));
	cout << "*** Order list ***" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #1: Cheese burger, cooking, 0'39\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #2: Beef burger, preparing, 0'39\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #3: Cheese burger, preparing, 0'39\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #4: mushroom burger, preparing, 0'39\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #5: salmon burger, preparing, 0'39\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "-----------------------------------------------" << endl; sleep_for(nanoseconds(timeb));
	cout << "Score: 10" << endl; sleep_for(nanoseconds(timeb));
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order :";
	gotoxy(60, 2); sleep_for(seconds(timea));
	cout << "Good Job!" << endl;
	gotoxy(60, 4); sleep_for(seconds(timea));
	cout << "The status of order #1 has changed to cooking";
	gotoxy(60, 6); sleep_for(seconds(timea));
	cout << "Seems it will finish after a few second";
	for (int i = 38; i >= 29; i--) {
		sleep_for(nanoseconds(timeb * 50));
		gotoxy(36, 1); cout << i;
		gotoxy(36, 2); cout << i;
		gotoxy(38, 3); cout << i;
		gotoxy(40, 4); cout << i;
		gotoxy(38, 5); cout << i;
	}
	gotoxy(0, 1);
	cout << "Order #1: Cheese burger, ready to serve, 0'29\"" << endl;
	gotoxy(60, 10); sleep_for(seconds(timea));
	cout << "TASTY!!" << endl;
	gotoxy(60, 12); sleep_for(seconds(timea));
	cout << "A burger was finished by your hand";
	gotoxy(60, 14); sleep_for(seconds(timea));
	cout << "Lets type '1' to send out the order";
	do {
		gotoxy(58, 8);
		cout << "          ";
		gotoxy(58, 8);
		cin >> input;
		if (input != "1") {
			gotoxy(60, 14);
			cout << "Just type 1 and send it! DON'T YOU KNOW THIS SIMPLE ORDER?";
		}
	} while (input != "1");
	system("CLS"); sleep_for(nanoseconds(timeb));
	cout << "*** Order list ***" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #1: Beef burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #2: Cheese burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #3: mushroom burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #4: salmon burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "-----------------------------------------------" << endl; sleep_for(nanoseconds(timeb));
	cout << "Score: 20" << endl; sleep_for(nanoseconds(timeb));
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order :";
	gotoxy(60, 2); sleep_for(seconds(timea));
	cout << "Now you have got 10 marks!";
	gotoxy(60, 4); sleep_for(seconds(timea));
	cout << "It is a good start";
	gotoxy(60, 6); sleep_for(seconds(timea));
	cout << "However, if the score become 0 or smaller";
	gotoxy(60, 8); sleep_for(seconds(timea));
	cout << "You have to close the shop :'(";
	gotoxy(60, 10);
	system("PAUSE");
	system("CLS");
	sleep_for(nanoseconds(timeb));
	cout << "*** Order list ***" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #1: Beef burger, preparing, 0'00\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #2: Cheese burger, preparing, 0'00\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #3: mushroom burger, preparing, 0'00\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #4: salmon burger, preparing, 0'00\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "-----------------------------------------------" << endl; sleep_for(nanoseconds(timeb));
	cout << "Score: 20" << endl; sleep_for(nanoseconds(timeb));
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order :";
	gotoxy(60, 2); sleep_for(seconds(timea));
	cout << "If you cannot finish 1 order in time";
	gotoxy(60, 4); sleep_for(seconds(timea));
	cout << "5 marks will be deducted";
	gotoxy(60, 6); system("PAUSE");
	system("CLS"); sleep_for(nanoseconds(timeb));
	cout << "*** Order list ***" << endl; sleep_for(nanoseconds(timeb));
	cout << "-----------------------------------------------" << endl; sleep_for(nanoseconds(timeb));
	cout << "Score: 0" << endl; sleep_for(nanoseconds(timeb));
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order :";
	gotoxy(60, 2); sleep_for(seconds(timea));
	cout << "Like this";
	gotoxy(60, 4); sleep_for(seconds(timea));
	cout << "Try not to get 0";
	gotoxy(60, 6); sleep_for(seconds(timea));
	cout << "And now lets turn back to the few second before";
	gotoxy(60, 8); sleep_for(seconds(timea));
	cout << "Let me teach you a new thing!";
	gotoxy(60, 10);
	system("PAUSE"); system("CLS"); sleep_for(nanoseconds(timeb));
	cout << "*** Order list ***" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #1: Beef burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #2: Cheese burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #3: mushroom burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "Order #4: salmon burger, preparing, 0'29\"" << endl; sleep_for(nanoseconds(timeb));
	cout << "-----------------------------------------------" << endl; sleep_for(nanoseconds(timeb));
	cout << "Score: 20" << endl; sleep_for(nanoseconds(timeb));
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order :";
	gotoxy(60, 2); sleep_for(seconds(timea));
	cout << "if you type U";
	gotoxy(60, 4); sleep_for(seconds(timea));
	cout << "The order in this list will be refreshed";
	gotoxy(60, 6); sleep_for(seconds(timea));
	cout << "And sometimes there will be a new order come in!";
	gotoxy(58, 7); sleep_for(seconds(timea * 2));
	cout << "U";
	sleep_for(seconds(timea));
	system("CLS");
	cout << "*** Order list ***" << endl;
	cout << "Order #1: Beef burger, preparing, 0'29\"" << endl;
	cout << "Order #2: Cheese burger, preparing, 0'29\"" << endl;
	cout << "Order #3: mushroom burger, preparing, 0'29\"" << endl;
	cout << "Order #4: salmon burger, preparing, 0'29\"" << endl;
	cout << "Order #5: Veggie burger, preparing, 0'40\"" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Score: 20" << endl;
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order :";
	gotoxy(60, 2); sleep_for(seconds(timea));
	cout << "see? There is a new order come in";
	gotoxy(60, 4); sleep_for(seconds(timea));
	cout << "and thats all what i can teach to you";
	gotoxy(60, 6); sleep_for(seconds(timea));
	cout << "Good Luck and Have FUN!";
	gotoxy(60, 8);
	system("PAUSE");
}

void instructions() {
	char instruct_choice;
	do {
		cout << "***Game Instructions***\n";
		cout << "[1] How to play the game\n";
		cout << "[2] Game Rules\n";
		cout << "[3] About the Time limit\n";
		cout << "[4] How to quit the game\n";
		cout << "[5] Show a demonstration to teach you how to play\n";
		cout << "[6] Back to the Game Menu\n";
		cout << "Option(1-6):";
		cin >> instruct_choice;
		system("cls");
		switch (instruct_choice) {
		case '1':	 cout << "   How to play the game\n" << "1. Choose \"[1] Start Game\" at the Game Menu to start the game.\n"
			<< "2. A order list will be shown since the game start.\n" << "   The max number of order is default as 5.\n"
			<< "   You can change it by choosing \"[2] Settings\" at the Game Menu.\n";
			cout << "3. Each burger has to go through 3 statuses to complete : preparing, cooking and ready to serve.\n" << "\n"
				<< "   Status: preparing\n" << "1. Input the order number to process the order with status \"preparing\".\n"
				<< "2. Type the correct order of ingredient following the Burger Ingredient List.\n"
				<< "   You just need to input the first character of each ingredient.\n"
				<< "   If the input is correct, the system returns to the order list.\n"
				<< "   The status of that order will change to \"cooking\".\n" << "\n"
				<< "   Status: cooking\n" << "1. When the burger is in the \"cooking\" status, you have to wait until it is done.\n"
				<< "   Tips: You can cook other burgers to save time.\n"
				<< "   If the burger is cooked, the status of the burger will be changed from \"cooking\" to \"ready to serve\". \n";
			cout << "   Status: ready to serve\n" << "1. Type the order number of the order with status \"ready to serve\" to serve the order.\n\n";
			system("pause");
			system("cls");
			break;
		case '2': cout << "   Game Rules\n" << "1. When the game starts, you will initially have 10 marks.\n"
			<< "2. If the order is served on time, 10 marks will be awarded.\n"
			<< "   But if the order cannot be served within the time limit, 5 marks will be deducted.\n"
			<< "3. The game finishes when the score < 0 and you will be returned to the Game Menu.\n\n";
			system("pause");
			system("cls");
			break;
		case '3': cout << "   Time limit\n" << "1. All order of all types of burger are same.\n"
			<< "2. The time limit is defaulted as 40 seconds\n" << "3. You can change it by choosing \"[2] Settings\" at the Game Menu.\n\n";
			system("pause");
			system("cls");
			break;
		case '4': cout << "   How to quit the game\n" << "You can input ‘q’ or ‘Q’ in the order list page to quit the game.\n\n";
			system("pause");
			system("cls");
			break;
		case '5': demo(); system("cls"); break;
		case '6': break;
		default: cout << "Invalid input, please input again. \n\n";
			system("pause");
			system("cls");
			break;
		}
	} while (instruct_choice != '6');
}

void credit() {
	string line(50, '-');
	cout << left << setw(15) << "Name" << setw(15) << "Student ID" << setw(10) << "Class" << "Tutorial\n"
		<< line << "\n"
		<< left << setw(15) << "Ng Ho Tin" << setw(15) << "18188135A" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "Ho Kwong Wa" << setw(15) << "18006958A" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "Tam Chi Hong" << setw(15) << "18031710A" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "Lee Hei Tung" << setw(15) << "18024104A" << setw(10) << "203" << "Group A\n"
		<< setw(15) << "Pau Chun Wai" << setw(15) << "18071191A" << setw(10) << "203" << "Group A\n";
	system("pause");
	system("cls");
}

void starting_screen()
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	Sleep(300);
	SetConsoleTextAttribute(color, 10);
	cout << "    ___  ___    ___   _  __  _____  ___   __      __ ___  _  _ " << endl;
	Sleep(200);
	SetConsoleTextAttribute(color, 11);
	cout << "   / __|/ _ \\  / _ \\ | |/ / |_   _|/ _ \\  \\ \\    / /|_ _|| \\| |" << endl;
	Sleep(150);
	SetConsoleTextAttribute(color, 12);
	cout << "  | (__| (_) || (_) || ' <    | | | (_) |  \\ \\/\\/ /  | | | .` |" << endl;
	Sleep(200);
	SetConsoleTextAttribute(color, 13);
	cout << "   \\___|\\___/  \\___/ |_|\\_\\   |_|  \\___/    \\_/\\_/  |___||_|\\_|" << endl;
	SetColor();
	cout << "\n\nCan you win this game?" << endl;
	cout << "\nTips: FULLSCREEN WILL HAVE A BETTER PLAYING ENVIRONMENT :)" << endl;
	system("pause");
	system("cls");
}

void random_helping_msg(int a)
{
	SetConsoleTextAttribute(color, (rand()%8+2));
	switch (a)
	{
	case 1:cout << "If you don't know how tp play the game, try to click [4] Instructions. A demo teacher will help you!"; break;
	case 2:cout << "You can type [2] to set the basic value!"; break;
	case 3:cout << "Before to play the game, read the [3] Burger Menus first "; break;
	default:cout << "Good luck, have fun, don't mad :) "; break;
	}
	SetColor();
	cout << endl << endl;
}

int main() {
	char user_choice[2];
	List mylist;

	starting_screen();

	do	// Main meun
	{
		cout << "Yb        dP       8                                w             w   8              .d88b             8    w               .d88b                       8 8 8 " << endl;
		cout << " Yb  db  dP  .d88b 8 .d8b .d8b. 8d8b.d8b. .d88b    w8ww .d8b.    w8ww 8d8b. .d88b    8P    .d8b. .d8b. 8.dP w 8d8b. .d88    8P www .d88 8d8b.d8b. .d88b 8 8 8 " << endl;
		cout << "  YbdPYbdP   8.dP' 8 8    8' .8 8P Y8P Y8 8.dP'     8   8' .8     8   8P Y8 8.dP'    8b    8' .8 8' .8 88b  8 8P Y8 8  8    8b  d8 8  8 8P Y8P Y8 8.dP' \" \" \" " << endl;
		cout << "   YP  YP    `Y88P 8 `Y8P `Y8P' 8   8   8 `Y88P     Y8P `Y8P'     Y8P 8   8 `Y88P    `Y88P `Y8P' `Y8P' 8 Yb 8 8   8 `Y88    `Y88P' `Y88 8   8   8 `Y88P w w w " << endl;
		cout << "                                                                                                                    wwdP                                      " << endl;
		random_helping_msg(rand() % 3 + 1);
		cout << "*** Game Menu ***\n";
		cout << "[1] Start Game\n";
		cout << "[2] Settings\n";
		cout << "[3] Burger Menus\n";
		cout << "[4] Instructions\n";
		cout << "[5] Credits\n";
		cout << "[6] Exit\n";
		cout << "=================\n";
		cout << "Option(1 - 6) : ";
		cin >> user_choice;
		cin.ignore();

		while (user_choice[1] != '\0')
		{
			system("cls");
			user_choice[1] = '\0';
			cout << "Yb        dP       8                                w             w   8              .d88b             8    w               .d88b                       8 8 8 " << endl;
			cout << " Yb  db  dP  .d88b 8 .d8b .d8b. 8d8b.d8b. .d88b    w8ww .d8b.    w8ww 8d8b. .d88b    8P    .d8b. .d8b. 8.dP w 8d8b. .d88    8P www .d88 8d8b.d8b. .d88b 8 8 8 " << endl;
			cout << "  YbdPYbdP   8.dP' 8 8    8' .8 8P Y8P Y8 8.dP'     8   8' .8     8   8P Y8 8.dP'    8b    8' .8 8' .8 88b  8 8P Y8 8  8    8b  d8 8  8 8P Y8P Y8 8.dP' \" \" \" " << endl;
			cout << "   YP  YP    `Y88P 8 `Y8P `Y8P' 8   8   8 `Y88P     Y8P `Y8P'     Y8P 8   8 `Y88P    `Y88P `Y8P' `Y8P' 8 Yb 8 8   8 `Y88    `Y88P' `Y88 8   8   8 `Y88P w w w " << endl;
			cout << "                                                                                                                    wwdP                                      " << endl;
			cout << "*** Game Menu ***\n";
			cout << "[1] Start Game\n";
			cout << "[2] Settings\n";
			cout << "[3] Burger Menus\n";
			cout << "[4] Instructions\n";
			cout << "[5] Credits\n";
			cout << "[6] Exit\n";
			cout << "=================\n";
			SetConsoleTextAttribute(color, 10);
			cout << "Invalid input! Enter again!";
			SetColor();
			cout << endl << "Option(1 - 6) : ";
			cin >> user_choice;
			cin.ignore();
		}

		switch (user_choice[0])
		{
		case '1':system("cls"); game_start(mylist); break;
		case '2':system("cls"); settingsMenu(); break;
		case '3':system("cls"); burgerMenu(mylist); break;
		case '4':system("cls"); instructions(); break;
		case '5':system("cls"); credit(); break;
		case '6':do {
			system("cls");
			cout << "Are you really want to quit? (Y/N)\n";
			cin >> user_choice;
			cin.ignore();
			if (user_choice[0] != 'Y' && user_choice[0] != 'y' && user_choice[0] != 'N' && user_choice[0] != 'n')
			{
				cout << "Invalid input, please input again. \n";
				system("pause");
			}
		} while (user_choice[0] != 'Y' && user_choice[0] != 'y' && user_choice[0] != 'N' && user_choice[0] != 'n');
		default: cout << "Invalid input, please input again. \n\n"; system("pause"); break;
		}

		system("cls");

	} while (user_choice[0] != 'Y' && user_choice[0] != 'y');
	cout << "Good bye!" << "\n";
	system("pause");
	return 0;
}