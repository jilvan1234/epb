#include <iostream> 
#include <fstream> 
#include <iomanip> 
using namespace std; 

int main(int argc, char* argv[]) { 
    char ch; 
    int count = 0; 
	cout<<"�U���o�ӵ{���i�HŪ�J���N�ɮסA�C��Ū�J�@�Ӧ줸�աA\n�ñNŪ�J����ƥH16�i�����ܡA\
		�YŪ�J����ƫe�ɦ줸��1�A\n���F��X������A�h�ϥΨ�ɼƥ[�H��ܡG \n"<<endl;
     
	cout << "���O: read <filename>" << endl; 

    ifstream fin("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\temp.txt", ios::in | ios::binary); 
    if(!fin) { 
        cout << "�L�kŪ���ɮ�" << endl; 
        return 1; 
    } 

    while(!fin.eof()) { 
        fin.get(ch); 
        if(ch < 0) 
            ch = ~ch; // �t�ƨ��ɼ� 
        cout << setw(2) << hex << (int)ch << " "; 
        count++; 
        if(count > 16) {  // ���� 
            cout << endl; 
            count = 0; 
        } 
    } 
    cout << endl; 

    fin.close(); 
	
	system("pause");
    return 0; 
}
