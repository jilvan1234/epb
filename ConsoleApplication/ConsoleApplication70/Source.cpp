/*
�@�ӵ��c���j�p�O�T�w���A��n�g�J�@�ӵ��c�ɡA�i�H�ϥγo�˪��y�k�G 
fout.write(reinterpret_cast<const char*> (&student), sizeof(Student)); 
�䤤student�OStudent�ۭqstruct�ҫŧi���ܼƦW�١A�ѩ�write����const char*���A���ܼơA
�ҥH�ϥ�reinterpret_cast<const char*> �N���ഫ��const char*���СC 
*/

#include <iostream> 
#include <fstream> 
#include "Student.h" 
using namespace std; 

int main(int argc, char* argv[]) { 
  
       
	cout << "���O: create <filename>" << endl; 
	 
    ofstream fout("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt", ios::binary); 

    if(!fout) { 
        cerr << "�ɮ׿�X����" << endl; 
        return 1; 
    } 

    int count; 
    cout << "�n�إߴX����ơH "; 
    cin >> count; 

    Student student = {0, "", 0.0}; 

    for(int i = 0; i < count; i++) { 
        fout.write(reinterpret_cast<const char*> (&student), 
            sizeof(Student)); 
    } 

    fout.close(); 
	std::system("pause");
    return 0; 
}

   

	