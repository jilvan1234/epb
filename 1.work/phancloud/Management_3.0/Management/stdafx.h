// stdafx.h : �i�b�����Y�ɤ��]�t�зǪ��t�� Include �ɡA
// �άO�g�`�ϥΫo�ܤ��ܧ�
// �M�ױM�� Include �ɮ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �q Windows ���Y�ư����`�ϥΪ�����
// Windows ���Y��:
#include <winsock2.h>
#include <windows.h>

// C RunTime ���Y��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <string>

#include <atlbase.h>
#include <atlconv.h>

#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include "Management.h"
#include "epb_BearLib.h"
#include "IDNumber.h"
#include "GroupUser.h"
#include "Program.h"
#include "Configuation.h"
#include "epb_SendMessageGetString.h"

#include <Shlobj.h>
#include <assert.h>

#pragma   comment(lib,"mpr")

using namespace std;
// TODO: �b���Ѧұz���{���һݭn����L���Y
