#include "snake.h"
CSnake::CSnake(int x_pos,int y_pos,int len)
{
	if(len<1) len=1;
	int i;

	m_length=len;  //�D���������

	//��l�ƳD���y�Ц�m
	m_pPos=new SPoint[m_length+2];
	m_pPos[0].x=x_pos;m_pPos[0].y=y_pos;
	for(i=1;i<m_length+2;i++)
	{
		m_pPos[i].x=0;m_pPos[i].y=0;
	}

	//��l�ƳD���B�ʪ��A
	m_newSnake.head=S_NONE;
	m_oldSnake.head=S_NONE;
	m_newSnake.body=new MoveState[m_length];
	m_oldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
	{
		m_newSnake.body[i]=S_NONE;
		m_newSnake.body[i]=S_NONE;
	}
	m_newSnake.tail=S_NONE;
	m_oldSnake.tail=S_NONE;

	//��l�ƳD���I�}����ܪ��A
	m_pStateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		m_pStateArray[i]=M_NONE;
}

CSnake::~CSnake()
{
	SAFE_DELETE_ARRAY(m_pStateArray);
	SAFE_DELETE_ARRAY(m_pPos);
}

//
//�ھڷs�¨�Ө��骺�B���Ͷձ��p�A��^��e������ܪ����骬�A
//
BitmapState CSnake::GetRightState(MoveState oldDirect,MoveState newDirect)
{
	BitmapState res = M_NONE;
	switch(oldDirect)
	{
	case S_NONE:
		switch(newDirect)
		{
		case S_NONE:
			res=M_NONE;
			break;
		case S_UP:
			res=M_UP_UP;
			break;
		case S_DOWN:
			res=M_DOWN_DOWN;
			break;
		case S_LEFT:
			res=M_LEFT_LEFT;
			break;
		case S_RIGHT:
			res=M_RIGHT_RIGHT;
			break;
		}
		break;
	case S_UP:
		switch(newDirect)
		{
		case S_UP:
			res=M_UP_UP;
			break;
		case S_LEFT:
			res=M_UP_LEFT;
			break;
		case S_RIGHT:
			res=M_UP_RIGHT;
			break;
		}
		break;
	case S_DOWN:
		switch(newDirect)
		{
		case S_DOWN:
			res=M_DOWN_DOWN;
			break;
		case S_LEFT:
			res=M_DOWN_LEFT;
			break;
		case S_RIGHT:
			res=M_DOWN_RIGHT;
			break;
		}
		break;
	case S_LEFT:
		switch(newDirect)
		{
		case S_LEFT:
			res=M_LEFT_LEFT;
			break;
		case S_UP:
			res=M_LEFT_UP;
			break;
		case S_DOWN:
			res=M_LEFT_DOWN;
			break;
		}
		break;
	case S_RIGHT:
		switch(newDirect)
		{
		case S_RIGHT:
			res=M_RIGHT_RIGHT;
			break;
		case S_UP:
			res=M_RIGHT_UP;
			break;
		case S_DOWN:
			res=M_RIGHT_DOWN;
			break;
		}
		break;
	}
	return res;
}

//
//���ܤ�V
//
void CSnake::ChangeDirect(MoveState d)
{
	//  ���ܤ�V������G�D��ߤ�V
	//  �u��?�䥪�A�e�A�k��
	switch(d)
	{
	case S_NONE:
		m_newSnake.head=d;
		break;
	case S_UP:
		if(m_newSnake.head!=S_DOWN) m_newSnake.head=d;
		break;
	case S_DOWN:
		if(m_newSnake.head!=S_UP) m_newSnake.head=d;
		break;
	case S_LEFT:
		if(m_newSnake.head!=S_RIGHT) m_newSnake.head=d;
		break;
	case S_RIGHT:
		if(m_newSnake.head!=S_LEFT) m_newSnake.head=d;
		break;
	}
}

//
//�D����
//
void CSnake::Move(void)
{
	int i;
	//1.�p��s���A�U�Ӹ`�I�����A
	//�O�s�D����U�ӳ��쪺�Ϊ�
	for(i=0;i<m_length;i++)
	{
		m_oldSnake.body[i]=m_newSnake.body[i];
	}	

	//�N�D���骺���A�ھګe�������A�ܰʤ@��
	m_newSnake.tail=m_newSnake.body[m_length-1];
	for(i=m_length-1;i>0;i--)
	{
		m_newSnake.body[i]=m_newSnake.body[i-1];
	}
	m_newSnake.body[0]=m_newSnake.head;	

	//�ھڷs�ª��A�S�ʨ����T�����A
	m_pStateArray[0]=GetRightState(m_oldSnake.head,m_newSnake.head);
	for(i=0;i<m_length;i++)
		m_pStateArray[i+1]=GetRightState(m_oldSnake.body[i],m_newSnake.body[i]);
	m_pStateArray[m_length+1]=GetRightState(m_oldSnake.tail,m_newSnake.tail);


	//2.�N��ӳD���y�в���
	//���D�Y�~�A��L�������s��m?��e�@��������Ӧ�m
	for(i=m_length+1;i>0;i--)
		m_pPos[i]=m_pPos[i-1];
	//�D�Y���s��m�ھڳD���B�ʤ�V�P�_����������
	switch(m_newSnake.head)
	{
	case S_UP:
		m_pPos[0].y-=SNAKE_MOVE;
		break;
	case S_DOWN:
		m_pPos[0].y+=SNAKE_MOVE;
		break;
	case S_LEFT:
		m_pPos[0].x-=SNAKE_MOVE;
		break;
	case S_RIGHT:
		m_pPos[0].x+=SNAKE_MOVE;
		break;
	}

}

