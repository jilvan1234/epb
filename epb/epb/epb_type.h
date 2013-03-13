#ifndef _epb_type_20120622pm0945_
#define _epb_type_20120622pm0945_

#include  "epb_define.h"
// �򥻸�������w�q
namespace EPB
{
	typedef signed	 __int8		sint8;
	typedef unsigned __int8		uint8;
	typedef	char				char8;

	typedef signed	 __int16	sint16;
	typedef unsigned __int16	uint16;
	typedef			 wchar_t	char16;


	typedef signed __int32		sint32;
	typedef unsigned __int32	uint32;

	typedef signed __int64		sint64;
	typedef unsigned __int64	uint64;
	
	typedef bool				boole;
	typedef signed	int			sint;
	typedef unsigned	int		uint;

#ifdef DEF_EPB_UNICODE
	typedef char16		tchar;
#else
	typedef char8		tchar;
#endif

	typedef unsigned __int32	errcode;
};

#endif