#include <iostream> 
#include <fstream> 
using namespace std; 

int main() { 
    char ch;        
	cout << "���O: copy <input> <output>" << endl; 

    ifstream fin("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\a.txt", ios::in | ios::binary); 
    ofstream fout("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\b.txt", ios::out | ios::binary); 

    if(!fin) { 
        cout << "�ɮ�Ū�J����" << endl; 
        return 1; 
    } 

    if(!fout) { 
        cout << "�ɮ׿�X����" << endl; 
        return 1; 
    } 

    while(!fin.eof()) { 
        fin.get(ch); 
        if(!fin.eof()) 
            fout.put(ch); 
    } 

    fin.close(); 
    fout.close(); 

    return 0;
}