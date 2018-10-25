#include <iostream>
using namespace std;

struct phone
{
	int areacode;
	int exchange;
	int number; 
};
typedef struct phone Phone;

void enterphone(Phone &x)
{
	cout<<"\n Enter your area code, exchange, and number: ";
	cin>>x.areacode>>x.exchange>>x.number;
	cout<<endl;
}

void printphone(Phone x)
{
	cout<<"\n Your numberphone is: "<<"("<<x.areacode<<")"<<" "<<x.exchange<<"-"<<x.number<<endl; 
}

int main()
{
	Phone x1,x2;
	enterphone(x1);
	x2.areacode = 212;
	x2.exchange = 768;
	x2.number = 8900;
	cout<<"\n My numberphone is: "<<"("<<x2.areacode<<")"<<" "<<x2.exchange<<"-"<<x2.number<<endl;
	printphone(x1);
	return 0;
}
