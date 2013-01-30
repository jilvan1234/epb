#include <iostream>
using namespace std;
class Human
{
public:
	Human(){cout<<"�c�yHuman\n";}
	virtual void smart()=0;
	virtual void beautiful()=0;
	virtual ~Human(){cout<<"�R�cHuman\n";}
};
class father:virtual public Human
{
public:
	father(){cout<<"�c�yfather\n";}
	virtual void smart()
	{
		cout<<"father is int\n";
	}	
	virtual void beautiful(){cout<<"father no is handsome\n";}
	virtual ~father(){cout<<"�R�c father"<<endl;}
};
class mother:virtual public Human
{
public:
	mother(){cout<<"�c�ymother\n";}
	virtual void beautiful(){cout<<"mother is beautiful\n";}
	virtual void smart(){cout<<"mother no is int\n";}
	virtual ~mother(){cout<<"�R�c mother"<<endl;}
};
class son:public father,public mother
{
public:
	son(){cout<<"�c�yson\n";}
	virtual void beautiful(){cout<<"son is handsome\n";};
	virtual void smart(){cout<<"son is int\n";}
	virtual ~son(){cout<<"�R�c son"<<endl;}
};
int main()
{
	Human*p;	
	int choice=0;
	while(choice < 99)
	{
		bool quit=false;
		cout<<"(0)quit(1)father(2)son:(3)mother:";
		cin>>choice;
		switch(choice){
		case 0:quit=true;
			break;
		case 1:p=new father;
			p->beautiful();
			p->smart();
			delete p;
			break;
		case 2:p=new son;
			p->beautiful();
			p->smart();
			delete p;
			break;
		case 3:p=new mother;
			p->beautiful();
			p->smart();
			delete p;
			break;
		default:
			cout<<"please input 0 to 2 number ";
			break;
		}
		if(quit)
		{
			break;
		}

	}
	cout<<"end"<<endl;
	system("pause");
	return 0;
}