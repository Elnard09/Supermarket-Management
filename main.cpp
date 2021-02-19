#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<string>
#include<iostream>
#include <Windows.h>
#include "LoginAdmin.h"
#include "Product.h"
#include <sstream>

using namespace std;

string g_system_name = "SUPERMARKET MANAGEMENT SYSTEM";  //Global variable

//Initialization of functions
long stoi(const char *s);
void admin_menu();
void display(string my_str, string color);
void membership(float totalAmount);
void change(char availSukiCard, char memberSukiCard, float totalAmount, float totalAmountWithSukiCard);

//Create file stream naming fp.
fstream fp;

//Create Product object
Product objProduct;

//Save data input to database.dat file
void save_product()
{
    char addanotherornot;

    //Open the database.dat file in Output mode and Append mode.
	fp.open("database.txt",ios::out|ios::app);
	objProduct.create_product();
	fp.write((char*)&objProduct,sizeof(Product));   //Write to the file
	fp.close();  //Close file
	cout << endl <<"Do you want to add another product? y/n: ";
    cin >> addanotherornot;
            while (addanotherornot == 'y' || addanotherornot == 'Y')
            {
                fp.open("database.txt",ios::out|ios::app);
                objProduct.create_product();
                fp.write((char*)&objProduct,sizeof(Product));
                fp.close();
                cout << endl <<"Do you want to add another product? y/n: ";
                cin >> addanotherornot;
            }
	cout << endl;
	cout << endl;
	display("The Product/s Has Been Sucessfully Created...\n", "LIGHTGREEN");
	getchar();
}


void show_all_product()
{
	system("cls");
	cout<<endl<<"===========================================";
	display("\n\t\tRECORDS.", "YELLOW");
	cout<<endl<<"===========================================\n";
	fp.open("database.txt",ios::in);
	while(fp.read((char*)&objProduct,sizeof(Product)))
	{
		objProduct.show_product();
		cout<<endl<<"==========================================\n"<<endl;
		getch();
	}
	display("\n\n.............All product have been displayed..............", "LIGHTGREEN");
	getch();
	admin_menu();
	fp.close();
}

void edit_product()
{
	int num;
	bool found=false;
	system("cls");
	display("\n\t\tMODIFY PRODUCT\n", "YELLOW");
	cout<<"=============================================\n"<<endl;
	cout<<"Please Enter The Product #: ";
	cin>>num;


	fp.open("database.txt",ios::in|ios::out);
	while(fp.read((char*)&objProduct,sizeof(Product)) && found==false)
	{
		if(objProduct.getProduct()==num)
		{
			objProduct.show_product();
			cout<<"\n---------------------------------------------\n"<<endl;
			cout<<"Please Enter The New Details of Product: "<<endl;
			objProduct.create_product();
			int pos=-1*sizeof(objProduct);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&objProduct,sizeof(Product));
			display("\n\n.......Record Successfully Updated........\n", "LIGHTGREEN");
			found=true;
		}
	}
	fp.close();

	if(found==false)
		display("\n\n.........Record Not Found.........", "LIGHTRED");

	getch();
	admin_menu();
}


//delete the product the product funstion
void delete_product()
{
	int num;
	system("cls"); //clear the screen
	display("\n\t\tDELETE PRODUCT\n", "YELLOW");
	cout<<"=============================================\n"<<endl;
	cout<<"Please Enter The product #: ";
	cin>>num;
	fp.open("database.txt",ios::in|ios::out);                   //Open the database.dat file
	fstream fp2;                                                //Create fle stream naming fp2
	fp2.open("Temp.txt",ios::out);                              //Open the temp.dat file and set to Output mode
	fp.seekg(0,ios::beg);                                       //Read database.dat dile data from the beggining to end of the file.
	while(fp.read((char*)&objProduct,sizeof(Product)))          //while there's a character in database file execute this loop.
	{
		if(objProduct.getProduct()!=num)                        //If the Product number is not equal to Product you wanted to delete...
		{
			fp2.write((char*)&objProduct,sizeof(Product));      //write the product details to the Temp.dat file.
		}
	}
	fp2.close();                                                //Close Temp file
	fp.close();                                                 //Close database file
	remove("database.txt");                                     //Delete the database.dat file
	rename("Temp.txt","database.txt");                          //Rename Temp.dat file to database.dat
	cout<<endl<<endl;
	display(".........Record Deleted........\n\n", "LIGHTGREEN");
	getch();
	admin_menu();

}


