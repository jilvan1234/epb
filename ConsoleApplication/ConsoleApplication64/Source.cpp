#include <iostream> 
#include <fstream> 
using namespace std; 

int main(int argc, char* argv[]) { 
    char str[80]; 
  
        cout << "���O: write <filename>" <<endl ; 

    ofstream fout("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\temp.txt"); 
    if(!fout) { 
        cout << "�L�k�g�J�ɮ�" <<endl ;
        return 1; 
    } 

    do { 
        cout << "$ "; 
        cin >> str; 
        fout << str << endl; 
    } while(*str != 'q'); 

    fout.close(); 

    return 0; 
}