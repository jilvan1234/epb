//---------------------------------------------------------------------------
//
// LockMgr.cpp
//
// SUBSYSTEM: 
//				Generic libraries
//�q�ήw
// MODULE:    
//              Interface declaration of CCSWrapper CRITICAL_SECTION wrapper 
//���f��CCSWrapper CRITICAL_SECTION���]���n��
//
// DESCRIPTION:
//              
//
// AUTHOR:		Ivo Ivanov
//                                                                         
//---------------------------------------------------------------------------
#include "LockMgr.h"

//---------------------------------------------------------------------------
//
// class CCSWrapper 
//
// CRTICIAL_SECTION user object wrapper
// CRTICIAL_SECTION���Τ��H�]��
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// Constructor
//
//---------------------------------------------------------------------------
CCSWrapper::CCSWrapper()
{
	m_nSpinCount = 0;
	::InitializeCriticalSection( &m_cs );
}

//---------------------------------------------------------------------------
//
// Destructor
//
//---------------------------------------------------------------------------
CCSWrapper::~CCSWrapper()
{
	::DeleteCriticalSection( &m_cs );
}


//---------------------------------------------------------------------------
// Enter 
//
// This function waits for ownership of the specified critical section object 
//�o�Ө�Ƶ��ݫ��w���{�ɰϹ�H���Ҧ��v
//---------------------------------------------------------------------------
void CCSWrapper::Enter()
{
	::EnterCriticalSection( &m_cs );
	m_nSpinCount++;
}

//---------------------------------------------------------------------------
// Leave
//
// Releases ownership of the specified critical section object. 
//�o�����w���{�ɰϹ�H���Ҧ��v�C
//---------------------------------------------------------------------------
void CCSWrapper::Leave()
{
	m_nSpinCount--;
	::LeaveCriticalSection( &m_cs );
}

//--------------------- End of the file -------------------------------------