void product_menu()
{

	system("cls");                                  //Clear the screen
	fp.open("database.txt",ios::in);                //Open the database file

	display("\n\n\t\t\t\t\PRODUCT MENU\n\n", "YELLOW");
	cout<<"==================================================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\t\tDiscount\tAvailable Stocks\n";
	cout<<"==================================================================================\n";
	while(fp.read((char*)&objProduct,sizeof(Product)))          //While there's a character in database file execute this loop
	{
		cout << objProduct.getProduct();
		cout << "\t\t" << objProduct.getName();
		cout << "\t\t" << setprecision(2) << fixed <<objProduct.getPrice();
		cout << "\t\t" << setprecision(0) << objProduct.getDiscount()<<"%";
		cout << "\t\t"<< setprecision(0) << fixed <<objProduct.getQuantity()<< endl;
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
		cout<<"\nEnter The Product #: ";
		cin>>order_arr[c];
		fp.open("database.txt",ios::in);
		fp.seekg(0L, ios::beg);
		while(fp.read((char*)&objProduct,sizeof(Product)))
        {
		    if(objProduct.getProduct() != order_arr[c])
            {
                display("\nThat product is not on the list.\n\n", "LIGHTRED");
                cout << "Please enter valid product number: ";
                cin >> order_arr[c];
            }
        }
        fp.close();

		cout<<"\nQuantity: ";
		cin>>quan[c];
		fp.open("database.txt",ios::in | ios::binary);
		fp.seekg(0L, ios::beg);
		while(fp.read(reinterpret_cast<char *>(&objProduct), sizeof(Product)))
        {
            if ( objProduct.getQuantity() < quan[c] )
            {
                cout << "\nOut of stock.\nEnter another Quantity not exceeding ";
                cout << objProduct.getQuantity()<< " : ";
                cin >> quan[c];
            }
        }
        fp.close();

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
		fp.open("database.txt",ios::in);
		fp.read((char*)&objProduct,sizeof(Product));
		while(!fp.eof())
		{
			if(objProduct.getProduct() == order_arr[x])
			{
				amt = objProduct.getPrice()* quan[x];
				damt = amt-(amt*objProduct.getDiscount()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<objProduct.getName()<<"\t"<<quan[x]<<"\t\t"<< fixed <<setprecision(2) <<objProduct.getPrice()<<"\t"<<amt<<"\t\t"<<damt;
				total += damt;
			}
			fp.read((char*)&objProduct,sizeof(Product));
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
            getline(cin, custName);
            cin.ignore();

            cout << "\nEnter your contact number: ";
            getline(cin, custContactNum);
            cin.ignore();
            cin.clear();
            fflush(stdin);

            cout << "\nEnter your address: ";
            getline(cin, custAddress);
            cin.clear();
            fflush(stdin);

            totalMemberDiscount = totalAmount - (totalAmount * 0.1);
            cout << "\n----------------------------------------------------------------------\n";
            cout << setprecision(2);
            cout << "\n\t\t\t\tTotal Amount with Suki Card Discount= " << totalMemberDiscount;
            display("\n\n\n........Thank you for availing our Suri Card............\n", "LIGHTGREEN");
            getch();
            getch();
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
        cin.ignore();
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
        cin.ignore();
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
    display("\n\t\t\tADMIN MENU", "YELLOW");
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

long stoi(const char *s)
{
    long i;
    i = 0;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    return i;
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

