#include "Product.h"
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<string>
#include<iostream>
#include <Windows.h>
#include<limits>

void Product::create_product()
{

    Product objProduct;
    fstream dataFile;

    bool found=false;
    cout<<endl<<"===========================================\n";
    cout << "Please Enter The Product Number: ";
    cin >> product_number;
    dataFile.open("database.dat",ios::in|ios::out);
	while(dataFile.read((char*)&objProduct,sizeof(Product)) && found==false)
    {
        if(objProduct.getProduct()==product_number)
        {
            display("\nThat product number is already exist: ", "LIGHTRED");
            cin >> product_number;
            found = true;
        }
    }
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            display("You have entered wrong input: ", "LIGHTRED");
            cin>>product_number;
        }
        if(!cin.fail())
        break;
    }

    cout << endl << "Please Enter The Name of The Product: ";
    cin.ignore();
    cin.getline(product_name ,50);
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            display("You have entered wrong input: ", "LIGHTRED");
            cin>>product_name;
        }
        if(!cin.fail())
        break;
    }

    cout << endl << "Please Enter The Price of The Product: ";
    cin >> product_price;
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            display("You have entered wrong input: ", "LIGHTRED");
            cin>>product_price;
        }
        if(!cin.fail())
        break;
    }

    cout << endl << "Please Enter The Quantity of The Product: ";
    cin >> product_quantity;
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            display("You have entered wrong input: ", "LIGHTRED");
            cin>>product_quantity;
        }
        if(!cin.fail())
        break;
    }

    cout << endl << "Please Enter The Discount (%): ";
    cin >> product_discount;
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            display("You have entered wrong input: ", "LIGHTRED");
            cin>>product_discount;
        }
        if(!cin.fail())
        break;
    }


}

void Product::show_product()
{
    cout << endl << "\nProduct #: " << product_number;
    cout << endl << "\nProduct Name: " << product_name;
    cout << endl << "\nProduct Price: " << product_price;
    cout << endl << "\nProduct Quantity: " << fixed << setprecision(0) << product_quantity;
    cout << endl << "\nDiscount : " << fixed << setprecision(0) << product_discount << "%";
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
void Product::display(string my_str, string color){

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

