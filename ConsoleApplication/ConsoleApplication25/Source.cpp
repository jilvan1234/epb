#include <iostream>
using namespace std;

class area
{
public:
	area(int l,int w){length=l;width=w;cout<<"調用構造函數設置長和寬的值,"<<"長: "<<length<<"寬: "<<width<<endl;}
	~area(){cout<<"調用析構函數釋放內存,"<<"長: "<<length<<"寬: "<<width<<endl;}
	int get(){return length*width;}
	void set(int l,int w){length=l;width=w;}

private:
	int length;
	int width;
};
int main()
{
	area one[4]={area(10,10),area(13,34),area(20,30),area(40,40)};	
	cout<<one[0].get()<<endl;
	one[0].set(30,40);
	for(int i=0;i<4;i++)
	cout<<one[i].get()<<endl;


	system("pause");
	return 0;
};
