#include <iostream>
using namespace std;

class num
{
public:
	num(){n=1;cout<<"�c�y��ư���\n";}
	num(int i){n=i;cout<<"�a�Ѽƪ��c�y��ư���\n";}
	num(const num&s){n=s.n;cout<<"�ƻs�c�y��ư���\n";}
	~num(){cout<<"�R�c��ư���\n";}
	int get()const{return n;}
	void set(int x){n=x;}
	void add(){++n;}
	const num &operator++()
	{
		++n;				
		return *this;
	}
	const num operator++(int o)
	{
		num temp(*this);
		++n;
		return temp;
	}
private:
	int n;
};
int main()
{
	num i;
	cout<<"i:"<<i.get()<<endl;
	i.add();
	cout<<"i:"<<i.get()<<endl;
	num n=++i;
	cout<<"i:"<<i.get()<<endl;
	cout<<"n:"<<n.get()<<endl;
	//num n=i++;
	n=i++;
	cout<<"i:"<<i.get()<<endl;
	cout<<"n:"<<n.get()<<endl;
		
	system("pause");
	return 0;
}