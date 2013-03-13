#include "GA.h"

////////////////////////////////////////////////////////////////////

eightQ::eightQ()
{
	randQ();
}

// �H�����ͤ@�ո�
void eightQ::randQ()
{
	sit.clear();
	for(int i = 0 ; i < GEN_LENGTH ; ++i)
	{
		sit.push_back(MyRand());
	}
}

// �p�⦹�ոѪ�����
int eightQ::getScore()
{
	int nScore = 0;
	for (int i = 0; i < GEN_LENGTH; ++i)
	{
		int iPosX = i;
		int iPoxY = sit[i];
		//�P��L�ӦZ���
		for (int j = i + 1; j < GEN_LENGTH; ++j)
		{
			//�Y���P���ӦZ�PROW
			if (!(iPoxY == sit[j]))
				//�Y���b���ӦZ�k�פW
				if (!(iPoxY - iPosX == sit[j] - j))
					//�Y���b���ӦZ�k�פU
					if (!(iPosX + iPoxY == sit[j] + j))
						nScore++;
		}
	}
	return nScore;
}

void eightQ::show()
{
	for(int i = 0 ; i < GEN_LENGTH ; ++i)
		cout << sit[i];
	cout << endl;
}

////////////////////////////////////////////////////////////////////

GA::GA()
{
	init();
}

void GA::init()
{
	eightQ newQ;
	// �H�����ͲĤ@�N
	for(int i = 0 ; i < POPULATION_COUNT ; ++i)
	{
		newQ.randQ();
		thisGen.push_back(newQ);
	}
	theBest = newQ;
}

void GA::reproduction()
{
	DadPool.clear();
	MomPool.clear();
	int nScoreSum = 0;
	vector<int> vAccumulate;
	// �N���N�Ҧ����骺�A���O�֥[
	for(int i = 0 ; i < POPULATION_COUNT ; ++i)
	{
		nScoreSum += thisGen[i].getScore();
		vAccumulate.push_back(nScoreSum);
	}
	// �̷ӾA���O����ҿ�ܥ��˻P����
	for(int i = 0 ; i < POPULATION_COUNT ; ++i)
	{
		int nRand = rand() % nScoreSum;
		for(int j = 0 ; j < POPULATION_COUNT ; ++j)
			if(nRand < vAccumulate[j])
			{
				DadPool.push_back(thisGen[j]);
				break;
			}
		nRand = rand() % nScoreSum;
		for(int j = 0 ; j < POPULATION_COUNT ; ++j)
			if(nRand < vAccumulate[j])
			{
				MomPool.push_back(thisGen[j]);
				break;
			}
		
	}
}

void GA::crossover()
{
	int nPos;
	thisGen.clear();
	// �ϥγ��I����
	for(int i = 0 ; i < POPULATION_COUNT ; ++i)
	{
		// �M�w�����m 3~6
		nPos = rand()%4 + 3;
		eightQ newQ;
		// �e���ϥΪ������V����
		for(int j = 0 ; j < nPos ; ++j)
		{
			newQ.sit[j] = DadPool[i].sit[j];
		}
		// �᭱�ϥζ������V����
		for(int j = nPos ; j < GEN_LENGTH ; ++j)
		{
			newQ.sit[j] = MomPool[i].sit[j];
		}
		thisGen.push_back(newQ);
	}
}

void GA::mutation()
{
	// �C�@�ӬV����P�_�n���n����
	for(int i = 0 ; i < POPULATION_COUNT ; ++i)
	{
		double dRate = (double)(rand() % 10000) / 10000.0f;
		if(dRate < MUTATION_RATE)
		{
			// �M�w���ܦ�m
			int nPos = MyRand();
			thisGen[i].sit[nPos] = MyRand();
		}
		// �p��O�_��̨θѧ�n
		if(thisGen[i].getScore() > theBest.getScore())
			theBest = thisGen[i];
	}
}

void GA::show()
{
	for(int i = 0 ; i < POPULATION_COUNT ; ++i)
	{
		thisGen[i].show();
	}
}
