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
	//�b�{�����ڭ̥��Ѱ��Fios::dec�榡�X�СA�o�Ӱʧ@�ä��O�@�w�ݭn�A���b�Y�ǽsĶ�����A�o�ӺX�з|�л\�䥦���X�СA�ҥH�ڭ̤����M������O�I�C 
    cout.unsetf(ios::dec); // ����10�i����� 
    cout.setf(ios::hex | ios::scientific); // 16�i����ܩά�ǰO����� 
    cout << 12345 << "  " << 100 << endl; 
                                                                                
    cout.setf(ios::showpos | ios::showpoint); // ������� + ���B��ܤp���I 
    cout << 10.0 << ": " << -10.0 << endl; 
	system("pause");
    return 0; 
}
