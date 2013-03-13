
//---------------------------------------------------------------------------
//
// ThreadMonitor.cpp
//
// SUBSYSTEM: 
//              Monitoring process creation and termination  
//�ʵ��i�{�ЫةM�פ�
//				
// MODULE:    
//              Thread management
//
// DESCRIPTION:
//              Implement abstract interface provided by CCustomThread
//
//��{��H���f��CCustomThread����
// AUTHOR:		Ivo Ivanov
//                                                                         
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
// Includes
//
//---------------------------------------------------------------------------
#include "ThreadMonitor.h"
#include "NtDriverController.h"

//---------------------------------------------------------------------------
//
// class CThreadMonitor
//
//---------------------------------------------------------------------------
CProcessThreadMonitor::CProcessThreadMonitor(
	TCHAR*               pszThreadGuid,     // Thread unique ID
	CNtDriverController* pDriverController, // service controller
	CQueueContainer*     pRequestManager    // The underlying store
	):
	CCustomThread(pszThreadGuid),
	m_pRequestManager(pRequestManager),
	m_hKernelEvent(INVALID_HANDLE_VALUE),
	m_hDriverFile(INVALID_HANDLE_VALUE)
{
	assert(NULL != pDriverController);
	//
	// Store the pointe to the service controller, thus
	// we can use it later
//�s�x���y�A�ȱ���A�q��
//�ڭ̥i�H�Υ��ʶR
	//
	m_pDriverCtl = pDriverController;

	::ZeroMemory((PBYTE)&m_LastCallbackInfo, sizeof(m_LastCallbackInfo));
}

CProcessThreadMonitor::~CProcessThreadMonitor()
{

}

//
// A user supplied implementation of the thread function.
// Override Run() and insert the code that should be executed when 
// the thread runs.
//�Τᴣ�Ѫ��u�{��ƪ�����C
//���grun�]�^�����J�N�X�A�������
//�u�{�B��C
//
void CProcessThreadMonitor::Run()
{
	HANDLE handles[2] = 
	{
		m_hShutdownEvent,
		m_hKernelEvent
	};

	while (TRUE)
	{
		DWORD dwResult = ::WaitForMultipleObjects(
			sizeof(handles)/sizeof(handles[0]), // number of handles in array
			&handles[0],                        // object-handle array�Ʋդ��y�`�ƶq
			FALSE,                              // wait option
			INFINITE                            // time-out interval�W�ɮɶ����j
			);
		//
		// the system shuts down
		//
		if (handles[dwResult - WAIT_OBJECT_0] == m_hShutdownEvent)
			break;
		//
		// The kernel event has been just signaled
//���֨ƥ�w�H��
		//
		else
			RetrieveFromKernelDriver();
	} // while
}

//
// Perform action prior to activate the thread
//�����ʤ��e�E�����u�{
//
BOOL CProcessThreadMonitor::OnBeforeActivate()
{
	BOOL bResult = FALSE;
	//
	// Try opening the device driver
//���ե��}�]���X�ʵ{��
	//
	m_hDriverFile = ::CreateFile(
		TEXT("\\\\.\\ProcObsrv"),
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,                     // Default security
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,  // Perform asynchronous I/O
		0);                    // No template
	if (INVALID_HANDLE_VALUE != m_hDriverFile)
		//
		// Attach to kernel mode created event handle
//���[�줺�ּҦ��U�Ыت��ƥ�y�`
		//
		bResult = OpenKernelModeEvent();

	return bResult;
}

//
// Called after the thread function exits
//�u�{��ưh�X��ե�
//
void CProcessThreadMonitor::OnAfterDeactivate()
{
	if (INVALID_HANDLE_VALUE != m_hKernelEvent)
	{
		::CloseHandle(m_hKernelEvent);
		m_hKernelEvent = INVALID_HANDLE_VALUE;
	}
	if (INVALID_HANDLE_VALUE != m_hDriverFile)
	{
		::CloseHandle(m_hDriverFile);
		m_hDriverFile = INVALID_HANDLE_VALUE;
	}
}

//
// Attach to the particular kernel mode created event handle
//���[��S�w�����ּҦ��U�Ыت��ƥ�y�`
//
BOOL CProcessThreadMonitor::OpenKernelModeEvent()
{
	m_hKernelEvent = ::OpenEvent(
		SYNCHRONIZE, FALSE, TEXT("ProcObsrvProcessEvent") );

	return (INVALID_HANDLE_VALUE != m_hKernelEvent);
}

//
// Retrieve data from the kernel mode driver.
//�˯��ƾڱq���ּҦ��X�ʵ{�ǡC
//
void CProcessThreadMonitor::RetrieveFromKernelDriver()
{
	OVERLAPPED  ov          = { 0 };
	BOOL        bReturnCode = FALSE;
	DWORD       dwBytesReturned;
	PROCESS_CALLBACK_INFO  callbackInfo;
	QUEUED_ITEM queuedItem;         
	//
    // Create an event handle for async notification from the driver
//�q�X�ʾ����Ыؤ@�Ӳ��B�q���ƥ�y�`
	//
	ov.hEvent = ::CreateEvent(
		NULL,  // Default security�q�{���w����;
		TRUE,  // Manual reset��ʴ_��
		FALSE, // non-signaled state�D�H�����A
		NULL
		); 
	//
	// Get the process info
//����i�{�H��
	//
	bReturnCode = ::DeviceIoControl(
		m_hDriverFile,
		IOCTL_PROCOBSRV_GET_PROCINFO,
		0, 
		0,
		&callbackInfo, sizeof(callbackInfo),
		&dwBytesReturned,
		&ov
		);
	//
	// Wait here for the event handle to be set, indicating
	// that the IOCTL processing is completed.
//���ݨƥ�y�`�]�m�A����
//��IOCTL�B�z�����C
	//
	bReturnCode = ::GetOverlappedResult(
		m_hDriverFile, 
		&ov,
		&dwBytesReturned, 
		TRUE
		);
	//
	// Prevent duplicated events
//����ƨƥ�
	//
	if ( (m_LastCallbackInfo.bCreate != callbackInfo.bCreate) ||
	     (m_LastCallbackInfo.hParentId != callbackInfo.hParentId) ||
		 (m_LastCallbackInfo.hProcessId != callbackInfo.hProcessId) )
	{
		//
		// Setup the queued element
//�]�m�ƶ�����
		//
		::ZeroMemory((PBYTE)&queuedItem, sizeof(queuedItem));
		queuedItem.hParentId = callbackInfo.hParentId;
		queuedItem.hProcessId = callbackInfo.hProcessId;
		queuedItem.bCreate = callbackInfo.bCreate;
		//
		// and add it to the queue
//�ç⥦�K�[�춤�C
		//
		m_pRequestManager->Append(queuedItem);
		//
		// Hold last event
//�O���W���i�|
		//
		m_LastCallbackInfo = callbackInfo;
	} // if
	//
	//
	//
	if (ov.hEvent != NULL) 
		CloseHandle(ov.hEvent); 
		
}

//----------------------------End of the file -------------------------------

