#include <windows.h>

class GroupEventer{
public:
	
static void shellgrouoppget();	//�q���A�ݨ��^�s�զC��
static void shelluserpget(std::string wstr);	//�q���A�ݨ��^�ϥΪ̦C��A�ѼƤ@��J�s��
static void GrouopAdd(std::string wstr);//�s�W�s��
static void GrouopDel(std::string wstr);//�R���s��
static void UserAdd(std::string wstr);//�s�W�ϥΪ�
static void UserDel(std::string wstr);//�R���ϥΪ�
static void GroupUserUpdate();//�ǵ����A��update�A�w����
static void UserMod(std::string wstr);	//���ϥΪ̸s��
static std::string GroupName;

static int GroupEventer::split(const std::string& str, std::vector<std::string>& ret_ );	//�H"/n"���Ϲj���ά�����A��J�e��
static int bhja1(const std::string& str, std::vector<std::string>& ret_ );	//�H","���Ϲj���ά�����A��J�e��

static HWND hGroupList		;
static HWND hGroupText		;
static HWND hUserList		;
static HWND hUserText		;
static HWND hGroupEditText	;
static HWND hUserEditText	;
static HWND hUserModText	;
static HWND hGroupModText	;

  static int GroupEventNumber;
  static int GroupNumberID;
};

LRESULT CALLBACK DialogProcGROUPUSER_TITLE(HWND, UINT, WPARAM, LPARAM); //loadimginformation
	//��l�Ƥ����A�]�mWM_COMMAND���a��
void RegisterDialogGROUPUSER_TITLE(HWND);
//�m���Υu��}�@�ӵ�����count�]�m
