#include <windows.h>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

class ProgramEventer{
private:
	
public:
	static int bb(const std::string& str, std::vector<std::string>& ret_);
		//�H"/n"���Ϲj���ά�����A��J�e��
	static int hh(const std::string& str, std::vector<std::string>& ret_);
		//�H","���Ϲj���ά�����A��J�e��
	static int ProgramEventNumber;
	static int ProgramNumberID;
	static int ProgramProgramNumberID;
	static std::string ProgramGroupName;
	static std::string GetAPPNameAPPON;
	//static int GetCountSoftware;
	static std::string GetAPPName;
	static std::string GetAPPPathName;
	static int rg;

	

static BOOL InitListViewColumns(HWND );
//ListView�]�m
static void SoftwareView(std::string);
//GetSoftwareName
static void SetView(std::string,LVITEM,int);
	//ListView
static void ProgramGetGroupList();
//GroupList
static void SoftwareTick(std::string,std::string,std::string);
	//�n��Ŀ�
static void APPDel(std::string);
	//�n��R��
static void SoftwarePath(std::string a,std::string b);
	//GetSoftwarePathName
static void AppendSpace();
//�ƻs�ɮת����j
static void CopyFiles( const bf::path& from, const boost::filesystem::path& to );
	//�ƻs�ɮ�
static void GetFiles( const boost::filesystem::path& from, const boost::filesystem::path& to );
	//���o�ɮ�
static std::string GetFolderName();
	//���o��Ƨ��W��

static HWND hProgramView				;
static HWND hProgramGroupList			;
static HWND hProgramGroupText			;
static HWND hProgramGroupProgramList	;
static HWND hProgramGroupProgramUseText	;
static HWND hProgramGroupProgramMaxText	;

static HWND hProgramGroupProgramText	;
static HWND hProgramGroupProgramPathText;
static HWND hProgramSoftwareEditText	;
static HWND hProgramSoftwarehProgBar	;
static HWND hProgramSoftwarePathText	;
static HWND hProgramSoftwareAppMaxText	;



};

void RegisterDialogPROGRAM_TITLE(HWND);
	//��l�Ƥ����A�]�mWM_COMMAND���a��
LRESULT CALLBACK DialogProcPROGRAM_TITLE(HWND, UINT, WPARAM, LPARAM); //loadimginformation
	//�m���Υu��}�@�ӵ�����count�]�m