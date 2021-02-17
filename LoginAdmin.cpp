#include "LoginAdmin.h"
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<string>
#include<iostream>
#include <Windows.h>

	string password;
	string passWord = "12345678910111213";
	bool accessGranted;

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
        cout << "\n\n............Successfully log in............\n";
        getch();
    }
    else
    {
        system("cls");
        cout << "............Invalid password............\n";
        logIn();
    }


};
