#include <iostream> 
#include <fstream> 
#include "Student.h" 
using namespace std; 

int main(int argc, char* argv[]) { 
    Student student; 
    int count = 0, number; 

        cout << "���O: read <filename>" << endl; 


    ifstream fin("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt", ios::in | ios::binary); 
    if(!fin) { 
        cerr << "�L�kŪ���ɮ�" << endl; 
        return 1; 
    } 

    while(true) { 
        fin.read(reinterpret_cast<char *> (&student), 
            sizeof(Student)); 
        if(!fin.eof()) 
            count++; 
        else 
            break; 
    } 
    fin.clear(); 

    cout << "��J�Ǹ�(1-" << count << ")"  << endl
         << "��J0���}"; 

    while(true) { 
        cout << "\n�Ǹ�? "; 
        cin >> number; 
        if(number == 0) 
            break; 
        else if(number > count) { 
            cout << "��J�Ǹ�(1-" << count << ")" << endl; 
            continue; 
        } 
                                                                                
        cout << "\n�Ǹ�\t�m�W\t\t����" << endl; 
                                                                                
        fin.seekg((number - 1) * sizeof(Student)); 
        fin.read(reinterpret_cast<char*> (&student), 
            sizeof(Student)); 
        cout << student.studyNumber << "\t" 
             << student.name << "\t\t" 
             << student.score << endl; 
    } 

    fin.close(); 

    return 0; 
}

/*

�b�P�_��Ƶ��Ʈ��٦���²�檺��k�A�N�O�}���ɮ׫���ϥ�ios::end�N���в����ɮק��A
�M��ϥ�tellg()�o��ثe���ɮ׫��Ц�m�A�A���H��Ƶ��c���j�p���i�o����Ƶ��ơA�Ҧp�G 
file.seekg(0, ios::end); 
count = file.tellg() / sizeof(��Ƶ��c); 
*/