#ifndef _FRAME_DEFINE_H
#define _FRAME_DEFINE_H

#include <iostream>
#include <string>
#include  <sstream> 
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define PixelsNum 27648 //�C�@���]�t�������Ӽ�
#define FramesNum 80 //���W�]�t���`����

string VideoName = "kylie"; //���W���W�١A��bdebug��󧨤��C



class Frame{

public:
	Frame(){}
	Frame(int i); //�c�y���
	~Frame() { delete [] L; delete [] A;} //�R�c���

	Frame & operator =(const Frame &fr);

	double Distance(const Frame &f);

	void Print(){

		for(int k=0;k<3*PixelsNum;k++)
		cout<<L[k]<<endl;
	}


private:
	double *L;//�C�ӹ�����L��.�ΰ�ʺA���t���s
	double *A;//HSV���@���ڶq��.A=H+S+V
	double first;//����HSV�@���ڶq�ƫ᪺�@���Z
	double second;//����HSV�@���ڶq�ƫ᪺�G���Z
	double third;//����HSV�@���ڶq�ƫ᪺�T���Z
};
Frame & Frame::operator =(const Frame &fr)
{
	if(this == &fr)
		return *this;

	L = new double[3*PixelsNum];
	A = new double[PixelsNum]; 
	for(int i=0;i<3*PixelsNum;i++)
		L[i] = fr.L[i];
	for(int i=0; i<PixelsNum; i++)
		A[i] = fr.A[i];

	first = fr.first;
	second = fr.second;
	third = fr.third;
		

	return *this;
}

Frame::Frame(int i){ //�q�������Ū���ƾ�,��l�� (����Ū���M�r�Ŧ�ާ@�A�d�I)
	

	string filename;
	stringstream ss;
	ss<<i;
	ss>>filename;
	
	string filenametxt=VideoName+"_80_unitary/("+filename+")_unitary.txt";
	fstream infile;

	cout<<filenametxt<<endl;

	infile.open( filenametxt.c_str() ,ios::in);
	if(!infile){
		std::cout<<"Can not open file!\n";
		abort();
	}

	L = new double[3*PixelsNum]; //��new�b��̰ʺA���t���s
	A = new double[PixelsNum]; 

	char s[20];
	//�N��󤤰O�����C�@�ӹ�����rgb�O����Ʋդ��A�A���B�z�C
	for(int j=0; j<3*PixelsNum; j++){
		infile.getline( s, sizeof(s) );
		L[j] = atof(s);
	}

	infile.close();


	//�N�C�ӹ�����rgb�k�@�ơA�ϥL�̦b[0�A1]���C�åB�Nrgb�নhsv�C��HSV���@���ڶq�ơA�C�@�ӹ���HSV�@���ڶq�ƪ����G�s�J�Ʋ�A
	i = 0;
	for(int j=0; j<3*PixelsNum; j+=3){
		double tempmax3, tempmin3;
		tempmax3 = tempmin3 = L[j];
		for(int k=1; k<3; k++){
			if( L[j+k] > tempmax3 ) tempmax3 = L[j+k];//�o��@�ӹ���rgb�T�̪��̤j�ȡA�O��tempmax3
			if( L[j+k] < tempmin3 ) tempmin3 = L[j+k];//�o��@�ӹ���rgb�T�̪��̤p�ȡA�O��tempmin3
		}
	//	cout<<"tempmax3 ="<<tempmax3<<endl;
	//	cout<<"tempmin3 ="<<tempmin3<<endl;
		if( tempmax3 > 1 ){ //�p�G�o�ӳ̤j�Ȥ�@�j�A�h�N��������rgb�k�@�ơC
			L[j] /= tempmax3;
			L[j+1] /= tempmax3;
			L[j+2] /= tempmax3;
		}

		double r, g, b;
		double h, s, v;
		r = L[j];
		g = L[j+1];
		b = L[j+2];

	//	cout<<"r="<<r<<endl;
	//	cout<<"g="<<g<<endl;
	//	cout<<"b="<<b<<endl;

		
		double delta = tempmax3 - tempmin3; 

		if( delta != 0 ){//���ɫDrgb�T�̬۵��F���H���w�q�A�������C��F���M��S�]���w�q
		//	if R = max, H = (G-B)/(max-min) 
		//	if G = max, H = 2 + (B-R)/(max-min) 
		//	if B = max, H = 4 + (R-G)/(max-min) 
		//	H = H * 60 
		//	if H < 0, H = H + 360 

			if( r == tempmax3 ) h = (g - b)/delta;
			if( g == tempmax3 ) h = 2 + (b - r)/delta;
			if( b == tempmax3 ) h = 4 + (r - g)/delta;

			h *= 60;
			if( h < 0 ) h += 360;

			h /= 360;//h�k�@�Ʀ�[0,1]�A�Ps,v�ۦP
			s = delta / tempmax3;
			v = tempmax3;
		}
		else{//����rgb�T�̬۵��A�S����ץu���ǫסF���H�L�w�q
			h = -1;//h�L�w�q
			if(tempmax3 ==0){//����r=g=b=0 �¦�
				s = -1;//�¦� S�L�w�q
				v = tempmax3;
			}
			else{//����r=g=b!=0 �Ǧ�Υզ�
				s = 0;
				v = tempmax3;
			}
		}
		
	//	//S=(max-min)/max 
	//	if( tempmax3 != 0 ) s = delta/tempmax3;
	//	else{ //���ɹ����I��rgb���O0
	//		s = 0;
	//		v = -1;//v�L�w�q
	//		h = -1;//h�L�w�q
	//	}

		

	

		L[j] = h; 
		L[j+1] = s;
		L[j+2] = v;
		
	//	cout<<"h = "<<h<<endl;
	//	cout<<"s = "<<s<<endl;
	//	cout<<"v = "<<v<<endl;

		if( h<0 ) h=0;
		if( s<0 ) s=0;
		if( v<0 ) v=0;	

		A[i] = h + s + v;  //�p�GHSV���w�q�N��L�̤@���ڶq�ơC�S�w�q�����[�C
		
	//	cout<<"A["<<i<<"] = "<<A[i]<<endl;
		i++;

	}

//	for(int i=0; i<PixelsNum; i++)
//		cout<<"A["<<i<<"] = "<<A[i]<<endl;
//cout<<"A[29999] = "<<A[29999]<<endl;
//cout<<"A[30000] = "<<A[30000]<<endl;
//cout<<"A[30001] = "<<A[30001]<<endl;
	double temp = 0;
	for(int j=0; j<PixelsNum; j++)
		temp += A[j];
	cout<<"temp = "<<temp<<endl; 
	first = temp/PixelsNum;

	temp = 0;
	for(int j=0; j<PixelsNum; j++ )
		temp += pow( (A[j] - first) , 2);
//	cout<<"temp_second = "<<temp<<endl;
//	cout<<"temp_second/PixelsNum ="<<temp/PixelsNum<<endl;
	second = pow( (temp / PixelsNum) , 0.5);

	temp = 0;
	for(int j=0; j<PixelsNum; j++)
		temp += pow( fabs(A[j] - first) , 3);
	third = pow( (temp / PixelsNum) , 0.333333);

	
    cout<<"first = "<<first<<endl;
		cout<<"second = "<<second<<endl;
		cout<<"third = "<<third<<endl;



}


