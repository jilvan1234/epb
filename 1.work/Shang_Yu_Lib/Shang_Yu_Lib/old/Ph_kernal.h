#include "applay_entry.h"

struct CFG_temp_File
{
	int chacknum;		//for system soft
	char resystem;		//resart system flag
	std::string config;

	int chacknum2;		//for system soft
}PHANCLOUD_rest_crtl;

/*
#define sername "PRMonitor"
#define sysfilename "hellodrive.sys"
#define serentry "\\\\.\\PRMONITOR"
*/
 //REG�s����|
#define sername "PhanCloud"
#define sysfilename "hellodrive.sys"
#define serentry "\\\\.\\PhanCloud"


#define CFG_ServerIP	 "\\\\192.168.1.51" //��W
#define CFG_InstalledDir "C:\\Phancloud"
#define	CFG_FilesysSite	 "project\\"
#define CFG_FileRegSite  "PhanCloud\\Reg"







#define MSG_error_loadsys_false "�֤߼Ҳո��J����"
#define MSG_loadsys_fin			"�֤߼Ҳո��J�פF"
#define MSG_loadsys_turn		"�֤߼Ҳո��J���\"
#define MSG_loading				"Loading..."


void RegFile_SET(std::string softname);
void R3_load();  //cc�V�c
char CFG_FileSysSite[14]=  "PhanCloud\\Sys";
char strage1[] = "xcopy /H/E/Y/C ";
