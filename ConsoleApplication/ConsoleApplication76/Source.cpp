
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
void main()
{	   	
    TCHAR chBuf[512];
    ZeroMemory(chBuf,512);     
    if (GetModuleFileName(NULL,chBuf,512))  //������O��eEXE�Ҧb���|
    {
		wprintf(chBuf);
		printf("\n");
    }

	system("pause");

}