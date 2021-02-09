#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>

using namespace std;

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
		cout<<endl<<"===========================================\n"<<endl;
		getchar();
	}
	fp.close();
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

int main()
{
    cout<<"\n\t==========================================";
    cout<<"\n\t1. CUSTOMER";
    cout<<"\n\t2. ADMINISTRATOR";
    cout<<"\n\t3. EXIT";
    cout<<"\n\t==========================================";

    cout<<"\n\tOption: ";
    return 0;
}

