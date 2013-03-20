#include <windows.h>
#include <time.h>
#include "snaker.h"
#include "table.h"


#ifdef _DEBUG      // �ˬd�O���鬪�|��(��) 
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 
#define MYDEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__) 
#define new MYDEBUG_NEW 
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the 
//allocations to be of _CLIENT_BLOCK type 
#else 
#define MYDEBUG_NEW 
#endif // _DEBUG 

//�C�����A�w�q
#define GAME_STATE_WAIT     0  //�C�����ݪ��A
#define GAME_STATE_RUN      1  //�C���B�檬�A
#define GAME_STATE_END      2  //�C���������A

//������������ؤo�w�q
#define WALL_WIDTH             80  //�~��q������C���Ϫ��e��
#define WALL_HEIGHT            80  //�~��q������C���Ϫ�����

#define BMP_SCORE_BOARD_WIDTH  256 //���Ʀ줸�ϪO���e��
#define BMP_SCORE_BOARD_HEIGHT 55  //���Ʀ줸�ϪO������

#define BMP_WALL_WIDTH         16  //���I�}�Ϫ��e��
#define BMP_WALL_HEIGHT        16  //���I�}�Ϫ�����


void DrawGame(void);
void ShellDraw( HDC  hdc );
void GameAreaDraw(HDC hdc);

void OnTimer(UINT uTIMER_ID);
void StartGame( void );
void EndGame( void );

//�Ыؤ@�Ӯ�l
CTable table;

int tableBlockWidth = 0;  //��l����l���e��
int tableBlockHeight = 0; //��l����l������
int iScores = 0;          //�C�����o��

UINT uGameState = GAME_STATE_WAIT; //��e�C�����A

HDC windowDC = NULL;      //windows�ù��]��
HDC bufferDC = NULL;      //�w�ĳ]������
HDC picDC = NULL;         //snake�Ϲ��O����]��
HDC endDC = NULL;		 //�C���׵��Ϲ��O����]��
HDC scoreDC = NULL;      //���ƪO�O����]��

HWND hAppWnd = NULL;     //��application���f����X


HBITMAP picBMP = NULL;      //snake�Ϲ��I�}�ϱ���X
HBITMAP bufferBMP = NULL;   //�w���I�}�ϱ���X
HBITMAP endBMP = NULL;      //�C���׵��Ϲ��O���鱱��X
HBITMAP hbmpWall = NULL;    //���I�}�ϱ���X
HBITMAP hbmpScore = NULL;   //���ƪO�I�}�ϱ���X
HBRUSH hbrushWall = NULL;      //��e��

//�p�ɾ�����
UINT uSnakeMoveTimer;  //�D������
UINT uFoodAddTimer;    //���G��?��

//�ج[����m��Ʃw�q
//GDI RECT �Ӥ��O MFC CRect
RECT g_ClientRect;
RECT g_GameValueRect;
int g_iClientWidth;
int g_iClientHeight;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 
/* ************************************
* �\����ܤ@�ӵ���
**************************************/

