#include <iostream>
using namespace std;
bool add(int a[],int n);
int main()
{
	int a[]={22,44,66,88,1,32,64};
	bool check = add(a,4);
	if(check==true)
	{
		cout<<"�Ʋզ����Ӷ��ǱƦC"<<endl;
	}
	else 
	{
		cout<<"�ƲըS�����Ӷ��ǱƦC"<<endl;
	}

	system("pause");
	return 0;
};
bool add(int a[],int n)
{
	for(int i=1;i<n;i++)
	{
		if(a[i]<a[i-1])
		{
			return false;
		}
	}		
	return true;
}