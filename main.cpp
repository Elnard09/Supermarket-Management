#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<string>
#include<iostream>
#include <Windows.h>
#include "LoginAdmin.h"
#include "product.h"

using namespace std;

string g_system_name = "SUPERMARKET MANAGEMENT SYSTEM";

void display(string my_str, string color);
void membership(float totalAmount);
void change(char availSukiCard, char memberSukiCard, float totalAmount, float totalAmountWithSukiCard);






fstream fp;
product produc;


void save_product()
{
    char addanotherornot;

	fp.open("database.dat",ios::out|ios::app);
	produc.create_product();
	fp.write((char*)&produc,sizeof(product));
	fp.close();
	cout << endl <<"Do you want to add another product? y/n: ";
    cin >> addanotherornot;
            while (addanotherornot == 'y' || addanotherornot == 'Y')
            {
                fp.open("database.dat",ios::out|ios::app);
                produc.create_product();
                fp.write((char*)&produc,sizeof(product));
                fp.close();
                cout << endl <<"Do you want to add another product? y/n: ";
                cin >> addanotherornot;
            }
	cout << endl;
	cout << endl;
	display("The Product/s Has Been Sucessfully Created...", "LIGHTGREEN");
	getchar();
}


void show_all_product()
{
	system("cls");
	cout<<endl<<"\t\t===========================================";
	cout<<endl<<"\t\tRECORDS.";
	cout<<endl<<"\t\t===========================================\n";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.show_product();
		cout<<endl<<"==========================================\n"<<endl;
		getchar();
	}
	fp.close();
}


void display_record(int num)
{
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()==num)
		{
			system("cls");
			produc.show_product();
			found=true;
		}
	}

	fp.close();
	if(found == true)
	cout<<"\n\nNo record found";
	getchar();
}



void edit_product()
{
	int num;
	bool found=false;
	system("cls");
	cout<<endl<<endl<<"\tPlease Enter The Product #: ";
	cin>>num;

	fp.open("database.dat",ios::in|ios::out);
	while(fp.read((char*)&produc,sizeof(product)) && found==false)
	{
		if(produc.getProduct()==num)
		{
			produc.show_product();
			cout<<"\nPlease Enter The New Details of Product: "<<endl;
			produc.create_product();
			int pos=-1*sizeof(produc);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&produc,sizeof(product));
			cout<<endl<<endl;
			display("\t Record Successfully Updated...", "LIGHTGREEN");
			found=true;
		}
	}
	fp.close();
	if(found==false)
		cout<<endl<<endl<<"Record Not Found...";
	getchar();
}


