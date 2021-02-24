#ifndef PRODUCT_H
#define PRODUCT_H
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<string>
#include<iostream>
#include <Windows.h>

using namespace std;

void display(string my_str, string color);

class Product
{
    private:
        int product_number;
        char product_name[50],addanotherornot;
        float product_price,product_quantity,tax,product_discount;

	public:

        void create_product();
        void show_product();
        int getProduct();
        float getPrice();
        char* getName();
        float getQuantity();
        float getDiscount();
        void display(string my_str, string color);
};

#endif // PRODUCT_H
