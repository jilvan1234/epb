#include "..\\applay_entry.h"
#include "server_crl_fun.h"
//�禡�\�� : �إߪA��
//CreatrServic(�A�ȥy�� , �{�����| , �A�ȦW�� , �㦡�W��)
BOOL CreatrServic(SC_HANDLE schmang , LPSTR szpath,LPSTR servername , LPSTR showname)
{

	SC_HANDLE schService;
	schService = CreateService(schmang,servername,showname,SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_DEMAND_START,SERVICE_ERROR_NORMAL,szpath,\
	NULL,			  //�ϥΪ̲պA
	NULL,			  //�ϥΤw�s�b����
	NULL,			  //�W�ߪA��
	NULL,			  //�����t�αb��
	NULL              //�K�X
	);
	if(schService == NULL)
	{
		return FALSE;
	}
	else
	{
		CloseServiceHandle(schService);
		return TRUE;
	}
}
//�禡�\�� : �R���A��
//
BOOL DeleteService( SC_HANDLE schmang,LPSTR ServiceName )
{
	SC_HANDLE schService;
	schService = OpenService(schService,ServiceName ,DELETE);
	if(schService == NULL)
	{
		return FALSE;
	}
	if(!DeleteService(schService))
	{
		return FALSE;
	}
	CloseServiceHandle(schService);
	return TRUE;
}
BOOLEAN StaetService(SC_HANDLE sc ,LPTSTR ServiceName)
{

	return FALSE;
}
void ERROR_SHOW(std::string erroemsg)
{
	std::cout <<erroemsg <<std::endl;
}


//�C�|�A��
BOOLEAN EnumService()
{
	DWORD dwBytesRequired;
	DWORD dwTotalServices;
	DWORD ResumeHandle = 0 ;

	ENUM_SERVICE_STATUS_PROCESS* pessp = NULL;
	SC_HANDLE scc= OpenSCManager(NULL,NULL,SC_MANAGER_ENUMERATE_SERVICE);
	if(scc ==NULL)
	{
		ERROR_SHOW("#1 scc ==NULL");
		return false;
	}
	BOOL bRet = EnumServicesStatusEx(\
		scc,SC_ENUM_PROCESS_INFO ,\
		SERVICE_WIN32,SERVICE_STATE_ALL,(LPBYTE)pessp,0,&dwBytesRequired,\
		&dwTotalServices,&ResumeHandle,NULL);
	//Error

		
		DWORD dwError = GetLastError();

		if(ERROR_MORE_DATA == dwError)
		{
			DWORD dwBufferSize = dwBytesRequired;
			pessp = (ENUM_SERVICE_STATUS_PROCESS*)malloc(dwBytesRequired);

			bRet = EnumServicesStatusEx(scc,SC_ENUM_PROCESS_INFO ,\
			SERVICE_WIN32,SERVICE_STATE_ALL,(LPBYTE)pessp,dwBufferSize,&dwBytesRequired,\
			&dwTotalServices,&ResumeHandle,NULL);
			if(bRet == false)
			{
				ERROR_SHOW("#2 bRet == false");
				free(pessp);
				return false;
			}
			//TCHAR* szOutput = (TCHAR*)malloc(1024);
			for(DWORD i = 0 ; i < dwTotalServices ; i++)
			{
				//LPWSTR hj = L"cccc";
				//std::cout << hj<<std::endl;
				//std::cout << pessp[i].lpServiceName<<std::endl;
			//	WriteConsole(NULL,pessp[i].lpServiceName,wstrlen(pessp[i].lpServiceName),NULL,0);
				printf("%S :: %S ::%x\n",pessp[i].lpServiceName,pessp[i].lpDisplayName,pessp[i].ServiceStatusProcess);
			}

			free(pessp);

	}
		CloseServiceHandle(scc);

	return true;
}
BOOLEAN StopService ()
{

	return FALSE;
}