void delete_product()
{
	int num;
	system("cls");
	cout<<endl<<endl<<"Please Enter The product #: ";
	cin>>num;
	fp.open("database.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()!=num)
		{
			fp2.write((char*)&produc,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("database.dat");
	rename("Temp.dat","database.dat");
	cout<<endl<<endl;
	display("\tRecord Deleted...", "LIGHTGREEN");
	getchar();
}


void product_menu()
{

	system("cls");
	fp.open("database.dat",ios::in);

	display("\n\n\t\t\t\t\PRODUCT MENU\n\n", "YELLOW");
	cout<<"==================================================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\t\tDiscount\tAvailable Stocks\n";
	cout<<"==================================================================================\n";
	while(fp.read((char*)&produc,sizeof(product)))
	{
		cout << produc.getProduct() << "\t\t" << produc.getName();
		cout << "\t\t" << setprecision(2) << fixed <<produc.getPrice();
		cout << "\t\t" << setprecision(0) << produc.getDiscount()<<"%";
		cout << "\t\t"<< setprecision(0) << fixed <<produc.getQuantity()<< endl;
	}
	fp.close();
}



void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0, totalMemberDiscount;
	char ch = 'Y';
	string custName, custAddress, custContactNum;

	product_menu();
	cout<<"\n================================================";
	cout<<"\n PLACE YOUR ORDER";
	cout<<"\n================================================\n";
	do{
		cout<<"\n\nEnter The Product #: ";
		cin>>order_arr[c];
		cout<<"\nQuantity: ";
		cin>>quan[c];
		/**
		fp.open("database.dat",ios::in | ios::binary);
		fp.seekg((quan[c]), ios::beg);
		while(fp.read(reinterpret_cast<char *>(&produc), sizeof(product)))
        {


            while ( produc.getQuantity() < quan[c] )
            {
                cout << "\nOut of stock.\nEnter another Quantity not exceeding ";
                cout << stoi(produc.getQuantity(), 0, 2)<< " : ";
                cin >> quan[c];
            }
        }
        fp.close();
        **/

		c++;
		cout<<"\nDo You Want To Order Another Product ? (y/n)";
		cin>>ch;
		}while(ch=='y' ||ch=='Y');
	display("\n\nThank You...", "LIGHTGREEN");
	getchar();
	getch();
	system("cls");
	display("\n\n\t\t\t\tRECEIPT\n", "YELLOW");
	cout<<"==================================================================================\n";
	cout<<"Pr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
	cout<<"==================================================================================\n";
	for(int x=0;x<=c;x++)
	{
		fp.open("database.dat",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{
			if(produc.getProduct() == order_arr[x])
			{
				amt = produc.getPrice()* quan[x];
				damt = amt-(amt*produc.getDiscount()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<produc.getName()<<"\t"<<quan[x]<<"\t\t"<< fixed <<setprecision(2) <<produc.getPrice()<<"\t"<<amt<<"\t\t"<<damt;
				total += damt;
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}
	cout << setprecision(2);
	cout<<"\n\n\t\t\t\t\t\tTOTAL = "<<total;
	cout << endl;

	membership(total);

	getchar();
}

void membership(float totalAmount)
{

	float totalMemberDiscount;
	char sukiCard = 'Y', availSukiCard = 'Y';
	string custName, custAddress, custContactNum;

    cout << "------------------------------------------------------------------------\n";
	cout << "\nDo you have Suki Card? (y/n) ";
	cin >> sukiCard;

	if (sukiCard == 'y' || sukiCard == 'Y')
    {
        totalMemberDiscount = totalAmount - (totalAmount * 0.1);
        cout << "\n-------------------------------------------------------------------\n";
        cout << setprecision(2);
        cout << "\n\t\t\tTotal Amount with Suki Card Discount= " << totalMemberDiscount;
        display("\n\n\n\n\t\"Thank you for availing our Suri Card.\"\n", "LIGHTGREEN");

    }
    else
    {
        cout << "\nDo you want to avail Suki Card? (y/n) ";
        cin >> availSukiCard;
        if (availSukiCard == 'y' || availSukiCard == 'Y')
        {

            cout << "\nPlease fill up the needed information.\n";

            cout << "\nEnter your name: ";
            cin >> custName;
            cout << "\nEnter your contact number: ";
            cin >> custContactNum;
            cin.ignore();

            cout << "\nEnter your address: ";
            cin >> custAddress;

            totalMemberDiscount = totalAmount - (totalAmount * 0.1);
            cout << "\n----------------------------------------------------------------------\n";
            cout << setprecision(2);
            cout << "\n\t\t\t\tTotal Amount with Suki Card Discount= " << totalMemberDiscount;
            display("\n\n\n........Thank you for availing our Suri Card............\n", "LIGHTGREEN");
            getchar();
        }
        else
        {
            getch();
        }

    }
    change(availSukiCard, sukiCard, totalAmount, totalMemberDiscount);

}

void change(char availSukiCard, char memberSukiCard, float totalAmount, float totalAmountWithSukiCard)
{
    float payment, totalChange;
    if (memberSukiCard == 'y' || memberSukiCard == 'Y' || availSukiCard == 'y' || availSukiCard == 'Y')
    {
        cout << "\n\nEnter your payment: ";
        cin >> payment;
        totalChange = payment - totalAmountWithSukiCard;
        cout << setprecision(2) << "\nYour change is " << totalChange;
        cout << endl;
        getch();
        system("cls");

    }
    else
    {
        cout << "\n\nEnter your payment: ";
        cin >> payment;
        totalChange = payment - totalAmount;
        cout << setprecision(2) << "\nYour change is " << totalChange;
        cout << endl;
        getch();
        system("cls");

    }


}

void admin_menu()
{
	system("cls");

	int option;

	display("\n\t=============================================","LIGHTCYAN");
	display("\n\tPress 1 to CREATE PRODUCT", "LIGHTCYAN");
	display("\n\tPress 2 to DISPLAY ALL PRODUCTS", "LIGHTCYAN");
	display("\n\tPress 3 to MODIFY PRODUCT", "LIGHTCYAN");
	display("\n\tPress 4 to DELETE PRODUCT", "LIGHTCYAN");
	display("\n\tPress 5 to GO BACK TO MAIN MENU", "LIGHTCYAN");
	display("\n\t============================================", "LIGHTCYAN");

	cout<<"\n\n\tOption: ";
	cin>>option;
	switch(option)
	{
		case 1: system("cls");
				save_product();
				break;

		case 2: show_all_product();
				break;

		case 3: edit_product();
		break;

		case 4: delete_product();
		        break;

		case 5: system("cls");
				break;

		default:admin_menu();
	}
}
void display(string my_str, string color){

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

void myHeader(){
	display("***"+g_system_name+"***\n","YELLOW");
}

int main(int argc, char *argv[])
{
	system("cls");
	system("color 07");

	int option;

	for(;;)
	{
	    myHeader();
		display("\n===========================================", "LIGHTCYAN");
		display("\n1. CUSTOMER", "LIGHTCYAN");
		display("\n2. ADMINISTRATOR", "LIGHTCYAN");
		display("\n3. EXIT", "LIGHTCYAN");
		display("\n===========================================", "LIGHTCYAN");

		cout<<"\nOption: ";
		cin>>option;

		switch(option)
		{
			case 1: system("cls");
					place_order();
					getchar();
					break;

			case 2: {
                    system("cls");
                    LoginAdmin loginManagerObj;
                    loginManagerObj.logIn();
                    admin_menu();
					break;
					}

			case 3:{
					cout<<"\n\t===========================================";
					cout<<"\n\tGood Bye!";
					cout<<"\n\t===========================================\n";
					exit(0);
                    }

			default :
                    cout << endl;
                    display("Invalid Input...\n", "LIGHTRED");
		}

	}
}

