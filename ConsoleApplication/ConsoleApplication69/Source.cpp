
#include <iostream> 
#include <fstream> 
using namespace std; 
/*
�bC+ +���ϥΨ�ӫ��ШӾާ@�ɮסA�@�ӬO get ���СA���|���V�ɮפ��U�@�ӿ�JŪ������m�A�t�@�ӬO put ���СA
���|���V�ɮפ��U�@�ӿ�X�g�J����m�A�o��ӫ��Цb�C�@��Ū���μg�J�ɡA���|�`�Ǫ����U�@�Ӧ�m���ʡA
�ڭ̥i�H�ϥ�seekg()�Ӿާ@ get ���СA�ϥ�seekp()�Ӿާ@ put ���СA�O�ɮק@�D�`�Ǫ��s���C 

seekg()�Pseekp()���禡�����p�U�G 
istream &seekg(off_type type, seekdir origin); 
ostream &seekg(off_type, seekdir origin); 


�䤤off_type�Oios�ҩw�q����ƫ��A�A�q�`�O�@��long��ơA��seekdir�h�O��ios�ҩw�q���C�|�ȡA�p�U�G 
ios::beg	���ɮ׭�seek
ios::cur	�ѥثe����mseek
ios::end	���ɮק���seek
seekg()�Pseekp()�Y�����wseekdir�A�h�ѥثe����m�}�l�A�ڭ̤]�i�H��tellg()��tellp()�ӱo��ثe get ���лP put ���Ъ���m�G 
pos_type tellg() 
pos_type tellp() 


�n�i��D�`�Ǫ��ɮצs���A�q�`�|�ϥΤG�i��Ҧ��A�åB�N��ƥH�@�w�j�p����Ƶ��c�]�˰_�ӡA
�U�@�ӥD�D�N�|�ݨ�A���ާ@ get ���й�`�ǩʪ��ɮפ]����n�B�A
�Ҧp�ڭ̥i�H�b��r�ɮפ��x�s�ǥͪ���ƨöi��d�ߡA�d�ߪ��ʧ@�ä��@�w�g�L�@���A
�ҥH�ڭ̥i�H�b�C���d�߫�A�Nget�� �в����ɮ׭��A�H�K�A���d�ߡA�U���o�ӵ{���O��²�檺�ܽd�G 
*/
int main() { 
    ifstream fin("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt"); 
    if(!fin) { 
        cout << "�L�kŪ���ɮ�\n"; 
        return 1; 
    } 

    char name[30]; 
    int request, account, score; 

	
    cout << "��J�ﶵ:" << endl
         << "1) ��ܩҦ��ǥͻP����" << endl
         << "2) ��ܤή�ǥͻP����" << endl
         << "3) ��ܤ��ή�ǥͻP����" << endl
         << "4) ���}" << endl;
	
    while(true) { 
        cout << "\n�ﶵ? "; 
        cin >> request; 
        if(request == 4) 
            break; 

        switch(request) { 
            case 1: 
                cout << "\n�Ҧ��ǥͻP����:" << endl;
                break; 
            case 2: 
                cout << "\n�ή�ǥͻP����:" << endl;
                break; 
            case 3: 
                cout << "\n���ή�ǥͻP����:" << endl;
                break; 
			default:
				break;
        } 
		
	std::system("cls");
    cout << "��J�ﶵ:" << endl
         << "1) ��ܩҦ��ǥͻP����" << endl
         << "2) ��ܤή�ǥͻP����" << endl
         << "3) ��ܤ��ή�ǥͻP����" << endl
         << "4) ���}\n" << endl;
	

        fin >> account >> name >> score; 
        while(!fin.eof()) { 
            if((request == 1) || (request == 2 && score >= 60) || 
               (request == 3 && score < 60)) 
                cout << account << "\t" << name << "\t" << score << endl; 

            fin >> account >> name >> score; 
        } 

        fin.clear();  // ���m eof 
        fin.seekg(0);  // get ���в����ɮ׭� 
    } 

    fin.close(); 
	std::system("pause");

    return 0; 
}


/*
�p�Gdata.txt���ɮפ��e�p�U�G 
 1       Justin  90 
2       Momor   90 
3       Bush    75 
4       John    50 
5       Bob     65 
6       Rich    53 
7       Doe     41 
8       Bill    85 
9       Jason   67 
10      Jones   88

//

�����r�ɮפ��A�X�D�`�Ǧs���A�z�ѫ�²��A��r�ɮת����e���g�L�r���ഫ�A���]�{�b�����ɮפ����ⵧ��Ʀp�U�A�䤤�ťլ�'\t'�G 
1       Justin  90 
2       Momor   90 


�p�G�{�b�ڧ��F�Ĥ@����Ʀp�U�G 
1       caterpillar  90 


�h�ĤG����Ʒ|�Q�л\�A�p�G�O�bLinux�U�A���欰'\n'�A�h���G�|�p�U�G 
1       caterpillar  90or   90 

�ѩ�r���ഫ�᪺��ƪ��רä��T�w�A�ҥH��r�ɮרä��A�X�D�`�Ǧs���C 
*/