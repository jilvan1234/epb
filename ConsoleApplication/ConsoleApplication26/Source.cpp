#include <iostream>
using namespace std;

class area
{
public:
	area(int l,int w){length=l;width=w;cout<<"�եκc�y��Ƴ]�m���M�e����,"<<"��: "<<length<<"�e: "<<width<<endl;}
	~area(){cout<<"�եΪR�c������񤺦s,"<<"��: "<<length<<"�e: "<<width<<endl;}
	int get(){return length*width;}
	void set(int l,int w){length=l;width=w;}

private:
	int length;
	int width;
};
int main()
{
	for(int i=0;i<10000;i++)
	{
		area *one=new area(4,5*i);
		cout<<"area["<<i<<"]:";
		cout<<one->get()<<endl;
		delete one;
	}

	system("pause");
	return 0;
};
