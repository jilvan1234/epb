#ifndef _jge_win_time_20080205pm0108_
#define _jge_win_time_20080205pm0108_
#include "jge_time.h"
#include <windows.h>
_JGE_BEGIN

class WinTime : public ITime
{
	static LARGE_INTEGER	mLintTC;		//�C��p�Ʀ���

	LARGE_INTEGER			mLintBegin;		//�}�l�ֿn����
	LARGE_INTEGER			mLintEnd;		//�����ֿn����
	uint64					mnTime;			//�g�L���ɶ�
			
public:
					WinTime		();
					~WinTime	();

	static	boole	fnInitialize();
			void	SetZero		() ;
			void	Get			(TimeData& timeData) const ;
			void	Get			(uint64& nTime)	const ;
			void	Update		();
};

_JGE_END
#endif