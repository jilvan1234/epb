
//---------------------------------------------------------------------------
//
// CustomThread.cpp
//
// SUBSYSTEM: 
//              Monitoring process creation and termination  
//�l�t�ΡG
//�ʵ��i�{�ЫةM�פ�
// MODULE:    
//              Thread management 
//�Ҷ��G
//�u�{�޲z
//
// DESCRIPTION:
//              This is an abstract class that enables creation of separate 
//              threads of execution in an application. 
//�o�O�@�ө�H���A���\�إ߿W��
//�u�{���ε{�Ǫ�����C
//
// AUTHOR:		Ivo Ivanov
//                                                                         
//---------------------------------------------------------------------------
#include "CustomThread.h"
#include <process.h>
#include <assert.h>

//---------------------------------------------------------------------------
//
// Thread function prototype
//
//---------------------------------------------------------------------------
typedef unsigned (__stdcall *PTHREAD_START) (void *);

//---------------------------------------------------------------------------
//
// class CCustomThread 
//
// It is an abstract class that enables creation of separate threads of 
// execution.
//�o�O�@�ө�H���A���\�ЫؿW�߽u�{
//����C
//                                                                         
//---------------------------------------------------------------------------

HANDLE CCustomThread::sm_hThread = NULL;

CCustomThread::CCustomThread(TCHAR* pszThreadGuid):
	m_hShutdownEvent(NULL),
	m_bThreadActive(NULL),
	m_dwThreadId(NULL)
{
	if (NULL != pszThreadGuid)
		wcscpy_s(m_szThreadGuid, pszThreadGuid);
	else
		wcscpy_s(m_szThreadGuid, TEXT(""));
}

CCustomThread::~CCustomThread()
{	
	SetActive( FALSE );
}

//
// Activate / Stop the thread 
//�E��/����u�{
//
void CCustomThread::SetActive(BOOL bValue)
{
	BOOL bCurrent = GetIsActive();

	if (bValue != bCurrent)
	{
		if (!bCurrent)
		{
			//
			// Perform action prior to activate the thread
//�����ʤ��e�E�����u�{
			//
			if (!OnBeforeActivate())
				return;

			if (0 != _tcslen(m_szThreadGuid))
				m_hShutdownEvent = ::CreateEvent(NULL, FALSE, FALSE, m_szThreadGuid);
			ULONG ulResult = _beginthreadex(
				(void *)NULL,
				(unsigned)0,
				(PTHREAD_START)CCustomThread::ThreadFunc,
				(PVOID)this,
				(unsigned)0,
				(unsigned *)&m_dwThreadId
				);
			if (ulResult != -1)
				//
				// Wait until the thread gets activated
//���ݡA����ӽu�{�Q�E��
				//
				while (!GetIsActive())
				{
				}
		} 
		else
		{
			if ( GetIsActive() )
			{
				if (NULL != m_hShutdownEvent)
					//
					// Signal the thread's event
//�H�����u�{���ƥ�
					//
					::SetEvent(m_hShutdownEvent);
				//
				// Wait until the thread is done
//���ݡA����u�{����
//
				//
				while (GetIsActive())
				{
				}
				//
				// Called after the thread function exits
//�u�{��ưh�X��ե�
				//
				OnAfterDeactivate();
			} // if
			if (NULL != m_hShutdownEvent)
				::CloseHandle(m_hShutdownEvent);
		}
	} // if
}

//
// Indicates whether the driver has been activated
//��ܸ��X�ʵ{�ǬO�_�w�Q�E��
//
BOOL CCustomThread::GetIsActive()
{
	CLockMgr<CCSWrapper> lockMgr(m_CritSec, TRUE);	
	return m_bThreadActive;
}

//
// Setup the attribute
//�]�m�ݩ�
//
void CCustomThread::SetIsActive(BOOL bValue)
{
	CLockMgr<CCSWrapper> lockMgr(m_CritSec, TRUE);	
	m_bThreadActive = bValue;
}


//
// Return the handle to the thread's shut down event
//��^�u�{�y�`�������ƥ�
//
HANDLE CCustomThread::Get_ShutdownEvent() const
{
	return m_hShutdownEvent;
}

//
// Primary thread entry point
//�D�u�{���J�f�I
//
unsigned __stdcall CCustomThread::ThreadFunc(void* pvParam)
{
	CCustomThread* pMe = (CCustomThread*)( pvParam );
	// retrieves a pseudo handle for the current thread
//�˯���e�u�{�����y�`
	sm_hThread = GetCurrentThread();
	try
	{
		pMe->SetIsActive( TRUE );
		// Execute the user supplied method
//����Τᴣ�Ѫ���k
		pMe->Run();
	}
	catch (...)
	{
		// Handle all exceptions
//�B�z�Ҧ����`
	}
	pMe->SetIsActive( FALSE );
	_endthreadex(0);
	return 0;
}


//
// Perform action prior to activate the thread
//�����ʤ��e�E�����u�{
//
BOOL CCustomThread::OnBeforeActivate()
{
	// Provide default implementation
//�����q�{����{
	return TRUE;
}

//
// Called after the thread function exits
//�u�{��ưh�X��ե�
//
void CCustomThread::OnAfterDeactivate()
{
	// Do nothing
//����]����
}

//----------------------------End of the file -------------------------------