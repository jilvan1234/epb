#include <iostream>
#include <string>
using namespace std;

class book{
public:
	int num;
	float price;
	book*next;
};

book*head=NULL;
bool check(string str)
{
	int rrnum = str.length();
	for(int i=0;i<rrnum;i++)
	{
		if((str[i]>'9'||str[i]<'0')&&(str[i]!='.'))
			return false;
	}
	return true;

}
book*creat()
{
	book*p1,*p2;
	p1=new book;
	head=p1;
	p2=p1;
	cout<<"�п�J�ϮѪ��s��, �H 0 ����"<<endl;
	string str;
	cin>>str;
	while(!check(str))
	{
		cout<<"��J�����O�Ʀr.�Э��s��J,��0��^!!!"<<endl;
		cin>>str;
	}
	p1->num=atoi(str.c_str());
	
	if(p1->num!=0)
	{
		cout<<"�п�J�ϮѪ�����"<<endl;		
		cin>>str;
		while(!check(str))
		{
			cout<<"��J�����O�Ʀr.�Э��s��J,��0��^!!!"<<endl;
			cin>>str;
		}
		p1->price=(float)atof(str.c_str());
	}
	else
	{
		delete p1;
		p2=NULL;
		//p2->next=NULL;
		head=NULL;
		return head;
	}
	while(p1->num!=0)
	{
		p2 = p1;
		p1 = new book;
		cout<<"�п�J�ϮѪ��s��, �H 0 ����"<<endl;		
		cin>>str;
		while(!check(str))
		{
			cout<<"��J�����O�Ʀr.�Э��s��J,��0��^!!!"<<endl;
			cin>>str;
		}
		p1->num=atoi(str.c_str());
		if(p1->num!=0)
		{
			cout<<"�п�J�ϮѪ�����"<<endl;
			cin>>str;
			while(!check(str))
			{
				cout<<"��J�����O�Ʀr.�Э��s��J,��0��^!!!"<<endl;
				cin>>str;
			}
			p1->price=(float)atof(str.c_str());
			
		}
		p2->next=p1;
	}
	delete p1;
	p2->next=NULL;
	return head;
}
void showbook(book*head)
{
	cout<<endl;
	cout<<"�ϮѫH���p�U�G "<<endl;
	while(head)
	{
		cout<<"�Ϯѽs��: "<<head->num<<"\t";
		cout<<"price: "<<head->price<<endl;
		head=head->next;
	}
}
void Delete(book*head,int num)
{
	book*l;
	if(head->num==num)
	{
		l=head;
		head=head->next;
		::head=head;
		delete l;
		cout<<"�ާ@���\"<<endl;
		return;
	}
	while(head)
	{
		if(head->next==NULL)
		{
			cout<<"�䤣��n�R�����s�� "<<endl;
			return;
		}
		if(head->next->num==num)
		{
			l=head->next;
			head->next=l->next;
			delete l;
			cout<<"�ާ@���\"<<endl;
			return;
		}
		head=head->next;
	}
	cout<<"�䤣��n�R�����s��"<<endl;
}
void insert(book*head,int num,float price)
{
	book*list=new book;	
	list->num=num;
	list->price=price;
	if(num<=head->num)
	{
		list->next=head;
		::head=list;
		return;
	}
	book*temp=NULL;
	while((num>head->num)&&(head->next!=NULL))
	{
		temp=head;
		head=head->next;
	}
	if(num>head->num)
	{
		head->next=list;
		list->next=NULL;
	}
	else
	{
		temp->next=list;
		list->next=head;
	}
}
int getBookNum(book*head)
{
	int num=0;
	while(head)
	{
		num++;
		head=head->next;
	}
	return num;
}
int main()
{
	string str;
begin:
	cout<<"1->���عϮ�2->��ܹϮ�3->���J�Ϯ�4->�R���Ϯ�5->�ϮѼƥ�Q->���}"<<endl;
	cin>>str;
	if(str[0]=='1')
	{
		::head=creat();
		system("cls");
		goto begin;
	}
	else if(str[0]=='2')
	{
		if(head==NULL)
		{
			cout<<"�z���ϮѲ{�b�O�Ū��A�мW�[�Ϯ�"<<endl<<"���T�w��^�D�{��"<<endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		showbook(head);
	}
	else if(str[0]=='3')
	{
		if(head==NULL)
		{
			cout<<"�z���ϮѲ{�b�O�Ū��A�мW�[�Ϯ�"<<endl<<"���T�w��^�D�{��"<<endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		cout<<"�п�J�n���J���Ϯѽs��, �H 0 ��^"<<endl;
		string str;
		int num;
		float price;
		cin>>str;
		while(!check(str))
		{
			cout<<"��J�����O�Ʀr.�Э��s��J,��0��^!!!"<<endl;
			cin>>str;
		}
		num=atoi(str.c_str());
	
		if(num!=0)
		{
			cout<<"�п�J�ϮѪ�����"<<endl;		
			cin>>str;
			while(!check(str))
			{
				cout<<"��J�����O�Ʀr.�Э��s��J,��0��^!!!"<<endl;
				cin>>str;
			}
			
			price=(float)atof(str.c_str());
		}
		else
		{
			system("cls");
			goto begin;
		}
		insert(head,num,price);
		cout<<"�ާ@�����A���T�w��^�D�{��"<<endl;
	}	
	else if(str[0]=='4')
	{
		if(head==NULL)
		{
			cout<<"�z���ϮѲ{�b�O�Ū��A�мW�[�Ϯ�"<<endl<<"���T�w��^�D�{��"<<endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		cout<<"�п�J�n�R�����Ϯѽs��, �H 0 ��^"<<endl;
		string str;
		int num;
		
		cin>>str;
		while(!check(str))
		{
			cout<<"��J�����O�Ʀr.�Э��s��J,��0��^!!!"<<endl;
			cin>>str;
		}
		num=atoi(str.c_str());
	
		Delete(head,num);
		cout<<"�ާ@�����A���T�w��^�D�{��"<<endl;
	}
	else if(str[0]=='5')
	{
		cout<<"�ϮѼƥجO: "<<getBookNum(head)<<endl<<"���T�w���^�D�{��"<<endl;
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
	else
	{
		if(str[0]!='Q'&&str[0]!='q')
		{
			cout<<"�п�J�Ʀr!���T�w��^�~��ާ@";
		}
	}
	if(str[0]!='Q'&&str[0]!='q')
	{
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}

	system("pause");
	return 0;
};
