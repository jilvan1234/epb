#include <WinSock2.h>
#ifndef _WINDOWS_
#include <windows.h>
#endif
#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_STDLIB
#include <stdlib.h>
#endif
#ifndef _STRING_
#include <string>
#endif
#ifndef _INC_IO
#include <io.h>
#endif

#define _applay_entry_H
#include "version.h"
#include "DeBug_Tools\command_func.h"
#include "computer_Info\PH_Get_Info_fun.h" //���J�t�α���Ҳ�
#include "win�v������\permission_crl_fun.h" //�v������
#include "pross_&_mem\pross_mem_fun.h"     //������P�O���骺����
#include "reg_crl\Registr_Filter_fun.h"    //�n�����R



#ifdef offlin_hive
#include "hivetst\offreg.h"
#endif

bool soft_install_check(std::string softname);
bool reg_Check();

void all_work(std::string softname,std::string chack_catah);
void ALL_run();
void S_all_work2(std::string softname);
bool load_reg_tree();
void strt_set();
void ClearBUFF();

//�Ȥ�ݶ}�l
bool network_check();
void MSG_show(std::string Msg);

std::string softpath_get (std::string softname );
//���μh�T�����X

int soft_list(std::string list[] ,int item_num);

typedef struct Test_intput_msg
{
	std::string a1;
	std::string a2;

}Test_intput_msg;

typedef struct test_output_msg
{
	std::string o1;
}Test_output_msg;

Test_output_msg Debug_item(Test_intput_msg a);



#ifdef offlin_hive
void reg_test_mon(HKEY hkey,char command[2]);
DWORD Orc_tst();
LONG reg_save_and_restore_tst(HKEY hKey,char crl_c);
#endif

//hive control
BOOLEAN load_hive(HKEY key,LPCTSTR subkey,LPCTSTR filename);
BOOLEAN hive_unload(HKEY key,LPCTSTR subkey);
BOOLEAN save_hive(HKEY key,LPCTSTR subkey,LPCTSTR filename);



void dChangTextColor(WORD color, char *output);

VOID bitmap_test();
VOID gdi_tst ();
VOID Get_Bmpinfo();
int N_TTlist_ll_ppp();
void CloseSrv();






bool machine_check();

typedef struct {
  char mark[16];    // WDAPIDISK
} WDAPISCSI_DISK_GET_INFO_OUTPUT ;

#define IOCTL_WDAPISCSI_DISK_GET_INFO       CTL_CODE(0x9000, 0x0402, METHOD_BUFFERED, FILE_ANY_ACCESS)

//======================================================================================================================
// FUNCTION: OpenDevice( IN LPCTSTR, HANDLE *)
// PURPOSE: Opens the device and returns a handle if desired.
//======================================================================================================================
BOOL OpenDevice( IN LPCTSTR DriverName, HANDLE * lphDevice , int async);


bool IsWdapiscsiVirtualDisk(char drive_letter );

