#include <iostream>
#include <stdlib.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
using namespace std;

int X[MAX], xuoi[MAX], nguoc[MAX], chuaxet[MAX];
int n, dem = 0;

void Init(void)
{
	cout<<"\n nhap n = ";
	cin>>n;
	for(int i=1; i<=n; i++)
		chuaxet[i]=TRUE;
	for(int i=1; i<=2*n-1; i++)
	{
		xuoi[i]=TRUE;
		nguoc[i]=TRUE;
	}
}

void result(void)
{
	cout<<"\n Phuong an "<<++dem<<" :";
	for(int i=1; i<=n; i++)
		cout<<X[i]<<" ";
}

void Try(int i)
{
	for(int j=1; j<=n; j++)
	{
		if(chuaxet[j]&&xuoi[i-j+n]&&nguoc[i+j-1])
		{
			X[i] = j;
			chuaxet[j]=FALSE;
			if(i==n)result();
			else Try(i+1);
			chuaxet[j]=TRUE;
			xuoi[i-j+n]=TRUE;
			nguoc[i+j-1]=TRUE;
		}
	}
}

int main()
{
	Init();
	Try(1);
	return 0;
} 
