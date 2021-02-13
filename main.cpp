#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include <Windows.h>
#include "TextTable.h"

using namespace std;

string g_system_name = "SUPERMARKET MANAGEMENT SYSTEM";

void display(string my_str, string color);
void membership(float totalAmount);
void change(char availSukiCard, char memberSukiCard, float totalAmount, float totalAmountWithSukiCard);


class LoginAdmin{
    private:
	string password;
	string passWord = "12345678910111213";
	bool accessGranted;

	public:
	     LoginManager()
         {
            accessGranted = 0;
         }

	void logIn(){
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
            display("\n\n............Successfully log in............\n", "LIGHTGREEN");
            getch();
        }

		else
        {
			system("cls");
			display("............Invalid password............\n","LIGHTRED");
			logIn();
		}

    }
};



class product
{
	int product_number;
	char product_name[50],addanotherornot;
	float product_price,product_quantity,tax,product_discount;

	public:

	void create_product()
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

        cout << endl <<"Do you want to add another product? y/n: ";
        cin >> addanotherornot;
            if (addanotherornot == 'y')
            {
                return create_product();
            }

	}

	void show_product()
	{
		cout << endl << "\nProduct #: " << product_number;
		cout << endl << "\nProduct Name: " << product_name;
		cout << endl << "\nProduct Price: " << product_price;
		cout << endl << "\nProduct Quantity: " << product_quantity;
		cout << endl << "\nDiscount : " << product_discount;
	}

	int getProduct()
	{
		return product_number;
	}

	float getPrice()
	{
		return product_price;
	}

	char* getName()
	{
		return product_name;
	}

	float getQuantity()
	{
	    return product_quantity;
	}

	float getDiscount()
	{
		return product_discount;
	}
};




fstream fp;
product produc;


void save_product()
{
	fp.open("database.txt",ios::out|ios::app);
	produc.create_product();
	fp.write((char*)&produc,sizeof(product));
	fp.close();
	cout << endl;
	cout << endl;
	display("The Product Has Been Sucessfully Created...", "LIGHTGREEN");
	getchar();
}


void show_all_product()
{
	system("cls");
	cout<<endl<<"\t\t===========================================";
	cout<<endl<<"\t\tRECORDS.";
	cout<<endl<<"\t\t===========================================\n";
	fp.open("database.txt",ios::in);
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
	fp.open("database.txt",ios::in);
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

	fp.open("database.txt",ios::in|ios::out);
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
	fp.open("database.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.txt",ios::out);
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
	remove("database.txt");
	rename("Temp.txt","database.txt");
	cout<<endl<<endl;
	display("\tRecord Deleted...", "LIGHTGREEN");
	getchar();
}


void product_menu()
{
    TextTable t( '-', '|', '+' );
    t.add( "P.NO.");
    t.add( "NAME");
    t.add( "PRICE");
    t.add( "Discount");
    t.add( "Available Stocks");
    t.endOfRow();

	system("cls");
	fp.open("database.txt",ios::in);

	cout<<endl<<endl<<"\t\t\t\tProduct MENU\n\n";
	cout<<"==================================================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\t\tDiscount\tAvailable Stocks\n";
	cout<<"==================================================================================\n";
	while(fp.read((char*)&produc,sizeof(product)))
	{
		cout<<produc.getProduct()<<"\t\t"<<produc.getName()<<"\t\t"<<produc.getPrice()<<"\t\t"<<produc.getDiscount()<<"%"<<"\t\t"<<produc.getQuantity()<< endl;
	}
	fp.close();
}



void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0, totalMemberDiscount;
	char ch = 'Y', sukiCard = 'Y', availSukiCard = 'Y';
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
		fp.open("database.txt",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{
			if(produc.getQuantity() < quan[c])
			{
				cout << "Out of Stock!\nPlease enter Quantity not exceeding " << produc.getQuantity() << ": ";
				cin >> quan[c];
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
		c++;
		cout<<"\nDo You Want To Order Another Product ? (y/n)";
		cin>>ch;
		}while(ch=='y' ||ch=='Y');
	display("\n\nThank You...", "LIGHTGREEN");
	getchar();
	system("cls");
	cout<<"\n\n********************************RECEIPT************************\n";
	cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
	for(int x=0;x<=c;x++)
	{
		fp.open("database.txt",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{
			if(produc.getProduct() == order_arr[x])
			{
				amt = produc.getPrice()* quan[x];
				damt = amt-(amt*produc.getDiscount()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<produc.getName()<<"\t"<<quan[x]<<"\t\t"<< fixed <<setprecision(2) <<produc.getPrice()<<"\t"<<amt<<"\t\t"<<damt;
				total+=damt;
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}
	cout << setprecision(2);
	cout<<"\n\n\t\t\t\t\t\tTOTAL = "<<total;
	cout << endl;

	membership(total);
	change(availSukiCard, sukiCard, total, totalMemberDiscount);

	getchar();
}

void membership(float totalAmount)
{

	float totalMemberDiscount;
	char sukiCard = 'Y', availSukiCard = 'Y';
	string custName, custAddress, custContactNum;

    cout << "-------------------------------------------------------------------------------\n";
	cout << "Do you have Suki Card? (y/n) ";
	cin >> sukiCard;

	if (sukiCard == 'y' || sukiCard == 'Y')
    {
        totalMemberDiscount = totalAmount - (totalAmount * 0.1);
        cout << "\n--------------------------------------------------------------------------\n";
        cout << setprecision(2);
        cout << "\n\t\t\tTotal Amount with Suki Card = " << totalMemberDiscount;
        display("\n\n\n\n\t\"Thank you for availing our Suri Card.\"\n", "LIGHTGREEN");

    }
    else
    {
        cout << "Do you want to avail Suki Card? (y/n) ";
        cin >> availSukiCard;
        if (availSukiCard == 'y' || availSukiCard == 'Y')
        {
            cout << "Please fill up the needed information.\n";
            cout << "Enter your name: ";
            cin >> custName;
            cout << "Enter your contact number: ";
            cin >> custContactNum;
            cin.ignore();

            cout << "Enter your address: ";
            cin >> custAddress;

            totalMemberDiscount = totalAmount - (totalAmount * 0.1);
            cout << "\n----------------------------------------------------------------------\n";
            cout << fixed << setprecision(2);
            cout << "\n\t\t\tTotal Amount with Suki Card = " << totalMemberDiscount;
            display("\n\n\n\n\t\"Thank you for availing our Suri Card.\"\n", "LIGHTGREEN");
            getchar();
        }
        else
        {
            getchar();
        }

    }

}

void change(char availSukiCard, char memberSukiCard, float totalAmount, float totalAmountWithSukiCard)
{
    float payment, totalChange;
    if (memberSukiCard == 'y' || memberSukiCard == 'Y' || availSukiCard == 'y' || availSukiCard == 'Y')
    {
        cout << "Enter your payment: ";
        cin >> payment;
        totalChange = payment - totalAmountWithSukiCard;
        cout << fixed << setprecision(2) << "Your change is " << totalChange;
        cout << endl;
    }
    else
    {
        cout << "Enter your payment: ";
        cin >> payment;
        totalChange = payment - totalAmount;
        cout << fixed << setprecision(2) << "Your change is " << totalChange;
        cout << endl;

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
	myHeader();

	for(;;)
	{

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

