#include "jge_file_read.h"
#include <io.h>
_JGE_BEGIN
FileRead::FileRead() : mpFile(0)
{

}
//////////////////////////////////////////////////////////////////////////
FileRead::~FileRead()
{

}
//////////////////////////////////////////////////////////////////////////
errcode FileRead::Open(const char8* pszPath)
{
	//�}���ɮ�
	mpFile=fopen(pszPath,"r+b");
	
	if(mpFile!=NULL)
	{		
		return DEF_JGE_OK;
	}
	

	return DEF_JGE_FILE_OPEN_FAIL;
}
//////////////////////////////////////////////////////////////////////////
void FileRead::Close()
{
	if(mpFile)
	{
		close(fileno(mpFile));
		mpFile = 0;
	}		
}
//////////////////////////////////////////////////////////////////////////

errcode FileRead::Read(void* pBuffer,uint nBufferSize,uint* pnReadSize )
{
#define _set_read_size(size) if(pnReadSize) *pnReadSize = size;
	if(feof(mpFile))
	{
		//�ɮפw�쵲��
		_set_read_size(0);
		return DEF_JGE_END_OF_FILE;
	}
	size_t stRealReadSize=fread(pBuffer,1,nBufferSize,mpFile);
	_set_read_size(stRealReadSize);
	if(stRealReadSize==nBufferSize)
	{	
		//Ū�����\
		
		return DEF_JGE_OK;
	}

	else if(stRealReadSize==0)
	{
		//Ū������
		
		if(feof(mpFile))
		{
			//�ɮפw�쵲��
			return DEF_JGE_END_OF_FILE;
		}
		
		return DEF_JGE_FILE_READ_ERROR;
	}
	else if (stRealReadSize < nBufferSize)
	{
		//�p�G�u��Ū�쪺�j�p�p��쥻���j�p
		//�N���ɮפw�쵲��
		//Ū�����\,���O�ä��O���㪺�w�Ĥj�p\0";
		return DEF_JGE_OK;
	}
	return DEF_JGE_FILE_READ_ERROR;
}
//////////////////////////////////////////////////////////////////////////
boole FileRead::IsEof() const
{
	if(mpFile)
		return feof(mpFile) == 0;
	return false;
}
//////////////////////////////////////////////////////////////////////////
uint FileRead::GetSize() 
{
	if(mpFile)
	{
		return ftell(mpFile);
	}
	return 0;
	
}
_JGE_END