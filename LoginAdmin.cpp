#include "LoginAdmin.h"
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<string>
#include<iostream>
#include <Windows.h>

LoginAdmin::LoginAdmin()
         {
            accessGranted = 0;
         }

void LoginAdmin::logIn()
{
    password = "";

    cout << "\nEnter password: ";
    char ch = getch();
    int counter = 0;
    while(ch != 13)
    {
        if (ch == 8)
        {
            system("cls");
            cout << "Enter password: ";
            counter--;
            for(int i = 0; i < counter; i++)
            {
                cout << "*";
            }
            password = password.substr(0,password.length() - 1);

        }
        else
        {
            cout << "*";
            counter++;
            password.push_back(ch);
        }
        ch = getch();

    }
    string givenPassWord = "12345678910111213";
    if (givenPassWord == password)
    {
        textColor("\n\n............Successfully log in............\n", "LIGHTGREEN");
        getch();
    }
    else
    {
        system("cls");
        textColor("............Invalid password............\n", "LIGHTRED");
        logIn();
    }
}
void LoginAdmin::textColor(string my_str, string color){

	int num_color = 0;
	if (color == "BLUE"){
		num_color = 1;
	}
	else if (color == "GREEN"){
		num_color = 2;
	}
	else if (color == "CYAN"){
		num_color = 3;
	}
	else if (color == "RED"){
		num_color = 4;
	}
	else if (color == "MAGENTA"){
		num_color = 5;
	}
	else if (color == "BROWN"){
		num_color = 6;
	}
	else if (color == "LIGHTGREY"){
		num_color = 7;
	}
	else if (color == "DARKGREY"){
		num_color = 8;
	}
	else if (color == "LIGHTBLUE"){
		num_color = 9;
	}
	else if (color == "LIGHTGREEN"){
		num_color = 10;
	}
	else if (color == "LIGHTCYAN"){
		num_color = 11;
	}
	else if (color == "LIGHTRED"){
		num_color = 12;
	}
	else if (color == "LIGHTMAGENTA"){
		num_color = 13;
	}
	else if (color == "YELLOW"){
		num_color = 14;
	}
	else if (color == "WHITE"){
		num_color = 15;
	}
	else if (color == "BLINK"){
		num_color = 128;
	}

	// text color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num_color);
	cout << my_str;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

}
