
#include <bearlib.h>
#include <windows.h>
#include <iostream>
#include "ScrectKey\SCardAPI.h"
#include "phc_tst.h"
#include <boost\thread.hpp>


const int ID_MYBUTTON = 60001;
const int ID_MYBUTTON2 = 60002;
const int ID_MYBUTTON3 = 60003;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

int WINAPI WinMain(HINSTANCE hinstance, 
                             HINSTANCE hPrevInstance, 
                             LPSTR lpCmdLine, 
                             int nCmdShow) 
{     
    WNDCLASSEX wcx;         					//�@������
    HWND hwnd;             	 				//  �����B�z
    MSG msg;               					//�@�T��    
   
    // ��R����������Ƶ��c
    wcx.cbSize = sizeof(wcx);				// ���c�骺�j�p
    wcx.style = CS_HREDRAW | CS_VREDRAW;    // �˦��G�j�p���ܮɭ�ø���� 
    wcx.lpfnWndProc = WndProc; 			// �����T���B�z��� 
    wcx.cbClsExtra = 0;           			// ���ϥ����O����
    wcx.cbWndExtra = 0;          			// ���ϥε����O���� 
    wcx.hInstance = hinstance;				// ���ݪ����ε{����ҳB�z 
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);  					// �ϥܡG�ϥιw�]��	
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);						// �C�СG�ϥιw�]��
    wcx.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH);      					// �I���G�զ�
    wcx.lpszMenuName =  NULL;  				// ���G���ϥ�
    wcx.lpszClassName = "MainWClass";			// �������W 
	wcx.hIconSm = (HICON)LoadImage(hinstance,	// �p�ϥ�
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
          "MainWClass",       	// �����W
          "Test",            	// �������D 
         WS_OVERLAPPEDWINDOW,	// �����˦�  
         100,      	// ���Ǧ줸�mX�G�ϥιw�]�� 
         100,      	// �����줸�mY�G�ϥιw�]��
         640,       	// �e�סG�ϥιw�]��
         480,       	// ���סG�ϥιw�]��
         (HWND) NULL,         	// �������G�L 
         (HMENU) NULL,        	// ���G�ϥε���������� 
         hinstance,           	// ���ε{����ҳB�z 
         (LPVOID) NULL);      	// �����إ߮ɸ�ơG�L 
 
        if (!hwnd) 
        {
               return 1; 
         }
         // ��ܵ��� 
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

HWND gtest	= NULL;
HWND gtest2	= NULL;
static unsigned long UsageCount = 0;

#define One ((int)(UsageCount > 30000)) 


LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;	
	
    switch (Message) 
    { 						
		case WM_CREATE: 		
		{			
			gtest = CreateWindow(TEXT("EDIT"), TEXT("gg"), WS_CHILD | WS_VISIBLE ,
				80, 200, 300, 20, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

			gtest2 = CreateWindow(TEXT("EDIT"), TEXT("gg"), WS_CHILD | WS_VISIBLE ,
				80, 250, 300, 20, hwnd, NULL, 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

				CreateWindow(TEXT("BUTTON"), TEXT("save"), WS_CHILD | WS_VISIBLE ,
				80, 135, 80, 20, hwnd, HMENU(ID_MYBUTTON), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
				CreateWindow(TEXT("BUTTON"), TEXT("load"), WS_CHILD | WS_VISIBLE ,
				80, 165, 80, 20, hwnd, HMENU(ID_MYBUTTON2), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
				CreateWindow(TEXT("BUTTON"), TEXT("count"), WS_CHILD | WS_VISIBLE ,
				80, 185, 80, 20, hwnd, HMENU(ID_MYBUTTON3), 
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
		}
		break;	
		case WM_COMMAND:
			// ��R�\���������:		
		switch (LOWORD(wParam))
		{
		case ID_MYBUTTON:
			{												
				int var[25] ;
				UsageCount = 60000;
				var[0] = UsageCount;
				loadtable();
				SCard_SetIntArr(21,var);
				SCard_Save(21,1);
			}
			break;
		case ID_MYBUTTON2:
			{
				int var[25] ; 						
				loadtable();			
				SCard_Load(21,1);			
				SCard_GetIntArr(21,var);		
				char cc[25];
				sprintf(cc,"%d",Show_pool_int(21)[0]);
				SetWindowText(gtest2,cc);	
			}
			break;
		case ID_MYBUTTON3:
			{			

				int var[25]; 						
				loadtable();		
				//get
				SCard_Load(21,1);			
				SCard_GetIntArr(21,var);					
				unsigned long y = Show_pool_int(21)[0];
				unsigned long z = y+1;
				y *= y;
				y -= 1;
				UsageCount = y / z;
				//set
				var[0] = UsageCount;				
				SCard_SetIntArr(21,var);
				SCard_Save(21,1);				
				char cc[255];
				sprintf(cc,"%lu",Show_pool_int(21)[0]);
				SetWindowText(gtest2,cc);

					
				char ccd[255];
				sprintf(ccd,"%d",One);
				SetWindowText(gtest,ccd);

				
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

