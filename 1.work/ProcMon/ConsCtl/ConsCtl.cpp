
//---------------------------------------------------------------------------
//
// ConsCtl.cpp
//
// SUBSYSTEM: 
//              Monitoring process creation and termination  
//�l�t�ΡG
//�ʵ��i�{�ЫةM�פ�
//
// MODULE:    
//				Control application for monitoring NT process and 
//              DLLs loading observation. 
//�Ҷ��G
//�������ε{�ǩM�ʴ�NT�i�{
// DLL���[���[��C
//
// DESCRIPTION:
//
// AUTHOR:		Ivo Ivanov
//                                                                         
//---------------------------------------------------------------------------

#include "Common.h"
#include <conio.h>
#include <tchar.h>
#include "ApplicationScope.h"
#include "CallbackHandler.h"
#include <iostream>
//
// This constant is declared only for testing putposes and
// determines how many process will be created to stress test
// the system
//���`�q�ť�����putposes�u
//�M�w���h�ֶi�{�N�Ы����O����
//�t��
//

//---------------------------------------------------------------------------
// 
// class CWhatheverYouWantToHold
//
// Implements a dummy class that can be used inside provide callback 
// mechanism. For example this class can manage sophisticated methods and 
// handles to a GUI Win32 Window. 
//��{�F�@�ӵ��������A�i�Ω󤺴��Ѧ^��
//����C�Ҧp�A�o�����i�H�޲z��������k�A
//�B�z�@��GUI Win32���f�C
//
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// 
// class CWhatheverYouWantToHold
//
// Implements a dummy class that can be used inside provide callback 
// mechanism. For example this class can manage sophisticated methods and 
// handles to a GUI Win32 Window. 
//��{�F�@�ӵ��������A�i�Ω󤺴��Ѧ^��
//����C�Ҧp�A�o�����i�H�޲z��������k�A
//�B�z�@��GUI Win32���f�C
//
//---------------------------------------------------------------------------

class CWhatheverYouWantToHold
{
public:
	CWhatheverYouWantToHold()
	{
		wcscpy_s(m_szName, TEXT("This could be any user-supplied data."));
		hwnd = NULL;
	}
private:
	TCHAR  m_szName[MAX_PATH];
	// 
	// You might want to use this attribute to store a 
	// handle to Win32 GUI Window
//�A�i��Q�ϥΦ��ݩʨӦs�x
//�B�z��Win32 GUI���f
	//
	HANDLE hwnd;
};


//---------------------------------------------------------------------------
// 
// class CMyCallbackHandler
//
// Implements an interface for receiving notifications
//��{�@�ӱ��f�A�Ω󱵦��q��
//
//---------------------------------------------------------------------------
class CMyCallbackHandler: public CCallbackHandler
{
	//
	// Implements an event method
//��{�@�Өƥ��k
	//
	virtual void OnProcessEvent(
		PQUEUED_ITEM pQueuedItem, 
		PVOID        pvParam
		)
	{
		TCHAR szFileName[MAX_PATH];
		//
		// Deliberately I decided to put a delay in order to 
		// demonstrate the queuing / multithreaded functionality 
//�G�N�A�ڨM�w��H����
//�t�ܱƶ�/�h�u�{�\��
		//
		::Sleep(500);
		//
		// Get the dummy parameter we passsed when we 
		// initiated process of monitoring (i.e. StartMonitoring() )
//����ѼơA�ڭ�passsed��ڭ̪����H
//�Ұʺʴ��i�{�]�YStartMonitoring�]�^�^
		//
		CWhatheverYouWantToHold* pParam = static_cast<CWhatheverYouWantToHold*>(pvParam);
		//
		// And it's about time to handle the notification itself
//�����ɶ��ӳB�z���q������
		//
		if (NULL != pQueuedItem)
		{
			TCHAR szBuffer[1024];
			::ZeroMemory(
				reinterpret_cast<PBYTE>(szBuffer),
				sizeof(szBuffer)
				);
			GetProcessName(
				reinterpret_cast<DWORD>(pQueuedItem->hProcessId), 
				szFileName, 
				MAX_PATH
				);
			if (pQueuedItem->bCreate)
			{
				//
				// At this point you can use OpenProcess() and
				// do something with the process itself
//���ɡA�z�i�H�ϥ�OpenProcess�]�^�M
//����L�{�����F�襻��
				//
				wsprintf(
					szBuffer,
					TEXT("Process has been created: PID=%.8X %s\n"),
					pQueuedItem->hProcessId,
					szFileName
					);
				OutputDebugString(szBuffer);    
			}
			else
			{
				wsprintf(
					szBuffer,
					TEXT("Process has been terminated: PID=%.8X\n"),
					pQueuedItem->hProcessId);
				OutputDebugString(szBuffer); 
			}
			//
			// Output to the console screen
//��X�챱��x�̹�
			//
			_tprintf(szBuffer);
		} // if
	}
};

//---------------------------------------------------------------------------
// Perform
//
// Thin wrapper around __try..__finally
//���k__���]�˹���.. __finally
//---------------------------------------------------------------------------


void Perform(
	CCallbackHandler*        pHandler,
	CWhatheverYouWantToHold* pParamObject
	)
{
	CApplicationScope& g_AppScope = CApplicationScope::GetInstance(
		pHandler     // User-supplied object for handling notifications
		);//�Τᴣ�Ѫ���H�B�z���q��
	__try
	{
		//
		// Initiate monitoring
//�Ұʺʴ�
		//
		g_AppScope.StartMonitoring(
			pParamObject // Pointer to a parameter value passed to the object 
			); //�ѼƭȪ����w�ǻ�����H
		
		
		while(!_kbhit())
		{
			Sleep(100);
		}
	//	_getch();
		Sleep(100);
	}
	__finally
	{
		//
		// Terminate the process of observing processes
//�פ��[��i�{���L�{��
		//
		g_AppScope.StopMonitoring();
	}
}


//---------------------------------------------------------------------------
// 
// Entry point
//
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{	
	CMyCallbackHandler      myHandler;
	CWhatheverYouWantToHold myView; 
	Perform( &myHandler, &myView );

	return 0;
}
//--------------------- End of the file -------------------------------------
