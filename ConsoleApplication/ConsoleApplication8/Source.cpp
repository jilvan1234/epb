#include <iostream>
#include <string>
using namespace std;

class Father
{
public:
	Father(){cout<<"�c�y������H\n";}
	Father(string a,int i){name=a;tall=i;cout<<"�c�y�a��ӰѼƪ�������H\n";}
	~Father(){cout<<"�R�c������H\n";}
	void print(){cout<<name<<"������"<<tall<<"cm\n";}
protected:
	string name;
	int tall;
};
class Son:public Father
{
public:
	Son(string a,int i,int j):Father(a,i){weight=j;cout<<"�c�y�l����H\n";}
	~Son(){cout<<"�R�c�l����H\n";}
	void print1(){print();cout<<"�魫��:"<<weight;}
protected:
	int weight;
};
int main()
{
	Son Mike("Mike",180,80);
	Mike.print1();
	//Mike.print();
	cout<<"\n�{�ǵ���\n";
	system("pause");
	return 0;
}