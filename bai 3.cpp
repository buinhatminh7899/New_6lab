#include <iostream>
using namespace std;

float addition(float a, float b)
{
	return a+b;
}

float subtraction(float a, float b)
{
	return a-b;
}

float multiplication(float a, float b)
{
	return a*b;
}

float division(float a, float b)
{
	return a/b;
}

void caculation(float a, float b);

int main()
{
	float a, b;
	char choice;
	do
	{
		caculation(a,b);
		cout<<"\n Do another (y/n)?: ";
		cin>> choice;
	}while(choice == 'y');
	return 0;
}
void caculation(float a, float b)
{
	char x;
	cout<<"\n Enter first number, operator, second number: ";
	cin>>a>>x>>b;
	switch(x)
	{
		case '+':
		{
			cout<<"\n"<<a<<" + "<<b<<" = "<<addition(a, b);
			break;
		}
		case '-':
		{
			cout<<"\n"<<a<<" - "<<b<<" = "<<subtraction(a, b);
			break;
		}
		case '*':
		{
			cout<<"\n"<<a<<" * "<<b<<" = "<<multiplication(a, b);
			break;
		}
		default:
		{
			cout<<"\n"<<a<<" / "<<b<<" = "<<division(a, b);
			break;
		}
	}
	
}


