
#include "stdafx.h"


// This is a typedef for a random number generator.
// Try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
typedef boost::minstd_rand base_generator_type;
// This is a reproducible simulation experiment.  See main().
void experiment(base_generator_type & generator);
const int ID_MYBUTTON = 60001;
const int IDS_LISTBOX = 60007;
int NumberID = 0;

HWND Role_Name = NULL;
HWND Dice_reasons = NULL;
HWND Quantity = NULL;
HWND Dice_face = NULL;
HWND Adjusted_value = NULL;
HWND Tlist= NULL;
HWND hList		= NULL;

void shellgrouoppget();
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
	//�Ыؤ����ﹳ 
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
			Role_Name 
			Dice_reasons
			Quantity
			Dice face
			Adjusted value*/
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

			hList = CreateWindow(L"LISTBOX",NULL,
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER |
				LBS_STANDARD & (!LBS_SORT) | LBS_NOTIFY |WS_HSCROLL | WS_VSCROLL ,
				20, 120, 400, 300, hwnd, HMENU(IDS_LISTBOX), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

			Tlist = CreateWindowA("Edit", "", WS_CHILD | WS_VISIBLE |WS_BORDER,
				500, 140, 100, 28, hwnd, NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL); 


		}
		break;
	case WM_COMMAND:
		// ��R�\���������:
		switch (LOWORD(wParam))
		{
			NumberID  = SendMessage (hList, LB_GETCURSEL, 0, 0) ;
		case ID_MYBUTTON:
			{		

				char   szText[30000]; 
				SendMessageA(Quantity,WM_GETTEXT,10,(LPARAM)szText); 

				char   szText2[30000]; 
				SendMessageA(Dice_face,WM_GETTEXT,10,(LPARAM)szText2); 

				char   szText3[30000]; 
				SendMessageA(Adjusted_value,WM_GETTEXT,10,(LPARAM)szText3); 
				
				int a,b,c;
				a = atoi(szText);
				b = atoi(szText2);
				c = atoi(szText3);
			//	c = a + b;
			//	char ch1[256];
				//sprintf_s(ch1,"%d",c);
				std::string sbuf = "";
				//				MessageBoxA(NULL, ch1 ,"Error" , MB_OK);

				base_generator_type generator(42);
				generator.seed(static_cast<unsigned int>(std::time(0)));
				base_generator_type saved_generator = generator;
				typedef boost::uniform_int<> distribution_type;
				typedef boost::variate_generator<base_generator_type&, distribution_type> gen_type;
				int face=b;
				gen_type die_gen(generator, distribution_type(1, face));

				// If you want to use an STL iterator interface, use iterator_adaptors.hpp.
				boost::generator_iterator<gen_type> die(&die_gen);
				int cc=0;
				int sum=0;
				int teeth=a;
				int Adjusted=c;
				int Additional=0;
				char chbuf[10];
				std::vector<int> numbers; 

				for(int i = 0; i < teeth+1; i++)
				{
					numbers.push_back(*die++); 
				}
				numbers.erase(numbers.begin());

				sbuf += "X ���uX�v �Y�F�u" ;	
				_itoa_s(teeth,chbuf,10); 
				sbuf += chbuf;
				sbuf +=  " d " ;				
				_itoa_s(face,chbuf,10); 
				sbuf +=  chbuf;
				sbuf += " + ";	
				_itoa_s(Adjusted,chbuf,10); 
				sbuf += chbuf;
				sbuf += "�v �A�Y�X�u";
				printf("\nX ���uX�v �Y�F�u%d d %d + %d�v �A�Y�X�u",teeth,face,Adjusted);

				int sizz = numbers.size();
				for(int i=0;i<sizz;i++)
				{
					if(i == sizz-1)
					{
						_itoa_s(numbers[i],chbuf,10); 
						sbuf += chbuf;
						std::cout <<numbers[i];
						sum = sum + numbers[i];
						if(numbers[i] == 6)
							Additional++;
					}
					else
					{
						_itoa_s(numbers[i],chbuf,10); 
						sbuf += chbuf;
						sbuf += "�B";
						std::cout <<numbers[i]<<"�B";
						sum = sum + numbers[i];

						if(numbers[i] == 6)
							Additional++;
					}

				}


				boost::generator_iterator<gen_type> die2(&die_gen);
				if(Additional>0)
				{
					sbuf += "�l�[1d6 ";
				_itoa_s(Additional,chbuf,10); 
					sbuf += chbuf;
					sbuf += "��:";
					printf("�l�[1d6 %d��:",Additional);
				}

				int sum2=0;
				int aa=0;

				int Additional2=0;//0304
				boost::generator_iterator<gen_type> die3(&die_gen);// 0304

				int n = 1;
				for(int i=0;i<Additional;i++)
				{	  /*
					base_generator_type generator(42);
					generator.seed(static_cast<unsigned int>(std::time(0)));
					base_generator_type saved_generator = generator;

					typedef boost::uniform_int<> distribution_type;
					typedef boost::variate_generator<base_generator_type&, distribution_type> gen_type;  
					gen_type die_gen(generator, distribution_type(1, 6));

					boost::generator_iterator<gen_type> die(&die_gen);
					int aa=0;
					for(int i=0;i<n;i++)
					{	  
						aa = *die++;
						sbuf += " " ;
						_itoa_s(aa,chbuf,10); 
						sbuf += chbuf ; 
						sbuf += " ";
						std::cout<<" "<<aa<<" ";

					}*/
					aa = *die2++;
					sum2 = sum2 + aa;
					_itoa_s(aa,chbuf,10); 
					sbuf += chbuf ;
					sbuf += " ";
					std::cout<<aa<<" ";

				}
				sbuf += "�v�A�`�X���u";
				int csum=0;
				csum =  sum + Adjusted + sum2;				
				_itoa_s(csum,chbuf,10); 
				sbuf += chbuf;
				sbuf += "�v�C";
				printf("�v�A�`�X���u%d�v�C\n",sum + Adjusted + sum2);

				sbuf += "";
				std::cout << '\n';

				SendMessageA(hList,LB_ADDSTRING,0,(LPARAM)sbuf.c_str());
				

				///////////////
			}
			break;
		case IDS_LISTBOX:
			{	//LBN_DBLCLK
				if(HIWORD(wParam)==LBN_SELCHANGE)
				{					
					if (LB_ERR == (NumberID = SendMessage (hList, LB_GETCURSEL, 0, 0L)))
						break ;
						shellgrouoppget();
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


void shellgrouoppget()
{

	//SendMessage (hList, LB_RESETCONTENT, 0, 0) ;
	//SendMessage(hList,LB_ADDSTRING,0,(LPARAM)"ccccc");		
	char cc[30000];
	SendMessageA (hList, LB_GETTEXT, NumberID, (LPARAM)cc);
	//SendMessage (hList, LB_SETCURSEL, NumberID, 0) ;
	SetWindowTextA(Tlist,cc);
}