double Frame::Distance(const Frame &f){
//	double distance=0;
//
//	
//	for(int i=0;i<3*PixelsNum;i+=3)
//		distance += pow( ( pow((L[i]-f.L[i]),2) + pow((L[i+1]-f.L[i+1]),2) + pow((L[i+2]-f.L[i+2]),2) ), 0.5);
//	return distance;

	double distance;
	double sigma = 0;//�������Y��

//	cout<<"first ="<<first<<endl;
//	cout<<"f.first ="<<f.first<<endl;

	for(int j=0; j<PixelsNum; j++){
		sigma += (A[j] - first) * (f.A[j] - f.first);
//		cout<<"A["<<j<<"] = "<<A[j]<<endl;
//		cout<<"f.A["<<j<<"] = "<<f.A[j]<<endl;
//		cout<<"() = "<<A[j] - first<<endl;
//		cout<<"(f) ="<<f.A[j] - f.first<<endl;
	}
	sigma /= PixelsNum *second * f.second ;
//	cout<<"second = "<<second<<endl;
//	cout<<"f.second = "<<f.second<<endl;
//	cout<<"/() = "<<PixelsNum * second * f.second<<endl;

//	cout<<"sigma ="<<sigma<<endl;

//	distance = (1-sigma) * pow( ( ( pow( (first - f.first), 2 ) + pow( (second - f.second), 2 ) + pow( (third - f.third), 2) ) / 3 ) , 0.5); 
//  cout<<"distance = "<<distance<<endl;
//	distance = 1- (sigma * (2*first*f.first/(pow(first,2)+pow(f.first,2))) * (2*second*f.second/(pow(second,2)+pow(f.second,2)))* (2*third*f.third/(pow(third,2)+pow(f.third,2))));//* (pow(pow((first - f.first),2),0.5) +pow(pow((second - f.second),2),0.5)  );
//	distance = sigma*fabs(first - f.first)/ (first+f.first) * fabs(second-f.second)/(second+f.second) ;
//	distance =  ( fabs( first - f.first ) + fabs( second - f.second ) + fabs(third-f.third)) ; 
	distance = 1 - sigma * min(fabs(first/f.first),fabs(f.first/first)) * min(fabs(second/f.second),fabs(f.second/second))*min(fabs(third/f.third),fabs(f.third/third));
	return distance; 



}
		
	
#endif


 














