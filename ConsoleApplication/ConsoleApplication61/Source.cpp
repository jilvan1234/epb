#include <iostream> 
#include <fstream> 
using namespace std; 

/*
filename�O�ɮצW�١A��mode�M�w�ɮת��}�ҼҦ��A���O��ios���O�ҩw�q���`�ƨӨM�w�A�U���C�Xopenmode���ȻP�γ~�G 
ios::in			�ɮ�open����J�Ҧ�(istream default)
ios::out		�ɮ�open���g�J(ostream default)
ios::ate		�q�ɮק��ݿ�J��X
ios::app		�b�ɮק��ݥHappend�Ҧ��g�J
ios::trunc		�p�G�ɮצs�b�A�h�M���ɮפ��e
ios::binary		�H�G�i��Ҧ�open�ɮ�
*/
int main() 
{ 

	char ch; 

    ifstream fin;
    fin.open("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\a.txt");                       
                            
    if(!fin) { 
        cout << "�ɮ�I/O����" << endl; 
        return 1; 
    } 
                                            
    while(!fin.eof()) { 
        fin.get(ch); 
        cout << ch; 
    } 
          
	cout<<endl;
    fin.close(); 
	system("pause");
    return 0; 
}