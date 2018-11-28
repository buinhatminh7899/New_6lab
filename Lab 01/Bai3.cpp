#include <iostream>
using namespace std;
class serial
{
	private:
		static int count;
		int num;
	public:
		serial()
		{
	   		static int count=0;
        	num=++count;
		}
		void show()
		{
			cout<<"\t"<<num<<"\n";
		}
};

int main()
{ 
	serial a[4];
    for(int i=0;i<4;i++)
	{
		a[i].show();
	}
 	return 0;   
}

