#include <iostream>
#include <string>
using namespace std;
int main()
{
	string str1 = "gh";
	string str2 = "abcdef";
	str1.replace(0,1,str2,4,2);
	cout<<str1<<endl;
	cout<<str2<<endl;
	system("pause");
	return 0;
}
