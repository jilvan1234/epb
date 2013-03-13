#include "GA.h"

int main()
{
	srand((unsigned)time(0));
	GA ga;
	int nCounter = 0;

	// ��l��
	ga.init();
	cout << "��]�t��k�}�l" << endl;
	while(nCounter < GENERATION_COUNT)
	{
		ga.reproduction();
		ga.crossover();
		ga.mutation();
		//ga.show();
		++nCounter;
		//cout << "��" << nCounter << "�N�c�ާ����I" << endl;

		// �Y�̦n������w�g���A�Y�i�����C
		if(ga.theBest.getScore() >= 28)
			break;
	}
	cout << "��" << nCounter << "�N�Ҧ�����p�U�ҥܡG" << endl;
	ga.show();
	cout << "�̨θѬ�";
	ga.theBest.show();
	cout << "����Ƭ�" << ga.theBest.getScore() << endl;	
	system("PAUSE");
	return 0;
}