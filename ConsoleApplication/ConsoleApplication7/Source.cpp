#include <iostream>
using namespace std;
class father
{
public:
	father(int x){a=x;cout<<"�c�y������H ����a���Ȭ�:"<<a<<endl;}
	~father(){cout<<"�R�c������H  ����a���Ȭ�:"<<a<<endl;}
private:
	int a;
};
class son:public father
{
public:
	son(int z,int x,int y):father(x),Mick(y){b=z;cout<<"�c�y�l����H ����b���Ȭ�:"<<b<<endl;}
	~son(){cout<<"�R�c�l����H \n";}
private:
	int b;
	father Mick;
};
int main()
{
	son Jack(1,2,3);

	system("pause");
	return 0;
}