#include <iostream>
using namespace std;

class employee
{
	private:
		int id;
		float salary;
		int years;
	public:
		void Nhap();
		void Xuat();
		float caculation();
};

void employee::Nhap()
{
	cout<<"\nNhap id cua nhan vien: ";
	cin>>id;
	cout<<"\nNhap muc tien luong: ";
	cin>>salary;
	cout<<"\nNhap so nam lam viec: ";
	cin>>years;
}

void employee::Xuat()
{
	cout<<"\nId: "<<id;
	cout<<"\nLuong: "<<salary;
	cout<<"\nNam: "<<years;
}

float employee::caculation()
{
	for(int i=0; i<years; i++)
	{
		salary=salary+(salary*0.055);
	}
	return salary;
}

int main()
{
	int n;
	cout<<"\nNhap so luong nhan vien: ";
	cin>>n;
	employee a[n];
	for(int i=0; i<n; i++)
	{
		cout<<"\nNhap thong tin nhan vien thu "<<i+1;
		a[i].Nhap();
	}
	for(int i=0; i<n; i++)
	{
		cout<<"\nThong tin nhan vien thu "<<i+1<<" la: ";
		a[i].Xuat();
		cout<<endl;
		cout<<"\nTong tien nhan duoc la: "<<a[i].caculation();
	}
	return 0;
}
