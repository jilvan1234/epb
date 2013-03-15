#ifndef _HEAP_DEFINE_H  
#define _HEAP_DEFINE_H

//#include "Heap.h"
#include "Frame_Define.h"
//#include "math.h"
//#include "fstream"


//#include "stdlib.h"
//#include "iostream"

using namespace std;



struct Heap_Node{
	int id;
	
	int taoleft;
	int taoright;
	int tao;

	double Eleft;
	double Eright;
	double deltaE;

};//�w�q��`�I

typedef struct Heap_Node Node;


class MinHeap{

public:

	MinHeap (int n, int sz, Frame *frame ); //�a���諸��l�Ȫ��c�y���
	
	~MinHeap () { delete [] node; } //�諸�R�c���

	void BuildHeap (); //�إ̤߳p��
	double DeleteMin ( Node & x, Frame *frame); //�R���̤p�襤���̤p�����A�Y�ﳻ�����C�åB���Ӻ�k�ĤG�B�T�B�ק�`�I�������ݩʡC���ذ�



	int IsEmpty () const {return CurrentSize==0;} //�P��Ż�H
	int IsFull () {return CurrentSize==MaxSize;} //�P�ﺡ��H
	bool IsTheIdAlive(int i);//�P�_��id���լO�_�٦b�襤
	int FrameIdToNodeIndex(int i);//�q�ժ�Id��Node������
	int FindNodeNeighbourId(Node & x, int IdOffset);//�M��Q�R�����ժ��۾F�ժ�Id

	int GetCurrentSize(){return CurrentSize;}//Ū���諸��e�`�I��
	void ShowCurrentNode(){//��X�諸��e�`�I�H��

		int sortflag = 1; //�H���䷩�b���W�y������m������r�Ƨ�
		Node temp; 

		for(int i=1; (i<CurrentSize)&&(sortflag==1); i++){
			sortflag = 0;
			for(int j=1; j<=CurrentSize-i; j++){
		//		sortflag = 0;
				if(node[j].id > node[j+1].id){
					temp = node[j]; 
					node[j] = node[j+1];
					node[j+1] = temp;

					sortflag = 1;
				}
			}

		}


		fstream outfile; //�N���䷩��������G�g�J���

		outfile.open("result.txt", ios::out);
		if(! outfile){
			cout<< "result.txt can not open.\n";
			abort();
		}
		
		outfile<<VideoName<<endl; //���W�W
        outfile<<FramesNum<<endl; //�����`��
		outfile<<CurrentSize<<endl; //���䷩���ƶq 

		for(int i=1; i<=CurrentSize; i++){
			cout<<"node["<<i<<"].id="<<node[i].id<<" , taoright="<<node[i].taoright<<" , taoleft="<<node[i].taoleft<<endl;
			
			outfile<<node[i].taoleft<<endl;
			outfile<<node[i].id<<endl;
			outfile<<node[i].taoright<<endl;

		}

		outfile.close();
	}
	 
	int GetNode_Id(int index) { return node[index].id; }
	int GetNode_Taoleft(int index) { return node[index].taoleft; }
	int GetNode_Taoright(int index) { return node[index].taoright; }


	void Clear () {CurrentSize=0;} //�m��šA�襤�S���@�Ӥ���


private:

	Node * node; //�O�s�諸�Ʋ�
	int CurrentSize; //���e���`�I�Ӽ�
	int MaxSize; //�Ʋեi�H�O�s�����I���̤j�ƥ�
	
	void SiftDown (int j);

};

