#include <iostream>
using namespace std;


int main()
{/*//���ӼƲլۥ[
	char a[20]="This is a ";
	char b[]="Sparta";
	cout<<strcat(a,b)<<endl;
	cout<<a;*/

	/*//��b�ƻs��a
	char a[20]="This is a ";
	char b[]="Sparta";
	cout<<strcpy(a,b)<<endl;
	cout<<a;*/

	/*//�P�_��ӼƲլO�_�ۦP
	char a[]="This is a ";
	char b[]="Sparta";
	char c[]="Sparta";
	cout<<strcmp(a,b)<<endl;//> = 1 ,< = -1 , == 0
	cout<<a;*/

	/*//��p�g�ഫ���j�g
	char a[]="this is a Sparta";
	strupr(a);
	cout<<a<<endl;*/
	/*
	//��j�g�ഫ���p�g
	char a[]="THIS IS A SPARTA";
	strlwr(a);
	cout<<a<<endl;
	*/
	/*
	//�p��r�Ŧ����,�Ӫ��פ��]�A������'\0'
	char a[]="THIS IS A SPARTA";	
	cout<<strlen(a)<<endl;*/
	system("pause");
	return 0;
};
