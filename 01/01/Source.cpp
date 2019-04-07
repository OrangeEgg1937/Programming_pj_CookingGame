#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int max_type = 10, max_burger = 10;
int min_type = 8, min_burger = 5, max_order = 5, time_limit = 40; //max number of order = 50

class Countdown
{
public:
	void startCount(int s) {

		finishTime = time(0) + s;
	}
	int printTime() {
		return finishTime - time(0);
	}
private:

	int finishTime;
};
/*class Time
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
};*/

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
	ingredients_list[0].modify("Bread", 'B');
	ingredients_list[1].modify("Cheese", 'C');
	ingredients_list[2].modify("Beef", 'F');
	ingredients_list[3].modify("Lettuce", 'L');
	ingredients_list[4].modify("Tomato", 'T');
	ingredients_list[5].modify("Mushroom", 'M');
	ingredients_list[6].modify("Egg", 'E');
	ingredients_list[7].modify("Salmon", 'S');
	for (int i = 5; i < max_type; i++)
	{
		burger_list[i].modify("", "", 0);
	}
	for (int i = 8; i < max_type; i++)
	{
		ingredients_list[i].modify("NO",'N');
	}
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

                         //mylist,timer,order,choice,status  //ordernum=burgernum
/*void game_start_order(List a,Countdown timer[],int orderarr[],int ordernum,int status[])
{
	string choice;
	system("CLS");
	cout << "*** Process Order ***" << endl;
	cout << left << setw(22) << "Order #" << ": " << ordernum << endl;
	cout << setw(22) << "Burger" << ": " << a.call_burger_name(orderarr[ordernum])<<endl; //order[choice] e.g order[2]
	cout << setw(22) << "Status" << ": "  ;
	switch (status[ordernum]) {
	case 0:cout << "preparing" << endl; break;
	case 1:cout << "cooking" << endl; break;
	case 2:cout << "ready to serve" << endl; break;
	}
	cout << setw(22) << "Remaining Time" << ": "
		<<timer[orderarr[ordernum]].printTime() / 60 
		<< "'" << timer[orderarr[ordernum]].printTime() % 60 << "\"" << endl;
	cout << "Please choose [U] for update, [R] for return, or" << endl;
	cout << "type correct key list to start cooking : ";
	cin >> choice;
	if (choice == "U")game_start_order(a, timer, orderarr, ordernum, status);
};

void game_update_1(List a,Countdown timer[],int status[],int score,int order[]){
	system("CLS");
	cout << "*** Order list ***" << endl;
	for (int i = 1; i <= max_order; i++)
	{
		cout << "Order #" << i << ": " << a.call_burger_name(order[i]) << ", ";
		switch (status[i]) {
			case 0:cout << "preparing, "; break;
			case 1:cout << "cooking, "; break;
			case 2:cout << "ready to serve, "; break;
		}

		cout<< timer[i].printTime()/60<<"'"<< timer[i].printTime() % 60<<"\"" << endl;
	}
	cout << "-----------------------------------------------" << endl;
	cout << "Score: " << score << endl;
	cout << "Enter [U] for update, [Q] for Quit, or [1-5] for order: ";
}
void game_start(List a)
{
	int order[50];
	int status[50] = {};  //default 0 = preparing   //0-preparing 1-cooking 2-ready to serve
	char choice; //user input
	int score = 10; //default score
	Countdown timer[50]; //timer of each order
	srand(time(0));
	cout << "*** Order list ***" << endl;
	for (int i = 1; i <= max_order; i++)
	{
		order[i]= 0 + rand() % (max_order);  //create order
		timer[i].startCount(time_limit); //start the timer of that order
	}
		game_update_1(a, timer, status, score,order); //all order update
		do {
			cin >> choice;
			if (choice == 'U' || choice =='u') game_update_1(a, timer, status, score,order);
			else if (int(choice)-48 >= 1 && int(choice)-48 <= max_order) { //ascii 
				game_start_order(a,timer, order, int(choice)-48, status);
			}
		} while (choice !='Q');
}*/
void game_start(List a)
{
	int order[50];
	int status[50] = {};  //default 0 = preparing   //0-preparing 1-cooking 2-ready to serve
	char choice; //user input
	int score = 10; //default score
	int temp;
	Countdown timer[50]; //timer of each order
	srand(time(0));
	for (int i = 1; i <= max_order; i++)
	{
		order[i] = 0 + rand() % (max_order);  //create order
		timer[i].startCount(time_limit); //start the timer of that order
	}
	do {
		do{
			system("CLS");
			cout << "*** Order list ***" << endl;
			for (int i = 1; i <= max_order; i++)
			{
				cout << "Order #" << i << ": " << a.call_burger_name(order[i]) << ", ";
				switch (status[i]) {
				case 0:cout << "preparing, "; break;
				case 1:cout << "cooking, "; break;
				case 2:cout << "ready to serve, "; break;
				}
				cout << timer[i].printTime() / 60 << "'" << timer[i].printTime() % 60 << "\"" << endl;
			}
			cout << "-----------------------------------------------" << endl;
			cout << "Score: " << score << endl;
			cout << "Enter [U] for update, [Q] for Quit, or [1-"<<max_order<<"] for order: ";
			cin >> choice;
		}while (choice == 'U');
		while ((choice != 'Q') && ((int)(choice)-48 >= 1) && ((int)(choice)-48 <= max_order)) {
			do {
				if (choice == 'U')choice = temp;
				system("CLS");
				cout << "*** Process Order ***" << endl;
				cout << left << setw(22) << "Order #" << ": " << (int)choice - 48 << endl;
				cout << setw(22) << "Burger" << ": " << a.call_burger_name(order[(int)(choice)-48]) << endl;
				cout << setw(22) << "Status" << ": ";
				switch (status[(int)(choice)-48]) {
				case 0:cout << "preparing" << endl; break;
				case 1:cout << "cooking" << endl; break;
				case 2:cout << "ready to serve" << endl; break;
				}
				cout << setw(22) << "Remaining Time" << ": "
					<< timer[order[(int)(choice)-48]].printTime() / 60
					<< "'" << timer[order[(int)(choice)-48]].printTime() % 60 << "\"" << endl;
				cout << "Please choose [U] for update, [R] for return, or" << endl;
				cout << "type correct key list to start cooking : ";
				temp = choice;
				cin >> choice;	
			} while (choice == 'U');
			if (choice=a.call_burger_ingredients(order[(int)(temp)-48])
		}	
	}while (choice != 'Q');
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