MinHeap::MinHeap(int n, int sz, Frame *frame ){

	
	CurrentSize = n;
	MaxSize = sz;
	node = new Node[sz+1];
	int i;
	for( i=1; i<=n; i++){

		node[i].id = i;
		node[i].Eleft = node[i].Eright = 0;
		node[i].taoleft = i;
		node[i].taoright = i+1;

	
		
		if( i==1 ){
			node[i].tao = 1;
	//		node[i].taoleft = 1;
	//		node[i].taoright = 2;
		}
		if( i==n ){
			node[i].tao = n;
	//		node[i].taoright = n;
	//		node[i].taoleft = n;
		}
		
		if(! (i==1||i==n) ){

	//		node[i].taoleft = i;
	//		node[i].taoright = i+1;

			if( frame[i].Distance(frame[i-1]) <= frame[i].Distance(frame[i+1]) )
				node[i].tao = i;
			else
				node[i].tao = i+1;
		}

	
		if( i==1 )
			node[i].deltaE = pow(frame[1].Distance(frame[2]), 2);
		else if( i==FramesNum )
			node[i].deltaE = pow(frame[FramesNum].Distance(frame[FramesNum-1]), 2);
		else 
			node[i].deltaE = min( pow(frame[i].Distance(frame[i+1]), 2) , pow(frame[i].Distance(frame[i-1]), 2) );



		
//		switch(i){
//			case 1 : node[i].deltaE = pow(frame[1].Distance(frame[2]),2);
//			case FramesNum : node[i].deltaE = pow(frame[FramesNum].Distance(frame[FramesNum-1]),2);
//			default: node[i].deltaE = min( pow(frame[i].Distance(frame[i+1]),2), pow(frame[i].Distance(frame[i-1]),2) );
//		}
//		cout<<node[i].deltaE<<endl;

	}
	    
	BuildHeap();

	

	for(i=1; i<=n; i++){
		cout<<"id="<<node[i].id<<endl;
		cout<<"deltaE="<<node[i].deltaE<<endl;
	cout<<"tao="<<node[i].tao<<endl;
	}
		

}//����`�I��l�ƩM�إ̤߳p��

void MinHeap::SiftDown(int j){
	
	int MinSon;//�Ω�O���p��l���U�Цa�}
	node[0] = node[j];

	
	for(; j*2<=CurrentSize; j=MinSon){
		MinSon = 2*j;
		if( MinSon != CurrentSize && node[MinSon+1].deltaE < node[MinSon].deltaE ) MinSon++; 
		if( node[MinSon].deltaE < node[0].deltaE )
			node[j] = node[MinSon];

		else break;
	}
	node[j] = node[0];

}

void MinHeap::BuildHeap(){
	for(int j=CurrentSize/2; j>0; j--)
		SiftDown(j);

//	cout<<"The current node[1]'s id is "<<node[1].id<<endl;
}

bool MinHeap::IsTheIdAlive(int i){
	int j;
	for( j=1;j<=CurrentSize;j++){
		if(node[j].id==i)
		break;
	}

	if(j<=CurrentSize) return true;
	else return false;
}
int MinHeap::FrameIdToNodeIndex(int i){
	int j;
	for( j=1;j<=CurrentSize;j++){
		if(node[j].id==i)
		break;
	}
	return j;
}

