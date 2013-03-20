#ifndef _GREED_SNAKE_
#define _GREED_SNAKE_

#define SNAKE_MOVE 1
#define SAFE_DELETE(p) {delete (p);(p)=NULL;}
#define SAFE_DELETE_ARRAY(p) {delete[](p);(p)=NULL;}

#include <stdio.h>

//�`�I�Ϲ���ܹB�ʪ��A(��V)
enum BitmapState{M_NONE,M_UP_UP,M_DOWN_DOWN,M_LEFT_LEFT,M_RIGHT_RIGHT,
	M_UP_LEFT,M_UP_RIGHT,M_LEFT_UP,M_LEFT_DOWN,
	M_RIGHT_UP,M_RIGHT_DOWN,M_DOWN_RIGHT,M_DOWN_LEFT};

//�`�I�B�ʪ��A(��V)
enum MoveState{S_NONE,S_UP,S_DOWN,S_LEFT,S_RIGHT};

//�y�Ц�m���c
struct SPoint
{
	int x;
	int y;
};

class CSnake
{
	struct Snake_Struct//�w�q�D�骬�A
	{
		MoveState head;  //�Y��
		MoveState *body; //����
		MoveState tail; //����
	};

private:
	int m_length;                 //�D������
	Snake_Struct m_newSnake;      //�D���s�A���Ҧ��`�I�B�ʪ��A
	Snake_Struct m_oldSnake;      //�D����A���Ҧ��`�I�B�ʪ��A
	BitmapState *m_pStateArray;   //�D���Ҧ��`�I����I�}�Ϫ����A
	SPoint *m_pPos;                //�D��y��

private:
	BitmapState GetRightState(MoveState oldDirect,MoveState newDirect);

public:

	void Move(void);          
	void ChangeDirect(MoveState d);
	void AddBody(int n=1);
	void SetHeadPos(int x,int y);
	BitmapState* GetStateArray(void);
	SPoint* GetPos(void);
	bool IsHeadTouchBody(int x,int y);
	int GetLength( void );
	void Initial( void );

public:
	CSnake(int x_pos=0,int y_pos=0,int len=1);
	~CSnake();
};


#endif //_GREED_SNAKE_ 
