#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>

using namespace std;

const int max_type = 10, max_burger = 10;
int min_type = 8, min_burger = 5, max_order = 5, time_limit = 40; 

class Countdown
{
public:
	Countdown() {
		Timedue = finishtime = 0;
	}
	void startCount(int s) {

		Timedue = time(0) + s;
	}
	void cookCount(int s)
	{
		finishtime = time(0) + s;
	}
	int printTime() {
		return Timedue - time(0);
	}
	int printcooktime() {
		return finishtime - time(0);
	}
private:

	int Timedue,finishtime;

};

class Burger
{
public:

	void modify(string define_name, string order, int time)
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

	string call_order()
	{
		return ingredient_order;
	}

	int call_cooktime()
	{
		return cooking_time;
	}

private:
	string name, ingredient_order;
	int cooking_time;

};

class Ingredient
{
public:

	void modify(string a,char b)
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

	List();

	void modify()
	{

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
			for(int j = 0; j < min_type; j++)
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

List::List() 	// Set up default value of ingredients                    
{
	burger_list[0].modify("Cheese burger", "BCFLB", 10);
	burger_list[1].modify("Beef burger", "BCTMLB", 10);
	burger_list[2].modify("Mushroom burger", "BCFMB", 15);
	burger_list[3].modify("Veggie burger", "BTELB", 10);
	burger_list[4].modify("Salmon burger", "BCFSB", 15);
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
		burger_list[i].modify("", "", 0);
	}
	for (int i = 8; i < max_type; i++)
	{
		ingredients_list[i].modify("NO",'N');
	}
}
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
		cout <<setw(8) << a.call_ingredients_sname(i) << "/" << char(a.call_ingredients_sname(i)+32);
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
void generate_new_order(Countdown timer[],int order[],int status[],int &total_order)
{
	int randaccu = 1; 
	if (total_order < max_order)  //Generate new order when a order is less than then total with probability
	{
		if (0 + rand() % 2 == 0)
		{
			srand((time(0))*randaccu++);//Prevent only the same burger will become a order in a second
			total_order += 1;
			order[total_order + 1] = 0 + rand() % max_order;  //create order   //error
			timer[total_order + 1].startCount(time_limit); //start the timer
			status[total_order + 1] = 0;
		}
	}
}

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
void game_start(List a)
{
	int order[51] = {};
	int status[51] = {};  //default 0 = preparing   //0-preparing 1-cooking 2-ready to serve
	char choice; //user input
	int score = 10; //default score
	int temp, total_order = max_order;
	bool pass = 1;
	Countdown timer[51]; //timer of each order
	srand(time(0));
	for (int i = 1; i <= max_order; i++)
	{
		order[i] = 0 + rand() % (max_order);  //create order
		timer[i].startCount(time_limit); //start the timer of that order
	}
	while (score >= 0 || choice != 'Q') {
		do {
			system("CLS");
			for (int i=1;i<=total_order;i++){
				check_order_expired(a, timer, order, status, total_order, score,i);
			}
			if (total_order < max_order)  //Generate new order when a order is less than then total with probability
			{
				if (rand() % 3 == 0)
				{
					order[total_order + 1] = 0 + rand() % max_order;  //create order   //error
					timer[total_order + 1].startCount(time_limit); //start the timer
					status[total_order + 1] = 0;
					total_order += 1;
				}
			}
			display_order(a, timer, order, status, score, total_order);
			if (score < 0) break;//lose
			cout << "Enter [U] for update, [Q] for Quit, or [1-" << total_order << "] for order: ";
			cin >> choice;
		} while (choice == 'U' || choice == 'u');
		if (score < 0) break;//lose
		if (((int)(choice)-48 >= 1) && ((int)(choice)-48 <= total_order) && status[(int)(choice)-48] == 2) {
			score += 10;
			status[(int)(choice)-48] = 0;
			sorting(order, status, timer, (int)(choice)-48, total_order);
		}
		else {
			while ((choice != 'Q') && ((int)(choice)-48 >= 1) && ((int)(choice)-48 <= total_order)) {
				string input;
				do {
					if (choice == 'U')choice = temp;
					display_process(a, timer, status, order, choice);
					if (pass == 0) {
						SetColor(252);
						cout << "Wrong Input!!!" << endl;
						SetColor();
					}
					cout << "Please choose [U] for update, [R] for return, or" << endl;
					cout << "type correct key list to start cooking : ";
					temp = choice;
					cin >> input;
				} while (input == "U");
				if (input == a.call_burger_ingredients(order[(int)(choice)-48]))
				{
					pass = 1;
					status[(int)(choice)-48] = 1;
					timer[(int)(choice)-48].cookCount(a.call_burger_time(order[(int)(choice)-48]));
					break;
				}
				else if (input == "R") break;
				else pass = 0;
			}
		}
	}
}

void setting()
{

}


int main() {
	string user_choice = "1";
	char go;
	List mylist;
	
	do	// Main meun
	{

		if (user_choice != "1" && user_choice != "2" && user_choice != "3" && user_choice != "4" && user_choice != "5" && user_choice != "7")	// Data validation
		{
			cout << "Invalid input, try again! (TESTING) \n\n";
			go = 'N';
		}

		cout << "A good Welcome Message will be designed by someone\n\n";
		cout << "*** Game Menu ***\n";
		cout << "[1] Start Game\n";
		cout << "[2] Settings\n";
		cout << "[3] Burger Menus\n";
		cout << "[4] Instructions\n";
		cout << "[5] Credits\n";
		cout << "[6] Exit\n";
		cout << "=================\n";
		cout << "TEST Meun:\n";
		cout << "[7] Show List\n";
		cout << "*****************\n";
		cout << "Option(1 - 6) : ";
		cin >> user_choice;
		go = user_choice[0];

		system("cls");

		switch (go)
		{
		case '1':game_start(mylist); break;
		case '2':setting(); break;
		case '7':show_list(mylist); break;
		}

		system("pause");
		system("cls");

	} while (user_choice != "6");
	return 0;
}