int MinHeap::FindNodeNeighbourId(Node & x, int IdOffset){
	if(IdOffset>0){//�q��e�զV����٦b�襤��IdOffset����
		int alives=0;
		int id;
		for( id=x.id+1; id<=FramesNum; id++){
			if(IsTheIdAlive(id)) alives++;
			if(alives == IdOffset) break;
		}
		if(id<=FramesNum) return id;//�T����
		else return -1;//�S���A��^�@�ӫD�k���
	}
	else{//�q��e�զV�e���٦b�襤��IdOffset����
		int alives=0;
		int id;
		for( id=x.id-1; id>0; id--){
			if(IsTheIdAlive(id)) alives++;
			if(alives == (0-IdOffset)) break;
		}
		if(id>0) return id;//�T����
		else return -1;//�S���A��^�@�ӫD�k���
	}
}

	
double MinHeap::DeleteMin( Node & x, Frame *frame){

	
	x = node[1];//node[1]����e�諸�ﳻ�`�I�A�Y�̤p�`�I
	node[1] = node[CurrentSize--];

	SiftDown(1);//���ذ�


	cout<<"Delete "<<x.id<<" frame."<<endl;
	cout<<"Current deltaE = "<<x.deltaE<<endl;
	
	
	int IdKFPOne, IdKFNOne, IdKFPTwo, IdKFNTwo;
	int IndexPOne, IndexNOne, IndexPTwo, IndexNTwo; 
	//���P�Q�R������e��Id�e��ۮt1�B2���襤�{�s����ժ�Id�ΥL�̦b�襤���`�I��Index
	IdKFPOne = FindNodeNeighbourId(x, 1);
	IdKFNOne = FindNodeNeighbourId(x, -1);
	IdKFPTwo = FindNodeNeighbourId(x, 2);
	IdKFNTwo = FindNodeNeighbourId(x, -2);

	if(IdKFPOne!=-1) IndexPOne = FrameIdToNodeIndex(IdKFPOne);
	if(IdKFNOne!=-1) IndexNOne = FrameIdToNodeIndex(IdKFNOne);
	if(IdKFPTwo!=-1) IndexPTwo = FrameIdToNodeIndex(IdKFPTwo);
	if(IdKFNTwo!=-1) IndexNTwo = FrameIdToNodeIndex(IdKFNTwo);


	//���Ӻ�k�ĤG�B�ק�`�I���ݩʭ�

	if(IdKFNOne==-1){//�Q�R������e�ե��䤣�s�b���Q�R��������աA�h�u�B�z��e�եk��۾F�����
		
		node[IndexPOne].taoleft = 1;
		
		double s=0;
		for(int i=1; i<IdKFPOne; i++)
			s += pow(frame[i].Distance(frame[IdKFPOne]), 2);
		node[IndexPOne].Eleft = s ;
	}

	if(IdKFPOne==-1){//�Q�R������e�եk�䤣�s�b���Q�R��������աA�h�u�B�z��e�ե���۾F�����
		
		node[IndexNOne].taoright = FramesNum;

		double s=0;
		for(int i=FramesNum; i>IdKFNOne; i--)
			s += pow(frame[i].Distance(frame[IdKFNOne]), 2);
		node[IndexNOne].Eright = s;
	}

	if(!(IdKFPOne==-1 || IdKFNOne==-1)){//�Q�R������e�ե��k���ܤ֦��@�ӥ��Q�R��������աA�B�z���䪺���R���������
		
		node[IndexNOne].taoright = x.tao;

		double s=0;
		for(int i=IdKFNOne+1; i<x.tao; i++)
			s += pow(frame[i].Distance(frame[IdKFNOne]), 2);
		node[IndexNOne].Eright = s;

		
		node[IndexPOne].taoleft = x.tao;

		s=0;
		for(int i=x.tao; i<IdKFPOne; i++)
			s += pow(frame[i].Distance(frame[IdKFPOne]), 2);
		node[IdKFPOne].Eleft = s;
	}

	
	
	//���Ӻ�k�ĤT�B�ק�`�I���ݩʭ�
	
	int Mmin;
	double FirstResult; 
	double FirstUp;
	double FirstDown;

//	int aForDeltaE;
//	double Prior;
//	double Posterior;

	if(IdKFNOne!=-1){// 
		if(IdKFNTwo!=-1){//�Q�R������e�ե���ܤ֦�2�ө|���Q�R���������
			if(IdKFPOne!=-1){//�Q�R������e�եk��ܤ֦�1�ө|���Q�R���������
				//�Τ峹���y�z���g���k�ק�p(j-1)��deltaE�Mtao
				
				FirstResult = FirstUp = FirstDown = 0;
				Mmin = 0;
				int  t;
				for(  t=IdKFNTwo; t<IdKFPOne; t++)
				FirstUp += pow(frame[t].Distance( frame[IdKFPOne]), 2);

				FirstResult = FirstUp + FirstDown;
				Mmin = IdKFNTwo;

				for(int m=IdKFNTwo+1; m<IdKFPOne; m++){
					double result=0;
					double up=0;
					double down=0;

					for(t=IdKFNTwo+1; t<=m-1; t++)
						up += pow(frame[t].Distance( frame[IdKFNTwo]), 2);
					for(; t<IdKFPOne; t++)
						down += pow(frame[t].Distance( frame[IdKFPOne]), 2);

					result = up + down;

					if( result<FirstResult ){
						FirstResult = result;
						Mmin = m;
					}
				}
				
//				cout<<"The Prior DeltaE = "<<node[IndexNOne].deltaE<<endl;  
//				Prior = node[IndexNOne].deltaE;
				node[IndexNOne].deltaE = FirstResult - node[IndexNTwo].Eright - node[IndexPOne].Eleft;// - (node[IndexNOne].Eleft + node[IndexNOne].Eright) ;
				node[IndexNOne].tao = Mmin;
//				cout<<"The Posterior DeltaE = "<<node[IndexNOne].deltaE<<endl;  
//				Posterior = node[IndexNOne].deltaE; 
//				if ( Prior > Posterior ){
//					cout<<"!!!!!!!!!!!!!!!!"<<endl;
//					cout<<"The Prior DeltaE = "<<Prior<<endl;
//					cout<<"The Posterior DeltaE = "<<Posterior<<endl;
//					cout<<"The Left Frame = "<<IdKFNOne<<endl;
//					cin>>aForDeltaE; 
//				}
			
			
			}


			else{//�Q�R������e�եk��S���|���Q�R���������
				//��k1
				node[IndexNOne].tao = FramesNum;

				double s=0;
				for(int i=node[IndexNOne].taoleft; i<FramesNum; i++)
					s += pow(frame[i].Distance(frame[IdKFNTwo]), 2);

//				cout<<"The Prior DeltaE = "<<node[IndexNOne].deltaE<<endl;  
//				Prior = node[IndexNOne].deltaE;			
				node[IndexNOne].deltaE = s - (node[IndexNOne].Eleft + node[IndexNOne].Eright);
//				cout<<"The Posterior DeltaE = "<<node[IndexNOne].deltaE<<endl;  
			
//				Posterior = node[IndexNOne].deltaE; 
//				if ( Prior > Posterior){
//					cout<<"!!!!!!!!!!!!!!!!"<<endl;
//					cout<<"The Prior DeltaE = "<<Prior<<endl;
//					cout<<"The Posterior DeltaE = "<<Posterior<<endl;
//					cout<<"The Left Frame = "<<IdKFNOne<<endl;
//					cin>>aForDeltaE; 
//				}
			
			}
		}

		else{//�Q�R������e�ե���u��1�ө|���Q�R���������
			//��k2
			node[IndexNOne].tao = 1;

			double s=0;
			for(int i=1; i<x.tao; i++)
				s += pow(frame[i].Distance(frame[IdKFPOne]), 2);
			
//			cout<<"The Prior DeltaE = "<<node[IndexNOne].deltaE<<endl;  
//			Prior = node[IndexNOne].deltaE;	
			node[IndexNOne].deltaE = s - (node[IndexNOne].Eleft + node[IndexNOne].Eright);
//			cout<<"The Posterior DeltaE = "<<node[IndexNOne].deltaE<<endl;  
//
//			Posterior = node[IndexNOne].deltaE; 
//			if ( Prior > Posterior){
//					cout<<"!!!!!!!!!!!!!!!!"<<endl;
//					cout<<"The Prior DeltaE = "<<Prior<<endl;
//					cout<<"The Posterior DeltaE = "<<Posterior<<endl;
//					cout<<"The Left Frame = "<<IdKFNOne<<endl;
//					cin>>aForDeltaE; 
//			}
		}
	}

	
	
	if(IdKFPOne!=-1){//�Q�R������e�եk��ܤ֦�1�ө|���Q�R���������
		if(IdKFPTwo!=-1){//�Q�R������e�եk��ܤ֦�2�ө|���Q�R���������
			if(IdKFNOne!=-1){//�Q�R������e�ե���ܤ֦�1�ө|���Q�R���������
				//�Τ峹���y�z���g���k�ק�p(j-1)��deltaE�Mtao
				FirstResult = FirstUp = FirstDown = 0;
				Mmin = 0;
				int t;
				for( t=IdKFNOne; t<IdKFPTwo; t++)
				FirstDown += pow(frame[t].Distance(frame[IdKFPTwo]), 2);

				FirstResult = FirstUp + FirstDown;
				Mmin = IdKFNOne;

				for(int m=IdKFNOne+1; m<IdKFPTwo; m++){
					double up = 0;
					double down = 0;
					double result = 0;
					for(t=IdKFNOne+1; t<=m-1; t++)
						up += pow(frame[t].Distance(frame[IdKFNOne]), 2);
					for(; t<IdKFPTwo; t++)
						down += pow(frame[t].Distance(frame[IdKFPTwo]), 2);
					result = up + down;

					if(result < FirstResult){
						FirstResult = result;
						Mmin = m;
					}
				}
				
//				cout<<"The Prior DeltaE = "<<node[IndexPOne].deltaE<<endl;  
//				Prior = node[IndexPOne].deltaE;
				node[IndexPOne].deltaE = FirstResult - node[IndexNOne].Eright - node[IndexPTwo].Eleft;// - (node[IndexPOne].Eleft + node[IndexPOne].Eright) ;
				node[IndexPOne].tao = Mmin;
//				cout<<"The Posterior DeltaE = "<<node[IndexPOne].deltaE<<endl;  
		
//				Posterior = node[IndexPOne].deltaE;
//				if ( Prior > Posterior ){
//					cout<<"!!!!!!!!!!!!!!!!"<<endl;
//					cout<<"The Prior DeltaE = "<<Prior<<endl;
//					cout<<"The Posterior DeltaE = "<<Posterior<<endl;
//					cout<<"The Right Frame = "<<IdKFPOne<<endl;
//					cin>>aForDeltaE; 
//				}

			}

			else{//�Q�R������e�ե���S���|���Q�R���������
				//��k3
				node[IndexPOne].tao = 1;

				double s=0;
				for(int i=1; i<node[IndexPOne].taoright; i++)
					s += pow(frame[i].Distance(frame[IdKFPTwo]), 2);

//				cout<<"The Prior DeltaE = "<<node[IndexPOne].deltaE<<endl;
//				Prior = node[IndexPOne].deltaE;
				node[IndexPOne].deltaE = s - (node[IndexPOne].Eleft + node[IndexPOne].Eright);
//				cout<<"The Posterior DeltaE = "<<node[IndexPOne].deltaE<<endl;  
//				
//				Posterior = node[IndexPOne].deltaE;
//				if ( Prior > Posterior ){
//					cout<<"!!!!!!!!!!!!!!!!"<<endl;
//					cout<<"The Prior DeltaE = "<<Prior<<endl;
//					cout<<"The Posterior DeltaE = "<<Posterior<<endl;
//					cout<<"The Right Frame = "<<IdKFPOne<<endl;
//					cin>>aForDeltaE; 
//				}
			}
		}

		else{//�Q�R������e�եk��u��1�ө|���Q�R���������
			//��k4
			node[IndexPOne].tao = FramesNum;

			double s=0;
			for(int i=x.tao; i<FramesNum; i++)
				s += pow(frame[i].Distance(frame[IdKFNOne]), 2);

//			cout<<"The Prior DeltaE = "<<node[IndexPOne].deltaE<<endl;  
//			Prior = node[IndexPOne].deltaE;
			node[IndexPOne].deltaE = s - (node[IndexPOne].Eleft + node[IndexPOne].Eright);
//			cout<<"The Posterior DeltaE = "<<node[IndexPOne].deltaE<<endl;  
//		
//			Posterior = node[IndexPOne].deltaE;
//		
//			if ( Prior > Posterior ){
//					cout<<"!!!!!!!!!!!!!!!!"<<endl;
//					cout<<"The Prior DeltaE = "<<Prior<<endl;
//					cout<<"The Posterior DeltaE = "<<Posterior<<endl;
//					cout<<"The Right Frame = "<<IdKFPOne<<endl;
//					cin>>aForDeltaE; 
//			}
		}
	}

	
	//���ذ�
	BuildHeap();

//	if(IdKFNOne!=-1) SiftDown(IndexNOne);
//	if(IdKFPOne!=-1) SiftDown(IndexPOne);

	return x.deltaE;

}
	



#endif



			











