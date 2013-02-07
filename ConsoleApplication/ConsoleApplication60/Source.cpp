#include <iostream> 
using namespace std; 

/*

�H�U���C�X�@�Ǳ`�Ϊ��榡�ƺX�СG 
ios::boolalpha						�N�u�P���Htrue�Pfalse���
ios::dec							10�i�����
ios::fixed							���`�覡��ܡ]�D��ǰO���^
ios::hex							16�i�����
ios::left							�a��
ios::oct							8�i�����
ios::scientific						��ǰO��
ios::showbase						��ܰ�
ios::showpoint						��ܤp���I
ios::showpos						�������+
ios::skipws							�����ťզr��
ios::uppercase						�r���j�g

*/
int main() { 
    ios::fmtflags f; 

    cout.unsetf(ios::dec); 
    cout.setf(ios::oct | ios::showbase); 

    f = cout.flags(); 

    if(f & ios::left) {
        cout << "left flag on\n"; 
    }
    else {
        cout << "left flag off\n"; 
    }

    if(f & ios::dec) {
        cout << "dec flag on\n";
    }
    else {
        cout << "dec flag off\n"; 
    }

    if(f & ios::showbase) {
        cout << "showbase flag on\n"; 
    }
    else {
        cout << "showbase flag off\n"; 
    }

    if(f & ios::oct) {
        cout << "oct flag on\n"; 
    }
    else {
        cout << "left flag off\n"; 
    }
	system("pause");
    return 0; 
}