int WINAPI WinMain (
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
	)
{	
	WNDCLASS wndClass;
	HWND hWnd;
	MSG msg;
	UINT width,height;
	

#ifdef _DEBUG   // �ˬd�O���鬪�|��(�i�J�I) 
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 	
	//_CrtSetBreakAlloc(71);
#endif 


	//�w�q���f
	wndClass.style=CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc=WndProc;
	wndClass.cbClsExtra=0;
	wndClass.cbWndExtra=0;
	wndClass.hInstance=hPrevInstance;
	wndClass.hIcon=LoadIcon(NULL,MAKEINTRESOURCE(IDI_MAIN));
	wndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName=NULL;
	wndClass.lpszClassName=TEXT("Snake_CLASS");
	//���U���f
	RegisterClass(&wndClass);


	//����ӿù����ؤo	
	width=GetSystemMetrics(SM_CXSCREEN);
	height=	GetSystemMetrics(SM_CYSCREEN);
	//�Ыص��f
	hWnd=CreateWindowA(
		"Snake_CLASS",
		"skyblue snake",
		WS_POPUP,
		0,0,
		width,height,
		NULL,NULL,
		hPrevInstance,
		NULL);

	hAppWnd = hWnd;

	//��ܵ���
	ShowWindow(hWnd,nShowCmd);
	UpdateWindow(hWnd);

	//������j�p
	GetClientRect(hAppWnd, &g_ClientRect);
	g_iClientWidth = g_ClientRect.right-g_ClientRect.left;
	g_iClientHeight = g_ClientRect.bottom-g_ClientRect.top;

	//�N�C���ϰ�����a�A�?20�����p���
	//�íp��C���ϰ쪺�j�p
	tableBlockWidth = (g_iClientWidth-2*WALL_WIDTH)/20;
	tableBlockHeight = (g_iClientHeight-2*WALL_HEIGHT)/20;

	//�����e�D�����]�ƻPwindowDC���p
	windowDC=GetDC(NULL);
	//�ЫػPwindowDC�ۮe���O����]������
	bufferDC=CreateCompatibleDC(windowDC);
	picDC=CreateCompatibleDC(windowDC);
	endDC=CreateCompatibleDC(windowDC);	
	scoreDC=CreateCompatibleDC(windowDC);	

	//hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0,0,LR_CREATEDIBSECTION);
	//�I�}�Ϫ���l�Ʃθ��J�I�}��	
	bufferBMP=CreateCompatibleBitmap(windowDC,g_iClientWidth,g_iClientHeight);
	picBMP=(HBITMAP)LoadImageA(NULL,"snake.bmp",IMAGE_BITMAP,160,80,LR_LOADFROMFILE);
	hbmpWall=(HBITMAP)LoadImageA(NULL,"brick.bmp",IMAGE_BITMAP,16,16,LR_LOADFROMFILE);
	endBMP = (HBITMAP)LoadImageA(NULL,"end.bmp",IMAGE_BITMAP,369,300,LR_LOADFROMFILE);
	hbmpScore=(HBITMAP)LoadImageA(NULL,"scoreboard.bmp",IMAGE_BITMAP,265,55,LR_LOADFROMFILE);
	//	picBMP=(HBITMAP)LoadImage(hCurrentInst,MAKEINTRESOURCE(IDB_BITMAP),IMAGE_BITMAP,160,80,LR_CREATEDIBSECTION);
	//	hbmpWall=(HBITMAP)LoadImage(hCurrentInst,MAKEINTRESOURCE(IDB_BITMAP_WALL),IMAGE_BITMAP,16,16,LR_CREATEDIBSECTION);
	//	endBMP = (HBITMAP)LoadImage(hCurrentInst,MAKEINTRESOURCE(IDB_BITGAMEEND),IMAGE_BITMAP,369,300,LR_CREATEDIBSECTION);	
	//	hbmpScore=(HBITMAP)LoadImage(hCurrentInst,MAKEINTRESOURCE(IDB_BITMAPSCORE),IMAGE_BITMAP,265,55,LR_CREATEDIBSECTION);

	//�n���I�}�ϻP�]�����Ҫ����p
	SelectObject(bufferDC,bufferBMP);
	SelectObject(picDC,picBMP);
	SelectObject(endDC,endBMP);
	SelectObject(scoreDC,hbmpScore);

	//�إߵe��P��W�۹������Ϲ������p�A
	//�H�ƥΨ�l�N���X�ӡA��PatBlt()��{
	hbrushWall = CreatePatternBrush(hbmpWall);

	StartGame();


	while(GetMessage(&msg,NULL,0,0))
	{		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,
						 WPARAM wParam,LPARAM lParam)
{

	switch(message)
	{
	case WM_TIMER :
		OnTimer((UINT)wParam);		
		break;		

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			exit(0);
			break;
		case VK_UP:
			table.ChangeSnakeDirect(S_UP);
			break;
		case VK_DOWN:
			table.ChangeSnakeDirect(S_DOWN);
			break;
		case VK_LEFT:
			table.ChangeSnakeDirect(S_LEFT);
			break;
		case VK_RIGHT:
			table.ChangeSnakeDirect(S_RIGHT);
			break;
		case VK_SPACE:
			if(	uGameState == GAME_STATE_END )
			{
				StartGame();
				break;
			}

		}
		return 0;
	case WM_SETCURSOR:
		SetCursor(NULL);
		return 0;
	case WM_DESTROY:
		ReleaseDC(hWnd,picDC);
		ReleaseDC(hWnd,bufferDC);
		ReleaseDC(hWnd,windowDC);
		PostQuitMessage(0);
		return 0;			
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}

void DrawGame(void)
{
	//ø�s�~�߰ϰ��w��
	ShellDraw(bufferDC);

	//ø�s�C���ϰ��w��
	GameAreaDraw(bufferDC);

	//�N��ӵe���q�w��DC�����X�ù�
	BitBlt(windowDC,0,0,g_iClientWidth,g_iClientHeight,bufferDC,0,0,SRCCOPY);
}



void OnTimer(UINT uTIMER_ID)
{
	if ( uTIMER_ID == uSnakeMoveTimer )
	{
		//���ʳD
		table.SnakeMove();

		//�˴��O�_�I�쨭��(��¶)�A�����C��
		if(table.GetSnake()->IsHeadTouchBody(table.GetSnake()->GetPos()[0].x,table.GetSnake()->GetPos()[0].y))
		{
			EndGame();
		}

		//�ھڳD�Y�Ҧb���ϰ�@�X�������B�z
		switch(table.GetData(table.GetSnake()->GetPos()[0].x,table.GetSnake()->GetPos()[0].y))
		{
		case TB_STATE_FOOD:
			table.ClearFood(table.GetSnake()->GetPos()[0].x,table.GetSnake()->GetPos()[0].y);
			table.AddBlock((rand())%tableBlockWidth,(rand())%tableBlockHeight);
			table.GetSnake()->AddBody();
			++iScores;
			break;
		case TB_STATE_BLOCK:
		case TB_STATE_SBLOCK:
			//�˴��O�_�I���ê���A�����C��
			EndGame();
			break;
		}

		//���
		DrawGame();
	}
	else if ( uTIMER_ID == uFoodAddTimer )
	{//�w�ɥ[����
		table.AddFood((rand())%tableBlockWidth,(rand())%tableBlockHeight);
	}
}

void StartGame()
{
	iScores=0;

	//�ୱ����l��
	table.InitialTable(tableBlockWidth,tableBlockHeight);
	table.GetSnake()->ChangeDirect(S_RIGHT);
	table.GetSnake()->SetHeadPos(tableBlockWidth/2,tableBlockHeight/2);

	//�w���H��?�ʹX�ӭ���
	srand( (unsigned)time(NULL) );
	for(int iFoodNum=0;  iFoodNum<4; iFoodNum++)
	{
		table.AddFood((rand())%tableBlockWidth,(rand())%tableBlockHeight);
	}
	//�����U�ؤl�]�i�H������rand(),
	//���O�C���C���}�l���O?�ͧ����@�˪�?�H�Y�ǦC

	//���}�p�ɾ�
	uSnakeMoveTimer = SetTimer(hAppWnd,500,100,NULL);
	uFoodAddTimer = SetTimer(hAppWnd,600,7000,NULL);

	uGameState = GAME_STATE_RUN;
}

void EndGame( void )
{
	//�����p�ɾ�
	KillTimer(hAppWnd,uSnakeMoveTimer);
	KillTimer(hAppWnd,uFoodAddTimer);
	uGameState = GAME_STATE_END;
}

void ShellDraw( HDC  hdc )
{	
	//	HDC hMemDc;
	//	BOOL ret = TRUE;
	//	HDC hMemoryDC;
	//	HBITMAP hbmp;
	//���ƴ�����ܤ�r
	char szText[30] = "Score: ";
	char szNum[20] = "";		

	int iNowScore = iScores*100;
	_itoa_s(iNowScore,szNum,10);
	strcat_s(szText,sizeof(szText), szNum);

	RECT rt, rect;
	GetClientRect(hAppWnd, &rt);
	//��ø�s
	SelectObject(hdc,hbrushWall);
	PatBlt(hdc,rt.left,rt.top,rt.right,rt.bottom,PATCOPY);
	//�����C���Ϫ��զ⩳����
	rect.left = rt.left+WALL_WIDTH;
	rect.top = rt.top + WALL_HEIGHT;
	rect.right = rt.right - WALL_WIDTH;
	rect.bottom = rt.bottom - WALL_HEIGHT;		
	FillRect(hdc, &rect, (HBRUSH) (COLOR_WINDOW+1));

	//���ƴ��ܪO��ø�s		
	/*	hMemoryDC =	CreateCompatibleDC(NULL);	
	hbmp = CreateCompatibleBitmap(hdc,265,55);		
	SelectObject(hMemoryDC,hbrushScore);	
	SelectObject(hMemoryDC,hbmp);	
	PatBlt(hMemoryDC,0,0,256,55,PATCOPY);	
	BitBlt(hdc,GetSystemMetrics(SM_CXSCREEN)/3,
	10,256,55,hMemoryDC,0,0,SRCCOPY);
	*/
	BitBlt(hdc,GetSystemMetrics(SM_CXSCREEN)/3,
		10,256,55,scoreDC,0,0,SRCCOPY);

	//���ƪ��C�Lø�s
	SetBkMode(hdc, TRANSPARENT); 	
	TextOutA(hdc, GetSystemMetrics(SM_CXSCREEN)/3+50, 30,szText,strlen(szText) );
}

void GameAreaDraw(HDC hdc)
{
	int i,j;
	int x,y, x_pos,y_pos;
	BitmapState  state;
	//char strMark[20];

	//ø�s���G�P �r�G
	for(i=0;i<tableBlockHeight;i++)
		for(j=0;j<tableBlockWidth;j++)
		{	
			x_pos = j*20+WALL_WIDTH;
			y_pos = i*20+WALL_HEIGHT;

			switch(table.GetData(j,i))
			{
			case TB_STATE_FOOD:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,0,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,0,SRCAND);
				break;
			case TB_STATE_BLOCK:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,0,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,0,SRCAND);
				break;
			}
		}

		//�ھڷ�e�����Aø�s�D�Y		
		x=table.GetSnake()->GetPos()[0].x;
		y=table.GetSnake()->GetPos()[0].y;
		x_pos = x*20+WALL_WIDTH;
		y_pos = y*20+WALL_HEIGHT;		
		state=table.GetSnake()->GetStateArray()[0];

		switch(state)
		{
		case M_UP_UP:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,20,SRCAND);
			break;
		case M_DOWN_DOWN:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,20,SRCAND);
			break;
		case M_LEFT_LEFT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,20,SRCAND);
			break;
		case M_RIGHT_RIGHT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,20,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,20,SRCAND);
			break;
		}

		//�ھڦU�ӳD���`�I�����Aø�s�D�����Ϊ�
		for(i=1;i<table.GetSnake()->GetLength()-1;i++)
		{
			x=table.GetSnake()->GetPos()[i].x;
			y=table.GetSnake()->GetPos()[i].y;
			x_pos = x*20+WALL_WIDTH;
			y_pos = y*20+WALL_HEIGHT;	
			state=table.GetSnake()->GetStateArray()[i];
			switch(state)
			{
			case M_UP_UP:
			case M_DOWN_DOWN:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,40,SRCAND);
				break;
			case M_LEFT_LEFT:
			case M_RIGHT_RIGHT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,40,SRCAND);
				break;
			case M_RIGHT_DOWN:
			case M_UP_LEFT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,100,60,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,20,60,SRCAND);
				break;
			case M_LEFT_DOWN:
			case M_UP_RIGHT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,80,60,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,0,60,SRCAND);
				break;
			case M_RIGHT_UP:
			case M_DOWN_LEFT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,40,SRCAND);
				break;
			case M_LEFT_UP:
			case M_DOWN_RIGHT:
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,40,SRCPAINT);
				BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,40,SRCAND);
				break;

			}
		}

		//ø�s�D����
		x=table.GetSnake()->GetPos()[table.GetSnake()->GetLength()-1].x;
		y=table.GetSnake()->GetPos()[table.GetSnake()->GetLength()-1].y;
		x_pos = x*20+WALL_WIDTH;
		y_pos = y*20+WALL_HEIGHT;	
		state=table.GetSnake()->GetStateArray()[table.GetSnake()->GetLength()-1];		
		switch(state)
		{
		case M_UP_UP:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,60,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,60,SRCAND);
			break;
		case M_DOWN_DOWN:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,120,0,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,40,0,SRCAND);
			break;
		case M_LEFT_LEFT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,60,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,60,SRCAND);
			break;
		case M_RIGHT_RIGHT:
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,140,0,SRCPAINT);
			BitBlt(hdc,x_pos,y_pos,20,20,picDC,60,0,SRCAND);
			break;
		}

		if(uGameState == GAME_STATE_END)
		{//ø�s�C�������Ϲ�
			x_pos = g_iClientWidth/3;
			y_pos = g_iClientHeight/4;

			BitBlt(hdc, x_pos, y_pos, 369, 300, endDC, 0, 0, SRCCOPY);			
		}
} 
