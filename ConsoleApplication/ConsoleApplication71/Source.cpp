#include <iostream> 
#include <fstream> 
#include "Student.h" 
using namespace std; 

int main(int argc, char* argv[]) { 
    Student student; 
    int count = 0; 

        cerr << "���O: write <filename>"; 


    fstream fio("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt", ios::in | ios::out | ios::binary); 
    if(!fio) { 
        cerr << "�L�kŪ���ɮ�" << endl; 
        return 1; 
    } 

    while(true) { 
        fio.read(reinterpret_cast<char *> (&student), 
            sizeof(Student)); 
        if(!fio.eof()) 
            count++; 
        else 
            break; 
    } 

    fio.clear(); 

    cout << "��J�Ǹ�(1-" << count << ")"  << endl
         << "��J0���}"; 

    while(true) { 
        cout << "\n�Ǹ�? "; 
        cin >> student.studyNumber; 
        if(student.studyNumber == 0) 
            break; 
        
        cout << "��J�m�W, ����" << endl
             << "? "; 
        cin >> student.name >> student.score; 

        fio.seekp((student.studyNumber - 1) * sizeof(Student)); 
        fio.write(reinterpret_cast<const char*> (&student), 
            sizeof(Student)); 
    } 

    fio.close(); 
	
	std::system("pause");
    return 0; 
}

   

	