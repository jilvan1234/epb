#define VERSION_MAJ 1
#define VERSION_MIN 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

unsigned long find_00dc(unsigned long n,FILE *avif);
char Getjpg_avi(unsigned long file_R_L,unsigned long file_R_H,FILE *avif,char *outfname);

//main function
void main(int argc, char **argv)
{
	FILE *avif;	
	const char src[] = "C:\\Users\\naseem\\Desktop\\vedio\\test0.avi";
	errno_t err;	
	unsigned long file_R_N=0;	//��e���w����m
	unsigned long file_R_L=0;	//�@�ƹϤ��}�l���a��
	unsigned long file_R_H=0;	//�@�ƹϤ��������a��
	
	

	//�q���Ū��jpg�Ϥ� Ū���q�@��"00dc"�D�U�@��"00dc"�������ƾ�
	/*if(argc<2){
		printf("TWO FEW ITEM!\n");
		exit(0);		
	}*/
	// 
 
	if (err = fopen_s(&avif,src, "rb") )	
	{
		printf("Read file Error!\n");
	}
	//
	/*
	avif=fopen(argv[1],"rb");
	if (avif==NULL){
		printf("Read file Error!\n");
	}*/
	
	
	fseek(avif,0,0);	//�����w���V����Y

	file_R_L=find_00dc(0,avif);
	file_R_H=find_00dc(file_R_L,avif);
	printf("This picture is begin at 0x%x,And end at 0x%x.\n",file_R_L,file_R_H);

	//�qavi��󤤴���jpg�Ϥ�
	Getjpg_avi(file_R_L,file_R_H,avif,"out0.jpg");
	
	printf("file_test_1\n");

	file_R_L=file_R_H;
	file_R_H=find_00dc(file_R_L,avif);
	printf("This picture is begin at 0x%x,And end at 0x%x.\n",file_R_L,file_R_H);
	Getjpg_avi(file_R_L,file_R_H,avif,"out1.jpg");
	
	//�������
	fclose(avif);
	system("pause");
}

char Getjpg_avi(unsigned long file_R_L,unsigned long file_R_H,FILE *avif,char *outfname)
{
	char R_tmp[600];
	unsigned long file_R_N=0;	//��e���w����m
	unsigned long i;
	//copy this area and write it to a file
	
	errno_t err;	
	FILE *jpgf;	
	err = fopen_s(&jpgf,outfname,"wb");
	printf(outfname);
	fseek(avif,file_R_L+4,0);	//the start of a picture
	file_R_N+=file_R_L+4;
	//�g�J�Ϲ����Y
	fread(R_tmp,6,1,avif);
	fwrite(R_tmp,6,1,jpgf);
	file_R_N+=6;
	//��JFIF�N��AVI1
	fread(R_tmp,4,1,avif);
	fwrite("JFIF",4,1,jpgf);
	file_R_N+=4;
	//�g�J�Ϲ��ƾ�
	for (i=file_R_N;i<file_R_H-4;i++){
		fread(R_tmp,1,1,avif);fwrite(R_tmp,1,1,jpgf);
	}
	//�������
	fclose(jpgf);

	return 0;
}

//n ��e�������w����m
//��^�X�{�u00dc����m�v
unsigned long find_00dc(unsigned long n,FILE *avif)
{	
	char name[10];
	unsigned long tmp=n;
	fseek(avif,n,0);
	//�M��y00dc�z
	do{
		fread(name,1,1,avif);
		tmp++;
		if (name[0]=='0'){
			fread(name+1,3,1,avif);
			tmp+=3;
			name[4]=0;
			if(strcmp(name,"00dc")==0){
				return tmp;
			}
		}
	} while (1);
}