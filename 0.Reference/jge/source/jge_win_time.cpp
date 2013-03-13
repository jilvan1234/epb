#include "jge_win_time.h"
#include "jge_debug.h"
_JGE_BEGIN

LARGE_INTEGER WinTime::mLintTC;
//////////////////////////////////////////////////////////////////////////
WinTime::WinTime() : mnTime(0)
{
	//�����}�l�ɶ�
	SetZero();
}
//////////////////////////////////////////////////////////////////////////
WinTime::~WinTime()
{

}
//////////////////////////////////////////////////////////////////////////
boole WinTime::fnInitialize()
{
	//���o�C��cpu�W�v
	QueryPerformanceFrequency(&mLintTC);
	_JGE_DBGLOGLN(L"cpu�C%f���s�v : %I64d",1.0f/DEF_JGE_ONE_SEC,mLintTC.QuadPart/DEF_JGE_ONE_SEC);
	return mLintTC.QuadPart > DEF_JGE_ONE_SEC;
}


//////////////////////////////////////////////////////////////////////////
void WinTime::SetZero() 
{
	mnTime = 0;
	QueryPerformanceCounter(&mLintBegin);
}
//////////////////////////////////////////////////////////////////////////
void WinTime::Get(TimeData& timeData) const
{
	
	
}
//////////////////////////////////////////////////////////////////////////
void WinTime::Get(uint64& nTime) const
{	
	//���o���
	nTime = mnTime / (mLintTC.QuadPart / DEF_JGE_ONE_SEC);

}
//////////////////////////////////////////////////////////////////////////
//��s�g�L�ɶ�
void WinTime::Update()
{
	if(QueryPerformanceCounter(&mLintEnd) == TRUE)
		mnTime = mLintEnd.QuadPart - mLintBegin.QuadPart;
#ifdef DEF_JGE_DEBUG
	else
	{
		_JGE_DBGLOGLN(L"WinTime::Update QueryPerformanceCounter Fail.");
	}

#endif
}

_JGE_END