

#ifndef _GAME_TABLE_
#define _GAME_TABLE_

#define TB_STATE_OK                   0   //���`
#define TB_STATE_FOOD                 1   //����
#define TB_STATE_BLOCK                2   //��ê�Ьr�G
#define TB_STATE_SBLOCK               3   //��ê����

#include"snake.h"

class CTable
{
private:
	int m_width;          //��l���e��
	int m_height;         //��l������
	int m_foodNumber;     //���G���ƥ�
	int m_blockNumber;    //��ê��(�r�G)���ƥ�
	CSnake m_snake;       //��l�W���D
	int **m_board;          //��l���O

public:
	CTable();
	~CTable();

	//��l�Ʈ�l���O
	void InitialTable(int w,int h);

	//�������ާ@
	bool AddBlock(int x,int y);
	bool AddFood(int x,int y);
	bool ClearFood(int x,int y);

	//�������
	CSnake* GetSnake(void);
	int** GetBoard(void);
	int GetData(int x,int y);

	//�D���ާ@
	void SnakeMove(void);
	bool ChangeSnakeDirect(MoveState d);
};

#endif //_GAME_TABLE_ 
