#ifndef _epb_win_time_20120622pm0945_
#define _epb_win_time_20120622pm0945_
#include "epb_time.h"
#include <windows.h>
_EPB_BEGIN

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

_EPB_END
#endif