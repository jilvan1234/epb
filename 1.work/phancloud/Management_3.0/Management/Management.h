#pragma once
#include <winsock2.h>
#include <windows.h>
#include <iostream>

#include <tchar.h>
#include <fstream>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <string>
#include <vector>


#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;

class MainApp{
	
public:
    MainApp();
    ~MainApp();

    HRESULT Initialize();
	//�]�m�[�t��A�I����icon�A�m���H�Τ���h�}���n�骺�a��

    void RunMessageLoop();//�D�j��
  

private:
	//��l�Ƥ����A�]�mWM_COMMAND���a��
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
        );
	
private:
    HWND m_hwnd;
	HINSTANCE hInstance;	
	static HACCEL hAccel ;//�[�t��
	static ACCEL Accel[3] ;
	
	
	
	static HWND title1;
	static HWND title2;
	static HWND title3;
	static HWND title4;
	static HWND title5;
	static HWND title6;
	static HWND title7;
	static HWND title8;
	static HWND title9;
	static HWND title10;
	static HWND title11;
	static HWND title12;
	static HWND title13;
	static HWND title14;
	static HWND title15;

	static HWND Account;
	static HWND Password;
	static HWND Login;

	static void GetCard();//�d����A�w����
	static void GetAppDlgItemText(HWND a,int b,int c);
	//�n�J�P�_�O�ѳ]�m����samba��{�A�w����
public:
	static HINSTANCE hinst; 
	static unsigned long UsageCount;

};



//#define One ((int)(MainApp::UsageCount > 30000))
#define One ((int)(1))
