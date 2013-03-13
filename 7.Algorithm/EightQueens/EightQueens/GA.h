#ifndef GA_H
#define GA_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

// �V�������
#define GEN_LENGTH 8
// �C�@�N���ƶq
#define POPULATION_COUNT 50
// �c�l�N��
#define GENERATION_COUNT 10000
// ���ܾ��v
#define MUTATION_RATE 0.1
// �H������0~7���Ʀr
#define MyRand() (rand()%8)

class eightQ
{
public:
	eightQ();
	void randQ();
	int getScore();
	void show();
	vector<int> sit;
};


class GA
{
public:
	GA();
	void init();
	void reproduction();
	void crossover();
	void mutation();
	void show();
	eightQ theBest;
private:
	vector<eightQ> thisGen;
	vector<eightQ> DadPool;
	vector<eightQ> MomPool;
};
#endif