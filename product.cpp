#include "Product.h"
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<string>
#include<iostream>
#include <Windows.h>
#include "LoginAdmin.h"

void Product::create_product()
{
    cout << endl << "Please Enter The Product Number: ";
    cin >> product_number;

    cout << endl << "Please Enter The Name of The Product: ";
    cin.ignore();
    cin.getline(product_name ,50);

    cout << endl << "Please Enter The Price of The Product: ";
    cin >> product_price;

    cout << endl << "Please Enter The Quantity of The Product: ";
    cin >> product_quantity;

    cout << endl << "Please Enter The Discount (%): ";
    cin >> product_discount;

	}

void Product::show_product()
{
    cout << endl << "\nProduct #: " << product_number;
    cout << endl << "\nProduct Name: " << product_name;
    cout << endl << "\nProduct Price: " << product_price;
    cout << endl << "\nProduct Quantity: " << product_quantity;
    cout << endl << "\nDiscount : " << product_discount;
}

int Product::getProduct()
{
    return product_number;
}

float Product::getPrice()
{
    return product_price;
}

char* Product::getName()
{
    return product_name;
}

float Product::getQuantity()
{
    return product_quantity;
}

float Product::getDiscount()
{
    return product_discount;
}
