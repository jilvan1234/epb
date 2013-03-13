//---------------------------------------------------------------------------
//
// RetrievalThread.cpp
//
// SUBSYSTEM: 
//              Monitoring process creation and termination  
//�ʵ��i�{�ЫةM�פ�
//				
// MODULE:    
//              Provides an interface for handling queued items
//���Ѥ@�ӱ��f�B�z�ƶ�����
//
// DESCRIPTION:
//
// AUTHOR:		Ivo Ivanov
//                                                                         
//---------------------------------------------------------------------------
#include "RetrievalThread.h"
#include "QueueContainer.h"

//---------------------------------------------------------------------------
//
// class CRetrievalThread
//
//---------------------------------------------------------------------------

CRetrievalThread::CRetrievalThread(
	TCHAR*            pszThreadGuid,
	CQueueContainer*  pQueue
	):
	CCustomThread(pszThreadGuid),
	m_pQueue(pQueue)
{
	assert( NULL != m_pQueue );
}

CRetrievalThread::~CRetrievalThread()
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
void CRetrievalThread::Run()
{
	m_pQueue->WaitOnElementAvailable();
}

//----------------------------End of the file -------------------------------