
#include <winsock2.h>
#include "applay_entry.h"
#include <epb_BoostClass.h>
#include <epb_Container.h>
#include <boost/filesystem.hpp>



bool soft_install_check(std::string softname)
{	
	
	Sleep(100);
	//�d�� soft_install_check("C:\\c++");  �|�P�_��Ӹ��|
	int bb = epb::Container::a_multimap::AppCount.size();
	bool abc = false;

	//MessageBox(NULL, wTmp.c_str() ,"�o�O�o�O�o�O�o�O�o�O�o�O�o�O�o�O�o�O�o�O�o�O�o�O�o�O�o�O�P�_local�O�_�s�b���a�� GG2 ���ӭn�L�⦸" , MB_OK);
	
	for(int i=0 ; i < bb ; i++)
	{	
		MessageBoxA(NULL, "ccccccccccccc" ,epb::Container::a_multimap::AppCount[i].second.c_str() , MB_OK);
		if(softname == epb::Container::a_multimap::AppCount[i].second.c_str())		
		{							
		//	MessageBox(NULL, softname.c_str() ,"�n����|�C�����o�ӳn��ؿ�" , MB_OK);
			boost::filesystem::path p( softname.c_str() );
			if( exists( p ) && is_directory( p ) )
			{				
		//		MessageBox(NULL, softname.c_str() ,"local�����ؿ�" , MB_OK);	
				abc = true;
			}
			else
			{
				MessageBox(NULL, softname.c_str() ,"local�S�����ؿ�" , MB_OK);	
			}		
		}
		else
		{				
			//MessageBox(NULL, softname.c_str() ,"�S���o�ӳn��ؿ�" , MB_OK);				
		}
	}

	return abc;
}
bool reg_Check()
{
	return true;
}

bool network_check()
{
	//�����s���T�{
	
		if(pinger::network_check_2 == true)
		{
			if(pinger::network_check == true)
			{
				return true;
			}
		}
		else
		{
			return false;
		}	
	//return true;
}

std::string softpath_get (std::string softname )
{
	//�ɮ׸��|�T�{
	//���osmba���n���Ƨ����|
	std::string hng;
		hng = "P:\\";		
		hng += softname.c_str();
		softname = hng;
		//MessageBox(NULL, softname.c_str() ,"Error" , MB_OK);
		return softname;
}
void MSG_show(std::string Msg)
{
	MessageBox(NULL, Msg.c_str() ,"Phancloud" , MB_OK);
	//�T����X
}