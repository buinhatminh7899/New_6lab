
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
  void showTime() 
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
  }
};

int main(){
 
 const time a(2,23,45), b(4,25,15);
 time c;
 c.addTime(a,b);
 c.showTime();
}

