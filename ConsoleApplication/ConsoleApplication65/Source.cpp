#include <iostream> 
#include <fstream> 
using namespace std; 

int main(int argc, char* argv[]) { 
    
	cout << "���O: copy <input> <output>" << endl; 

    ifstream fin("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\a.txt"); 
    ofstream fout("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\b.txt"); 

    if(!fin) { 
        cout << "�L�kŪ�J�ӷ��ɮ�" << endl; 
        return 1; 
    } 

    if(!fout) { 
        cout << "�L�k��X�ت��ɮ�" << endl;
        fin.close();
        return 1; 
    } 

    char ch; 

    fin.unsetf(ios::skipws); // �������ť� 
    while(!fin.eof()) { 
        fin >> ch; 
        if(ch >= 97 && ch <= 122) 
            ch -= 32; 
        if(!fin.eof()) 
            fout << ch; 
    } 

    fin.close(); 
    fout.close(); 
	system("pause");
    return 0; 
}