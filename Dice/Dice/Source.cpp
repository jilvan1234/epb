
#include "stdafx.h"

typedef struct dicedate
{
	char Role_Name[256];
	char Dice_reasons[256];
	char Quantity[256];
	char Dice_face[256];
	char Adjusted_value[256];
}dicedate;

// This is a typedef for a random number generator.
// Try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
typedef boost::minstd_rand base_generator_type;
// This is a reproducible simulation experiment.  See main().
void experiment(base_generator_type & generator);
const int ID_MYBUTTON = 60001;
const int ID_UPDATE = 60002;
const int IDS_LISTBOX = 60007;
int NumberID = 0;

HWND Role_Name = NULL;
HWND Dice_reasons = NULL;
HWND Quantity = NULL;
HWND Dice_face = NULL;
HWND Adjusted_value = NULL;
HWND Tlist= NULL;
HWND hList		= NULL;

int split(const std::string& str, std::vector<std::string>& ret_ );
void shellgrouoppget(HWND hwnd);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

/* ************************************
* �\����ܤ@�ӵ���
**************************************/
int WINAPI WinMain(HINSTANCE hinstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow) 
{     
	WNDCLASSEX wcx;         //�@������
	HWND hwnd;              //  �����B�z
	MSG msg;               //�@�T��    

	// ��R����������Ƶ��c
	wcx.cbSize = sizeof(wcx);// ���c�骺�j�p
	wcx.style = CS_HREDRAW | CS_VREDRAW;    // �˦��G�j�p���ܮɭ�ø���� 
	wcx.lpfnWndProc = WndProc; // �����T���B�z��� 
	wcx.cbClsExtra = 0;           // ���ϥ����O����
	wcx.cbWndExtra = 0;          // ���ϥε����O���� 
	wcx.hInstance = hinstance;// ���ݪ����ε{����ҳB�z 
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // �ϥܡG�ϥιw�]��
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);// �C�СG�ϥιw�]��
	wcx.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH);      // �I���G�զ�
	wcx.lpszMenuName =  NULL;  // ���G���ϥ�
	wcx.lpszClassName = TEXT("MainWClass");// �������W 
	wcx.hIconSm = (HICON)LoadImage(hinstance,// �p�ϥ�
		MAKEINTRESOURCE(5),
		IMAGE_ICON, 
		GetSystemMetrics(SM_CXSMICON), 
		GetSystemMetrics(SM_CYSMICON), 
		LR_DEFAULTCOLOR); 

	// ���U������
	if(!RegisterClassEx(&wcx))
	{
		return 1;
	}

	// �إߵ��� 
	hwnd = CreateWindow( 
		TEXT("MainWClass"),       // �����W
		TEXT("Dice"),            // �������D 
		WS_OVERLAPPEDWINDOW,// �����˦�  
		100,      // ���Ǧ줸�mX�G�ϥιw�]�� 
		100,      // �����줸�mY�G�ϥιw�]��
		640,       // �e�סG�ϥιw�]��
		480,       // ���סG�ϥιw�]��
		(HWND) NULL,         // �������G�L 
		(HMENU) NULL,        // ���G�ϥε���������� 
		hinstance,           // ���ε{����ҳB�z 
		(LPVOID) NULL);      // �����إ߮ɸ�ơG�L 

	if (!hwnd) 
	{
		return 1; 
	}
	// ��ܵ��� 

	RECT   rect;   
	int   ScreenWidth= GetSystemMetrics(SM_CXSCREEN);   
	int   ScreenHeight=  GetSystemMetrics(SM_CYSCREEN); 
	GetWindowRect(hwnd,&rect);
	int width = rect.right-rect.left;
	int height = rect.bottom-rect.top;
	MoveWindow(hwnd,ScreenWidth/2-width/2,ScreenHeight/2-height/2,width,height,TRUE);

	ShowWindow(hwnd, nCmdShow); 
	UpdateWindow(hwnd); 

	// �T���j��
	while (GetMessage(&msg, NULL, 0, 0))
	{  
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	} 


	return msg.wParam; 

} 
/* ************************************
* WndProc
* �\������T���B�z��ơA
��Ҧ����T�����ϥ�NULL�B�z���
**************************************/

LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (Message) 
	{ 
	case WM_CREATE: 
		{

			CreateWindowA("STATIC", "Role Name", WS_CHILD | WS_VISIBLE ,
				20, 15, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Dice reasons", WS_CHILD | WS_VISIBLE ,
				20, 85, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Quantity", WS_CHILD | WS_VISIBLE ,
				140, 15, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Dice face", WS_CHILD | WS_VISIBLE ,
				260, 15, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Adjusted value", WS_CHILD | WS_VISIBLE ,
				380, 15, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 
			Role_Name = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				20, 50, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Dice_reasons = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				140, 85, 200, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Quantity = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				140, 50, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Dice_face = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				260, 50, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Adjusted_value = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				380, 50, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindow(TEXT("BUTTON"), TEXT("���s1"), WS_CHILD | WS_VISIBLE ,
				500, 100, 100, 28, hwnd, HMENU(ID_MYBUTTON), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

			CreateWindow(TEXT("BUTTON"), TEXT("Update"), WS_CHILD | WS_VISIBLE ,
				500, 135, 100, 28, hwnd, HMENU(ID_UPDATE), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

			hList = CreateWindow(L"LISTBOX",NULL,
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER |
				LBS_STANDARD & (!LBS_SORT) | LBS_NOTIFY |WS_HSCROLL | WS_VSCROLL ,
				20, 120, 400, 300, hwnd, HMENU(IDS_LISTBOX), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
			/*
			Tlist = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
			500, 140, 100, 28, hwnd, NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL); */

			bearlib::wreadcfg(0);

		}
		break;
	case WM_COMMAND:
		// ��R�\���������:
		switch (LOWORD(wParam))
		{
			NumberID  = SendMessage (hList, LB_GETCURSEL, 0, 0) ;
		case ID_MYBUTTON:
			{	
				Sleep(300);
				sendCGlobal::ClientVerification();
				WCHAR strText[512];

				char   GetszText[30000]; 
				SendMessageA(Role_Name,WM_GETTEXT,10,(LPARAM)GetszText); 

				char   GetszText2[30000]; 
				SendMessageA(Dice_reasons,WM_GETTEXT,200,(LPARAM)GetszText2); 

				char   GetszText3[30000]; 
				SendMessageA(Quantity,WM_GETTEXT,10,(LPARAM)GetszText3); 

				char   GetszText4[30000]; 
				SendMessageA(Dice_face,WM_GETTEXT,10,(LPARAM)GetszText4); 

				char   GetszText5[30000]; 
				SendMessageA(Adjusted_value,WM_GETTEXT,10,(LPARAM)GetszText5); 

				if(strcmp(GetszText,"") == 0)
				{
					break;
				}
				if(strcmp(GetszText2,"") == 0)
				{
					break;
				}
				if(strcmp(GetszText3,"") == 0)
				{
					break;
				}
				if(strcmp(GetszText4,"") == 0)
				{
					break;
				}
				if(strcmp(GetszText5,"") == 0)
				{
					break;
				}

				std::string Temporary_str;
				Temporary_str = "Connection";
				Temporary_str += " ";
				Temporary_str += GetszText;
				Temporary_str += ",";
				Temporary_str += GetszText2;
				Temporary_str += ",";
				Temporary_str += GetszText3;
				Temporary_str += ",";
				Temporary_str += GetszText4;
				Temporary_str += ",";
				Temporary_str += GetszText5;

				sendCGlobal::CTransfer_instruction(Temporary_str);	

				try
				{
					boost::asio::io_service io_service;
					tcp::endpoint endpoint(boost::asio::ip::address_v4::from_string(bearlib::readcfg().c_str()),8100);
					boost::shared_ptr<sendclient> sendclient_ptr(new sendclient(io_service,endpoint));
					io_service.run();
				}
				catch (std::exception& e)
				{
					WCHAR strText[512];
					MultiByteToWideChar( CP_ACP, 0, e.what(), -1, strText, 510 );
					OutputDebugString(strText);     
				}

				sendCGlobal::CVerificationNumberR(sendCGlobal::CReceive_instructions().c_str());	

				MultiByteToWideChar( CP_ACP, 0, sendCGlobal::CReceive_instructions().c_str(), -1, strText, 510 );
				//MessageBox(NULL,strText,L"error",MB_OK |MB_ICONINFORMATION); 

				SendMessageA(hList,LB_ADDSTRING,0,(LPARAM)sendCGlobal::CReceive_instructions().c_str());

			}
			break;
		case ID_UPDATE:
			{	

				SendMessage (hList, LB_RESETCONTENT, 0, 0) ;
				sendCGlobal::ClientVerification();
				WCHAR strText[512];
				std::string Temporary_str;
				Temporary_str = "DiceUpdate";


				sendCGlobal::CTransfer_instruction(Temporary_str);	

				try
				{
					boost::asio::io_service io_service;
					tcp::endpoint endpoint(boost::asio::ip::address_v4::from_string(bearlib::readcfg().c_str()),8100);
					boost::shared_ptr<sendclient> sendclient_ptr(new sendclient(io_service,endpoint));
					io_service.run();
				}
				catch (std::exception& e)
				{
					WCHAR strText[512];
					MultiByteToWideChar( CP_ACP, 0, e.what(), -1, strText, 510 );
					OutputDebugString(strText);     
				}

				sendCGlobal::CVerificationNumberR(sendCGlobal::CReceive_instructions().c_str());	

				MultiByteToWideChar( CP_ACP, 0, sendCGlobal::CReceive_instructions().c_str(), -1, strText, 510 );
				//MessageBox(NULL,strText,L"error",MB_OK |MB_ICONINFORMATION); 
				/////////split

				std::vector<std::string> vt;
				split(sendCGlobal::CReceive_instructions().c_str(), vt);
				for (size_t i = 0; i < vt.size(); ++ i)
				{ 
					SendMessageA(hList,LB_ADDSTRING,0,(LPARAM)vt[i].c_str());
				}
				//////////////////////////////////////////


			}
			break;
		case IDS_LISTBOX:
			{	//LBN_DBLCLK
				if(HIWORD(wParam)==LBN_SELCHANGE)
				{					
					if (LB_ERR == (NumberID = SendMessage (hList, LB_GETCURSEL, 0, 0L)))
						break ;
					shellgrouoppget(hwnd);
				}					

			}
			break;	
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
		}
		break;
	case WM_KEYUP:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				{            
					SendMessage(hwnd, WM_DESTROY, NULL, NULL);
				}          
				break;
			}        
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		// TODO: �b���[�J����ø�ϵ{���X...
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY: 
		PostQuitMessage(0);
		return 0; 
	default: 
		return DefWindowProc(hwnd, Message, wParam, lParam); 
	} 
	return 0;
}



// This is a reproducible simulation experiment.  See main().
void experiment(base_generator_type & generator)
{
	// Define a uniform random number distribution of integer values between
	// 1 and 6 inclusive.
	typedef boost::uniform_int<> distribution_type;
	typedef boost::variate_generator<base_generator_type&, distribution_type> gen_type;
	gen_type die_gen(generator, distribution_type(1, 60));

	// If you want to use an STL iterator interface, use iterator_adaptors.hpp.
	boost::generator_iterator<gen_type> die(&die_gen);
	for(int i = 0; i < 10; i++)
		std::cout << *die++ << " ";
	std::cout << '\n';
}


void shellgrouoppget(HWND hwnd)
{	
	//strsafe.h���e���w�q#define STRSAFE_NO_DEPRECATE  �]���]�w��ĵ�i�����~�����Y
	//#define STRSAFE_NO_DEPRECATE
	static PTSTR 		pText ;
	HGLOBAL      		hGlobal ;
	PTSTR        		pGlobal ;	
	char cc[2048];
	SendMessageA (hList, LB_GETTEXT, NumberID, (LPARAM)cc);
	SetWindowTextA(Tlist,cc);

	TCHAR bb[2048];

	MultiByteToWideChar( CP_ACP, 0, cc, -1, bb, 2048 );

	pText = (PTSTR)malloc ((lstrlen (bb) + 1) * sizeof (TCHAR)) ;
	lstrcpy ((LPWSTR)pText, (LPCWSTR)bb) ;
	hGlobal = GlobalAlloc (GHND | GMEM_SHARE, 
		(lstrlen (pText) + 1) * sizeof (TCHAR)) ;
	pGlobal = (PTSTR)GlobalLock (hGlobal) ;
	lstrcpy (pGlobal, pText) ;
	GlobalUnlock (hGlobal) ;

	OpenClipboard (hwnd) ;
	EmptyClipboard () ;
	SetClipboardData (CF_UNICODETEXT, hGlobal) ;
	CloseClipboard () ;


}


int split(const std::string& str, std::vector<std::string>& ret_ )
{
	std::string sep = "\n";

	if (str.empty())
	{
		return 0;
	}

	string tmp;
	string::size_type pos_begin = str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}
