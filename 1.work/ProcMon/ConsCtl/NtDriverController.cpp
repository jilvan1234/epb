
//---------------------------------------------------------------------------
//
// NtDriverController.cpp
//
// SUBSYSTEM: 
//              Monitoring process creation and termination  
//�ʵ��i�{�ЫةM�פ�
//				
// MODULE:    
//				Provides simple interface for managing device driver 
//����²�檺�ɭ��޲z�]���X�ʵ{��
//              administration
//
// DESCRIPTION:
//
// AUTHOR:		Ivo Ivanov
//                                                                         
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// Includes
//
//---------------------------------------------------------------------------
#include "Common.h" 
#include "NtDriverController.h"
#include <tchar.h>
#include "winutils.h"


//---------------------------------------------------------------------------
//
// class CNtDriverController
//
//---------------------------------------------------------------------------

CNtDriverController::CNtDriverController():
	m_hSCM(NULL),
	m_hDriver(NULL),
	m_bDriverStarted(FALSE),
	m_bErrorOnStart(FALSE)
{
	if (TRUE == Open())
	{
		wcscpy_s(m_szName, TEXT("ProcObsrv"));
		wcscpy_s(m_szInfo, TEXT("Process creation detector."));
		TCHAR szFullFileName[MAX_PATH];
		GetProcessHostFullName(szFullFileName);
		if ( TRUE == 
			 ReplaceFileName(
				szFullFileName, TEXT("ProcObsrv.sys"), m_szFullFileName) )
			m_bDriverStarted = InstallAndStart();
	} // if
}

CNtDriverController::~CNtDriverController()
{
	Close();
}


//
// Obtain manager handle
//
BOOL CNtDriverController::Open()
{
	m_hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	return (m_hSCM != NULL);
}

//
// Close handle obtained from Open()
//
void CNtDriverController::Close()
{
	if (m_hDriver != NULL)
	{
		::CloseServiceHandle(m_hDriver);
		m_hDriver = NULL;
	}
	if (m_hSCM != NULL)
	{
		::CloseServiceHandle(m_hSCM);
		m_hSCM = NULL;
	} 
}

//
// Wait until driver reaches desired state or error occurs
//�X�ʵ{�ǵ��ݡA����F��z�Q���A�εo�Ϳ��~
//
BOOL CNtDriverController::WaitForState(
	DWORD           dwDesiredState, 
	SERVICE_STATUS* pss
	) 
{
	BOOL bResult = FALSE;
	if (NULL != m_hDriver)
	{
		// Loop until driver reaches desired state or error occurs
//�`���X�ʵ{�ǡA����F��z�Q���A�εo�Ϳ��~
		while (1)
		{
			// Get current state of driver
//����X�ʵ{�Ǫ���e���A
			bResult = ::QueryServiceStatus(m_hDriver, pss);
			// If we can't query the driver, we're done
//�p�G�ڭ̤���d���X�ʵ{�ǡA�ڭ̴N�j�\�i���F
			if (!bResult) 
				break;
			// If the driver reaches the desired state
//�p�G�q���F��z�Q�����A
			if (pss->dwCurrentState == dwDesiredState) 
				break;
			// We're not done, wait the specified period of time
//�ڭ̨S���o�˰��A���ݫ��w���ɶ���
			DWORD dwWaitHint = pss->dwWaitHint / 10;    // Poll 1/10 of the wait hint
			if (dwWaitHint <  1000) dwWaitHint = 1000;  // At most once a second
			if (dwWaitHint > 10000) dwWaitHint = 10000; // At least every 10 seconds
			::Sleep(dwWaitHint);
		} // while
	} // if

	return bResult;
}


//
// Add the driver to the system and start it up
//�K�[�X�ʨt�ΡA�ñҰʥ�
//
BOOL CNtDriverController::InstallAndStart()
{
	BOOL bResult = FALSE;

	if (NULL != m_hSCM)
	{
		m_hDriver = ::CreateService(
			m_hSCM, 
			m_szName, 
			m_szInfo,
			SERVICE_ALL_ACCESS,
			SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			m_szFullFileName, 
			NULL, 
			NULL,
			NULL, 
			NULL, 
			NULL
			);
		if (NULL == m_hDriver)
		{
			if ( (::GetLastError() == ERROR_SERVICE_EXISTS) ||
			     (::GetLastError() == ERROR_SERVICE_MARKED_FOR_DELETE) )
				m_hDriver = ::OpenService(
					m_hSCM,
					m_szName,
					SERVICE_ALL_ACCESS
					);
		}
		if (NULL != m_hDriver)
		{
			SERVICE_STATUS serviceStatus = { 0 };
			bResult = ::StartService(m_hDriver, 0, NULL);
 			if (bResult)
				bResult = WaitForState(SERVICE_RUNNING, &serviceStatus);	
			else
				bResult = (::GetLastError() == ERROR_SERVICE_ALREADY_RUNNING);
			// We should call DeleteService() if the SCM reports an error
			// on StartService(). Otherwise, the service will remain loaded
			// in an undesired state
//�ڭ����өI�~DeleteService�]�^�p�GSCM���i���~
//�W��StartService�]�^�C�_�h�A�ӪA�ȱN�~��[��
//�b�@�Ӥ����w�諸���A
			if (!bResult)
			{
				// Mark the service for deletion.
//�аO���R�����A�ȡC
				::DeleteService(m_hDriver);
				if (m_hDriver != NULL)
				{
					::CloseServiceHandle(m_hDriver);
					m_hDriver = NULL;
				}
				m_bErrorOnStart = TRUE;
			}
		} // if
	} // if

	return bResult;
}

//
// Stop the driver and remove it from the system
//�����X�ʵ{�ǡA�ñq�t�Τ��R��
//
void CNtDriverController::StopAndRemove()
{
	if ((NULL != m_hDriver) && (!m_bErrorOnStart))
	{
		BOOL bResult;
		SERVICE_STATUS serviceStatus = { 0 };
		// Notifies a service that it should stop. 
//�q���A�ȡA�����Ӱ���C
		bResult = ::ControlService(m_hDriver, SERVICE_CONTROL_STOP, &serviceStatus);
		if (bResult)
			bResult = WaitForState(SERVICE_STOPPED, &serviceStatus);	
		// Mark the service for deletion.
//�аO���R�����A�ȡC
		::DeleteService(m_hDriver);
	} // if
}

//----------------------------End of the file -------------------------------