#include <iostream>
#include <stdlib.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
using namespace std;

int n, k, X[MAX], dem =0;

void Init(void)
{
	cout<<"\n Nhap n= ";
	cin>>n;
	cout<<"\n Nhap k= ";
	cin>>k;
	X[0] = 0;
}

void result(void)
{
	cout<<"\n Ket qua buoc "<<++dem<<" :";
	for(int i = 1; i <= k; i++)
		cout<<X[i]<<" ";
}

void Try(int i)
{
	for (int j = X[i-1]+1; j <= n-k+i; j++)
	{
		X[i] = j;
		if(i==k)result();
		else Try(i+1);
	}
}

int main()
{
	Init();
	Try(1);
	return 0;
}
