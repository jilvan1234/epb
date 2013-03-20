#include "table.h"


CTable::CTable()
{
	m_width=m_height=0;
	m_foodNumber=m_blockNumber=0;
	m_board=NULL;
}

CTable::~CTable()
{
	if(m_board != NULL)
	{
		SAFE_DELETE_ARRAY(m_board);
	}
}

//
//// ��l�Ʈ�l
//
void CTable::InitialTable(int w,int h)
{//��l��Table

	int i,j;
	//���s�]�m��l�����׻P�e��
	m_width=w;
	m_height=h;

	//��L�����ܼƪ��M�ũʽ��l��
	m_snake.Initial();
	if(m_board != NULL)
	{
		SAFE_DELETE_ARRAY(m_board);
	}

	//�ھڰ��שM�e�׳Ыؤ@�ӷs����l
	m_board=new int*[m_height];
	for(i=0;i<h;i++)
	{
		m_board[i]=new int[m_width];
		for(j=0;j<w;j++)
			m_board[i][j]=0;
	}

	//�N��l�|�P�]�m?��
	//�N�����򩳳�����t�]�m?��ê���𪺪��A
	for(i=0;i<h;i++)
	{
		m_board[i][0]=TB_STATE_SBLOCK;
		m_board[i][m_width-1]=TB_STATE_SBLOCK;
	}
	//�N�����M�k������t�]�m?��ê���𪺪��A
	for(i=0;i<w;i++)
	{
		m_board[0][i]=TB_STATE_SBLOCK;
		m_board[m_height-1][i]=TB_STATE_SBLOCK;
	}
}

//
//// �b�Y�Ӧ�m��m�r�G
//
bool CTable::AddBlock(int x,int y)
{

	if( (x>=0)&&(x<m_width)&&
		(y>=0)&&(y<m_height)&&
		(m_board[y][x]==TB_STATE_OK) ) 
	{
		m_board[y][x]=TB_STATE_BLOCK;
		++m_blockNumber;
		return true;
	}
	else
	{
		return false;
	}
}

//
//// �b�Y�Ӧ�m��m���G
//
bool CTable::AddFood(int x,int y)
{
	if( (x>=0)&&(x<m_width)&&
		(y>=0)&&(y<m_height)&&
		(m_board[y][x]==TB_STATE_OK) ) 
	{
		m_board[y][x]=TB_STATE_FOOD;
		++m_foodNumber;
		return true;
	}
	else
	{
		return false;
	}
}

//
//// �M���Y�Ӧ�m���G��
//
bool CTable::ClearFood(int x,int y)
{
	m_board[y][x]=TB_STATE_OK;
	return true;
}

//
//// ����D����
//
CSnake* CTable::GetSnake(void)
{
	return &m_snake;
}

//
//// ����l����
//
int** CTable::GetBoard(void)
{
	return m_board;
}

//
//// ����l�Y�Ӧ�m���
//
int CTable::GetData(int x,int y)
{
	return m_board[y][x];
}

//
//// �D������
//
void CTable::SnakeMove(void)
{
	m_snake.Move();
}

//
//// ���ܳD����V 
//
bool CTable::ChangeSnakeDirect(MoveState d)
{
	m_snake.ChangeDirect(d);
	return true;
} 
