#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>

using namespace std;

const int max_type = 10, max_burger = 10;//i change temporary

int min_type = 8, min_burger = 5, max_order = 5, time_limit = 40; 

class Countdown
{
public:

	Countdown() {
		Timedue = finishtime = 0;
	}
	void startCount(){

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

	int Timedue,finishtime;

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
	int cooking_time,burger_code; // burger_code = -1 means no such burger

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
			burger_list[i].modify("", "", 0,-1);
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
	    food = food_list.call_burger(rand() % (min_burger-1));
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
	int status=0, end_time=0, check_order=0;  //default 0 = preparing  [0-preparing 1-cooking 2-ready to serve 3-fail to finish order 4-order closed]
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
		cout << "Order #:" << i + 1 << ": ";
		cout << a[i].show_order_name() << ", ";
		cout << a[i].show_status() << ", ";
		cout << a[i].show_order_time() / 60 << "'" << a[i].show_order_time() - (a[i].show_order_time() / 60 * 60) << "\"" << endl;
	}
	cout << "----------------------------------------------" << endl;
	cout << "Score: " << score << endl;
	cout << "Enter[U] for update, [Q] for Quit, or [1 - " << max_order << "] for order :" << endl;
}

void show_single_order(Order list[],int i)
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
			
			if (input == list[i].show_ingredient_order() && list[i].show_status()=="preparing")
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
	Order *player_order = new Order [max_order]; // Dynamic memory for order, size of order depends on "max_order"

	char choice[3] = { '0','0','\0' }; //user input and data validation
	int order=0;
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


		} while (choice[0] == 'U' || choice[0] == 'u' || choice[2] != '\0' );

		if (choice[1] == '\0')
		{
			choice[1] = '0';
		}
		if (choice[0] == 'Q' || choice[0] == 'q')
		{
			break;
		}

		order = ((int)choice[0] - 48) + (((int)choice[1] - 48) * 10); // Char to integer
		show_single_order(player_order, order-1);

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
	string user_choice = "1";
	List mylist;
	char go;
	
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
		cout << "[8] Show Order\n";
		cout << "*****************\n";
		cout << "Option(1 - 6) : ";
		cin >> user_choice;
		go = user_choice[0];

		system("cls");

		switch (go)
		{
		case '1':game_start(mylist); break;
		case '2':/*setting()*/; break;
		case '7':show_list(mylist); break;
		case '8':show_orderlist(mylist); break;
		}

		system("pause");
		system("cls");

	} while (user_choice != "6");
	return 0;
}