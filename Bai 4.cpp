#include <iostream>
using namespace std;

struct phanso
{
	int tuso;
	int mauso;
};
typedef struct phanso PhanSo;


PhanSo addition(PhanSo a, PhanSo b)
{
	PhanSo result;
	result.tuso = (a.tuso*b.mauso + b.tuso*a.mauso);
	result.mauso = a.mauso*b.mauso;
	return result;
}

PhanSo subtraction(PhanSo a, PhanSo b)
{
	PhanSo result;
	result.tuso = (a.tuso*b.mauso - b.tuso*a.mauso);
	result.mauso = a.mauso*b.mauso;
	return result;
}

PhanSo multiplication(PhanSo a, PhanSo b)
{
	PhanSo result;
	result.tuso = a.tuso*b.tuso;
	result.mauso = a.mauso*b.mauso;
	return result;
}

PhanSo division(PhanSo a, PhanSo b)
{
	PhanSo result;
	result.tuso = a.tuso*b.mauso;
	result.mauso = a.mauso*b.tuso;
	return result;
}

void caculation(PhanSo a, PhanSo b);

int main()
{
	PhanSo a, b;
	char choice;
	do
	{
		caculation(a,b);
		cout<<"\n Do another (y/n)?: ";
		cin>> choice;
	}while(choice == 'y');
	return 0;
}
void caculation(PhanSo a, PhanSo b)
{
	PhanSo ketqua;
	char x;
	do
	{
		cout<<"\n Enter first number ";
		cin>>a.tuso>>a.mauso;
		cout<<"\nMau so phai khac 0";
	}while((a.mauso=0));
	do
	{
		cout<<"\n second number ";
		cin>>b.tuso>>b.mauso;
		cout<<"\nMau so phai khac 0";
	}while((b.mauso=0));
	cout<<"\n operator : ";
	cin>>x;
	switch(x)
	{
		case '+':
		{
			ketqua =  addition(a, b);
			cout<<"\n Answer is: "<< ketqua.tuso <<"/"<< ketqua.mauso;
			break;
		}
		case '-':
		{
			ketqua = subtraction(a, b);
			cout<<"\n Answer is: "<< ketqua.tuso <<"/"<< ketqua.mauso;
			break;
		}
		case '*':
		{
			ketqua = multiplication(a, b);
			cout<<"\n Answer is: "<< ketqua.tuso <<"/"<< ketqua.mauso;
			break;
		}
		default:
		{
			ketqua = division(a, b);
			cout<<"\n Answer is: "<< ketqua.tuso <<"/"<< ketqua.mauso;
			break;
		}
	}
}
