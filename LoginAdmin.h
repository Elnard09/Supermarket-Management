#ifndef LOGINADMIN_H
#define LOGINADMIN_H
#include<string.h>
#include<string>
#include<iostream>

using namespace std;

void textColor(string my_str, string color);

class LoginAdmin
{

    private:
        string password;
        string passWord = "12345678910111213";
        bool accessGranted;

    public:

        LoginAdmin();

        void logIn();
        void textColor(string my_str, string color);

};

#endif // LOGINADMIN_H
