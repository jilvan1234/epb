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
	int rrnum=str.length();
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
		p2->next=NULL;
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
	}
	else
	{
		temp->next=list;
		list->next=head;
	}
}
int main()
{
	

	head=creat();
	showbook(head);
	cout<<"�п�J�A�n�R�����Ϯѽs��: ";
	int BookNum;
	cin>>BookNum;
	Delete(head,BookNum);
	showbook(head);
	cout<<"�п�J�z�n���J���Ϯѽs��: ";
	cin>>BookNum;
	cout<<"�п�J�z�n���J������: ";
	float BookPrice;
	cin>>BookPrice;
	insert(head,BookNum,BookPrice);
	showbook(head);
	system("pause");
	return 0;
};
