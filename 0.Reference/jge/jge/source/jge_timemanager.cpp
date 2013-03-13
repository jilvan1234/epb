#include "jge_timemanager.h"
#include "jge_debug.h"
//////////////////////////////////////////////////////////////////////////
_JGE_BEGIN

TimeManager::TimeManager(ITime* pTime) :mpTime(pTime)
{

}
//////////////////////////////////////////////////////////////////////////
TimeManager::~TimeManager()
{

}
//////////////////////////////////////////////////////////////////////////
void TimeManager::Register(TimerPtr pTimer,TimerStop bStop )
{
	uint64 nTime;
	mpTime->Get(nTime);

	TimerDataPtr ptd = new TimerData;
	ptd->pTimer = pTimer;
	ptd->nLastTime = nTime + pTimer->GetInterval();
	ptd->bStop = bStop;

	mTimeDatas.push_back(ptd);
	
	
}
//////////////////////////////////////////////////////////////////////////
void TimeManager::Unregister(TimerPtr pTimer)
{	
	for(TimerDataSet::iterator it = mTimeDatas.begin(); 
		it != mTimeDatas.end() ;
		++it)
	{
		TimerDataPtr ptd = *it;
		if(ptd->pTimer != pTimer)
			continue;
		
		mTimeDatas.erase(it);
		delete ptd;
		break;
	}
	
}

//////////////////////////////////////////////////////////////////////////

void TimeManager::Update()
{	
	/*
	��s�ɶ�����
	�v�@�߬dtimer�O�_���?
	�N�w�g��ɪ�timer�����ܰ}�C
	�b�@���Τ@�e�Xontime�ƥ�
	*/
	mpTime->Update();

	TimerDataSet vptd;

	for(TimerDataSet::iterator it = mTimeDatas.begin(); 
		it != mTimeDatas.end() ;
		++it)
	{
		TimerDataPtr ptd = *it;
		if(_IsOnTime(ptd) == false)
			continue;		
		//else		
		mpTime->Get(ptd->nLastTime);			
		ptd->nLastTime += ptd->pTimer->GetInterval() ;
#ifdef DEF_JGE_DEBUG

		/************************************************************************/
		/*	�߬d ontime �ɶ��O�_�j�� �w����ontime�ɶ�
		*/
		/************************************************************************/
		uint64 preTime = ptd->nLastTime - ptd->pTimer->GetInterval();
		uint64 curTime ;
		mpTime->Get(curTime);
		if(preTime > curTime)
		{
			_JGE_DBGLOGLN(L"TimeManager::Update �����~��Ontime�]�w! curTime=%I64d preTime=%I64d Interval=%I64d",curTime,preTime,ptd->pTimer->GetInterval());
			int i=0;
		}
#endif 


		vptd.push_back(ptd);
		
	}

	for(TimerDataSet::iterator it = vptd.begin(); 
		it != vptd.end() ;
		++it)
	{
		TimerDataPtr ptd = *it;
		ptd->bStop = ptd->pTimer->OnTime();	

	}

	vptd.clear();
}

//////////////////////////////////////////////////////////////////////////

boole TimeManager::_IsOnTime(TimerDataPtr ptd)
{
	if(ptd->bStop == false)
	{
		uint64 nCurTime;
		mpTime->Get(nCurTime);
#ifdef DEF_JGE_DEBUG
		{
			/************************************************************************/
			/*	�߬d ontime �ɶ��O�_�j�� �w����ontime�ɶ�
			*/
			/************************************************************************/
			uint64 preTime = ptd->nLastTime - ptd->pTimer->GetInterval();
			uint64 curTime ;
			mpTime->Get(curTime);
			if(preTime > curTime)
			{
				_JGE_DBGLOGLN(L"TimeManager::_IsOnTime �����~��Ontime�]�w! curTime=%I64d preTime=%I64d Interval=%I64d",curTime,preTime,ptd->pTimer->GetInterval());
				int i=0;
			}
		}
		
#endif 
		return (nCurTime > ptd->nLastTime) ;
				
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
const ITime* TimeManager::GetTime() const 
{
	return mpTime;
}

_JGE_END