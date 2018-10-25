#include <iostream>
using namespace std;

/*void enter_information(float amount,int year, float rate )
{
	cout<<"\n Enter initial amount: ";
	cin>>amount;
	cout<<"\n Enter number of years: ";
	cin>>year;
	cout<<"\n Enter interest rate(percent per year): ";
	cin>>rate;
	
}
int caculation(float amount, int year, float rate)
{
	float result = 0;
	
	for(int i = 1; i<=year; i++)
		{
			result = amount + (amount*rate);
			amount = result;
			
		}
	return result;
}*/

int main()
 {
 	float amount, rate;
 	int year;
 	cout<<"\n Enter initial amount: ";
	cin>>amount;
	cout<<"\n Enter number of years: ";
	cin>>year;
	cout<<"\n Enter interest rate(percent per year): ";
	cin>>rate;
 	//enter_information(amount, year, rate);
 	float result = 0;
	
	for(int i = 1; i<=year; i++)
		{
			result = amount + (amount*rate);
			amount = result;	
		}
	cout<<result;
		
 	//cout<<"\n At the end of "<<year<<" years, "<<"you will have "<<caculation(amount, year, rate)<<" dollar. ";
 	return 0;
 }