//
//�D������W��
//
void CSnake::AddBody(int n)
{

	//  ���t�{�ɪ�"save����"�ܼơA�Χ@�O�d
	//  �D���U�ظ�ƪ��A
	int i;
	Snake_Struct saveOldSnake,saveNewSnake;
	BitmapState *savestateArray;
	SPoint *savePos;

	//�O�s�D����m��T 
	// pos
	savePos=new SPoint[m_length+2];
	for(i=0;i<m_length+2;i++)
		savePos[i]=m_pPos[i];

	//�O�s�D�����A��T
	//  1.oldSnake
	//  2.newSnake
	//  3.stateArray

	//1
	saveOldSnake.head=m_oldSnake.head;
	saveOldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
		saveOldSnake.body[i]=m_oldSnake.body[i];
	saveOldSnake.tail=m_oldSnake.tail;
	//2
	saveNewSnake.head=m_newSnake.head;
	saveNewSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
		saveNewSnake.body[i]=m_newSnake.body[i];
	saveNewSnake.tail=m_newSnake.tail;
	//3
	savestateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		savestateArray[i]=m_pStateArray[i];

	//�N���׼W��
	m_length+=n;

	//����Ҧ��D������s�x��ƪŶ�
	delete[] m_oldSnake.body;m_oldSnake.body=NULL;
	delete[] m_newSnake.body;m_newSnake.body=NULL;
	delete[] m_pStateArray;m_pStateArray=NULL;
	delete[] m_pPos;m_pPos=NULL;

	//�Ыبê�l�ƼW���᪺�D���s�x��ƪŶ�

	m_newSnake.head=S_NONE;
	m_oldSnake.head=S_NONE;
	m_newSnake.body=new MoveState[m_length];
	m_oldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
	{
		m_newSnake.body[i]=S_NONE;
		m_newSnake.body[i]=S_NONE;
	}
	m_newSnake.tail=S_NONE;
	m_oldSnake.tail=S_NONE;

	m_pStateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		m_pStateArray[i]=M_NONE;
	m_pPos=new SPoint[m_length+2];
	for(i=0;i<m_length+2;i++)
	{
		m_pPos[i].x=0;
		m_pPos[i].y=0;
	}

	//��_��Ӫ��ת����(�s���Ϊ�l�ƪ����)
	//a. newSnake ,oldSnake���A
	//b. stateArray
	//c. pos

	//a
	m_newSnake.head=saveNewSnake.head;
	m_oldSnake.head=saveOldSnake.head;

		
	for(i=0;i<m_length-n;i++)
	{
		m_newSnake.body[0]=saveNewSnake.body[0];
		m_oldSnake.body[0]=saveOldSnake.body[0];
	}
	m_newSnake.tail=saveNewSnake.tail;
	m_oldSnake.tail=saveOldSnake.tail;
	
	//b
	for(i=0;i<m_length-n+2;i++)
		m_pStateArray[i]=savestateArray[i];

	//c
	for(i=0;i<m_length-n+2;i++)
		m_pPos[i]=savePos[i];
}

//
//�]�m�D�Y���y��
//
void CSnake::SetHeadPos(int x,int y)
{
	m_pPos[0].x=x;m_pPos[0].y=y;
}

//
//���D�����A���Ѱ}�C
//
BitmapState* CSnake::GetStateArray(void)
{
	return m_pStateArray;
}

//
//���D����m�}�C
//
SPoint* CSnake::GetPos(void)
{
	return m_pPos;
}

//
//���D��������
//
int CSnake::GetLength(void)
{
	return m_length+2;
}

//
//�˴��D�Y�O�_Ĳ�I��䨭��
//
bool CSnake::IsHeadTouchBody(int x,int y)
{
	int i;
	for(i=1;i<m_length+2;i++)
		if(m_pPos[i].x==x&&m_pPos[i].y==y) return true;
	return false;
}

//
//��l�� �Χ@�C�������᭫�s�}�l
//
void CSnake::Initial(void )
{
	//����H�e���Ҧ��s�x�Ŷ�
	SAFE_DELETE_ARRAY(m_pStateArray);
	SAFE_DELETE_ARRAY(m_pPos);

	//�ЫسD������?1���D�A�ð��U�ت�l��
	int i;
	int x = 0;
	int y = 0;

	//��l�ƳD���y�Ц�m
	m_length=1;
	m_pPos=new SPoint[m_length+2];
	m_pPos[0].x=x;m_pPos[0].y=y;
	for(i=1;i<m_length+2;i++)
	{
		m_pPos[i].x=0;m_pPos[i].y=0;
	}

	//��l�ƳD���B�ʪ��A
	m_newSnake.head=S_NONE;
	m_oldSnake.head=S_NONE;
	m_newSnake.body=new MoveState[m_length];
	m_oldSnake.body=new MoveState[m_length];
	for(i=0;i<m_length;i++)
	{
		m_newSnake.body[i]=S_NONE;
		m_newSnake.body[i]=S_NONE;
	}
	m_newSnake.tail=S_NONE;
	m_oldSnake.tail=S_NONE;

	//��l�ƳD���I�}����ܪ��A
	m_pStateArray=new BitmapState[m_length+2];
	for(i=0;i<m_length+2;i++)
		m_pStateArray[i]=M_NONE;
} 
