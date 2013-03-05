
#include "stdafx.h"


// This is a typedef for a random number generator.
// Try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
typedef boost::minstd_rand base_generator_type;
// This is a reproducible simulation experiment.  See main().
void experiment(base_generator_type & generator);
/*
�����N�O�Y��L�W��...�Ϊ̦ܤ�255��
�ƶq
�뭱
�վ��
��Ϋh�O�ĤG�եH�W���ƶq�P�뭱
���L���ҥu�Ψ�D6�ҥH�O��ܩʥ[�J�\���_A_
�M��N�O���}��
������ηN�O���F�ऽ�}�Y��
X ���uX�v �Y�F�u5 d 6 + 13�v �A�Y�X�u1�B2�B5�B5�B3�v�A�`�X���u29�v�C
Quantity
Dice face
Adjusted value
*/
const int ID_MYBUTTON = 60001;

HWND Role_Name = NULL;
HWND Dice_reasons = NULL;
HWND Quantity = NULL;
HWND Dice_face = NULL;
HWND Adjusted_value = NULL;

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


	//����h�}�{��
	TCHAR strappname[] = TEXT("Management"); 
    HANDLE hmutex = NULL; 
    //�Ыؤ�����H 
    hmutex = CreateMutex(NULL, false, strappname); 
    if (hmutex != NULL) 
    { 
		if (GetLastError() == ERROR_ALREADY_EXISTS) 
		{ 
			MessageBox(NULL,TEXT("�t�~�@�{���|�b����I���������{��"),TEXT("SMSServer"),MB_OK |MB_ICONINFORMATION); 
			//����������H�A�h�X�{�� 
			SendMessage (hwnd, WM_DESTROY, 0, 0) ;			
			CloseHandle(hmutex); 
        return FALSE; 
		} 
    } 
    else 
    { 
        MessageBox(NULL,TEXT("�L�k�إ�Mutex!�Э��s����"),TEXT("SMSServer"),MB_OK |MB_ICONINFORMATION); 
        //����������H�A�h�X�{�� 
		SendMessage (hwnd, WM_DESTROY, 0, 0) ;		
		if(hmutex != NULL)
			CloseHandle(hmutex); 
        return FALSE; 
    }

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
			/*
			Role Name:
			Dice reasons:
			�ƶq �뭱 �վ��
			Role_Name 
			Dice_reasons
			Quantity
			Dice face
			Adjusted value
			��Ϋh�O�ĤG�եH�W���ƶq�P�뭱
			���L���ҥu�Ψ�D6�ҥH�O��ܩʥ[�J�\���_A_*/
			//Ctrl+K->Ctrl+D
			
			bearlib::wreadcfg(0);

			sendCGlobal::ClientVerification();
			WCHAR strText[512];
		{
			//
		
		std::string Temporary_str;
		Temporary_str = "Connection";
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
			 MessageBox(NULL,strText,L"error",MB_OK |MB_ICONINFORMATION); 
			//
		}
			CreateWindowA("STATIC", "Role Name", WS_CHILD | WS_VISIBLE ,
				20, 24, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Dice reasons", WS_CHILD | WS_VISIBLE ,
				140, 24, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Quantity", WS_CHILD | WS_VISIBLE ,
				260, 24, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Dice face", WS_CHILD | WS_VISIBLE ,
				380, 24, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindowA("STATIC", "Adjusted value", WS_CHILD | WS_VISIBLE ,
				500, 24, 100, 28, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 
			Role_Name = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				20, 55, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Dice_reasons = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				140, 55, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Quantity = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				260, 55, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Dice_face = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				380, 55, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			Adjusted_value = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				500, 55, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 

			CreateWindow(TEXT("BUTTON"), TEXT("���s1"), WS_CHILD | WS_VISIBLE ,
				500, 100, 100, 28, hwnd, HMENU(ID_MYBUTTON), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

			//	SetWindowTextA(Quantity,"cc");

		}
		break;
	case WM_COMMAND:
		// ��R�\���������:
		switch (LOWORD(wParam))
		{
		case ID_MYBUTTON:
			{		

				char   szText[256]; 
				SendMessageA(Quantity,WM_GETTEXT,10,(LPARAM)szText); 

				char   szText2[256]; 
				SendMessageA(Dice_face,WM_GETTEXT,10,(LPARAM)szText2); 

				int a,b,c;
				a = atoi(szText);
				b = atoi(szText2);
				c = a + b;
				char ch1[256];
				sprintf_s(ch1,"%d",c);

				MessageBoxA(NULL, ch1 ,"Error" , MB_OK);


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