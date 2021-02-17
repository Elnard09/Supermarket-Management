#ifndef LOGINADMIN_H
#define LOGINADMIN_H
#include<string.h>
#include<string>
#include<iostream>

using namespace std;

class LoginAdmin
{

    private:
        string password;
        string passWord = "12345678910111213";
        bool accessGranted;

    public:

        LoginAdmin();

        void logIn();

};

#endif // LOGINADMIN_H
