
#include <iostream>
#include <conio.h>

using namespace std;

class time{
 private:
  int hours,minutes,seconds;
 public:
  time(){
   hours = minutes = seconds = 0;
  }
  time(int h, int m, int s){
   hours = h;
   minutes = m;
   seconds = s;
  }
  void showTime() const 
  {
   cout << hours << ':' << minutes << ':' << seconds;
  }
  void addTime(time x, time y){
   seconds = x.seconds + y.seconds;
   if(seconds>59){
    seconds-=60;
    minutes++;
   }
   minutes += x.minutes + y.minutes;
   if(minutes>59){
    minutes-=60;
    hours++;
   }
   hours+=x.hours+y.hours;
   if(hours>23)
   {
   	hours%=24;
   }
  }
  void Nhap();
};
void time::Nhap()
{
	do
	{
		cout<<"\nNhap gio: ";
		cin>>hours;
		if(hours>23||hours<0)cout<<"\nNhap sai, Xin moi kiem tra lai!";
	}while(hours>23||hours<0);
	do
	{
		cout<<"\nNhap phut: ";
		cin>>minutes;
		if(minutes>59||minutes<0)cout<<"\nNhap sai, Xin moi kiem tra lai!";
	}while(minutes>59||minutes<0);
	do
	{
		cout<<"\nNhap giay: ";
		cin>>seconds;
		if(seconds>59||seconds<0)cout<<"\nNhap sai, Xin moi kiem tra lai!";
	}while(seconds>59||seconds<0);
	
}

int main(){
 
 //const time a(2,23,45), b(4,25,15);
 time a,b;
 a.Nhap();
 b.Nhap();
 time c;
 c.addTime(a,b);
 c.showTime();
}

