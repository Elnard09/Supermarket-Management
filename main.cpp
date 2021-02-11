#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>

using namespace std;

class LoginAdmin{
     public:
         string passWordAttempt;

         LoginManager()
         {
            accessGranted = 0;
         }

         void login()
         {
                cout << "\nEnter your password:";
                cin >> passWordAttempt;

                while (passWordAttempt!=passWord){

                    cout << "\nIncorrect password!\nPlease enter the correct password:";
                    cin >> passWordAttempt;
            }
         }
    private:
        string passWord = "98645918";
        bool accessGranted;
};

class product
{
	int product_number;
	char product_name[50];
	float product_price,product_quantity,tax,product_discount;

	public:

	void create_product()
	{
		cout<<endl<<"Please Enter The Product Number: ";
		cin>>product_number;
		cout<<endl<<"Please Enter The Name of The Product: ";
		cin.ignore();
		cin.getline(product_name ,50);
		cout<<endl<<"Please Enter The Price of The Product: ";
		cin>>product_price;
		cout<<endl<<"Please Enter The Discount (%): ";
		cin>>product_discount;
	}

	void show_product()
	{
		cout<<endl<<"Product #: "<<product_number;
		cout<<endl<<"Product Name: "<<product_name;
		cout<<endl<<"Product Price: "<<product_price;
		cout<<endl<<"Discount : "<<product_discount;
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

	float getDiscount()
	{
		return product_discount;
	}
};



fstream fp;
product produc;


void save_product()
{
	fp.open("database.dat",ios::out|ios::app);
	produc.create_product();
	fp.write((char*)&produc,sizeof(product));
	fp.close();
	cout<<endl<<endl<<"The Product Has Been Sucessfully Created...";
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
			cout<<endl<<endl<<"\t Record Successfully Updated...";
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
	cout<<endl<<endl<<"\tRecord Deleted...";
	getchar();
}


void product_menu()
{
	system("cls");
	fp.open("database.dat",ios::in);

	cout<<endl<<endl<<"\t\tProduct MENU\n\n";
	cout<<"======================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	cout<<"======================================================\n";
	while(fp.read((char*)&produc,sizeof(product)))
	{
		cout<<produc.getProduct()<<"\t\t"<<produc.getName()<<"\t\t"<<produc.getPrice()<<endl;
	}
	fp.close();
}



void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	product_menu();
	cout<<"\n================================================";
	cout<<"\n PLACE YOUR ORDER";
	cout<<"\n================================================\n";
	do{
		cout<<"\n\nEnter The Product #: ";
		cin>>order_arr[c];
		cout<<"\nQuantity: ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Product ? (y/n)";
		cin>>ch;
		}while(ch=='y' ||ch=='Y');
	cout<<"\n\nThank You...";
	getchar();
	system("cls");
	cout<<"\n\n********************************RECEIPT************************\n";
	cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
	for(int x=0;x<=c;x++)
	{
		fp.open("database.dat",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{
			if(produc.getProduct()==order_arr[x])
			{
				amt=produc.getPrice()*quan[x];
				damt=amt-(amt*produc.getDiscount()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<produc.getName()<<"\t"<<quan[x]<<"\t\t"<<produc.getPrice()<<"\t"<<amt<<"\t\t"<<damt;
				total+=damt;
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
	getchar();
}



void admin_menu()
{
	system("cls");

	int option;
	cout<<"\t=============================================";
	cout<<"\n\tPress 1 to CREATE PRODUCT";
	cout<<"\n\tPress 2 to DISPLAY ALL PRODUCTS";
	cout<<"\n\tPress 3 to QUERY ";
	cout<<"\n\tPress 4 to MODIFY PRODUCT";
	cout<<"\n\tPress 5 to DELETE PRODUCT";
	cout<<"\n\tPress 6 to GO BACK TO MAIN MENU";
	cout<<"\n\t============================================";

	cout<<"\n\n\tOption: ";
	cin>>option;
	switch(option)
	{
		case 1: system("cls");
				save_product();
				break;

		case 2: show_all_product();
				break;

		case 3:
				int num;
				system("cls");
				cout<<"\n\n\tPlease Enter The Product Number: ";
				cin>>num;
				display_record(num);
				break;

		case 4: edit_product();
		break;

		case 5: delete_product();
		        break;

		case 6: system("cls");
				break;

		default:admin_menu();
	}
}


int main(int argc, char *argv[])
{
	system("cls");
	system("color 07");

	int option;

	for(;;)
	{

		cout<<"\n\t===========================================";
		cout<<"\n\t1. CUSTOMER";
		cout<<"\n\t2. ADMINISTRATOR";
		cout<<"\n\t3. EXIT";
		cout<<"\n\t============================================";

		cout<<"\n\tOption: ";
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
                    loginManagerObj.login();
                    admin_menu();
					break;
					}

			case 3:{
					cout<<"\n\t===========================================";
					cout<<"\n\tGood Bye!";
					cout<<"\n\t===========================================\n";
					exit(0);
                    }

			default :cout<<"Invalid Input...\n";
		}

	}
}

