#include<iostream>
using namespace std;
#include<cassert>
#include<fstream>
#include<cctype>
#include<cstdlib>

fstream file;

//////////////////////string
class String
{
	private:
		char* string;
		int cnt;
		int maxSize;
	public:
		String();
		String(char* str);
		char* getString();
		void strcpy(String str);
		void strcat(String str);
		bool strcmp(String str);
		int Length();
};


String::String()
{
	string=NULL;
	cnt=0;
	maxSize=100;
}
String::String(char* str)
{
	cnt=0;
	string=new char;
	for(int i=0;str[i]!='\0';i++)
	{
		cnt++;
		string[i]=str[i];
	}
	maxSize=100;
}

void String::strcpy(String str)
{
	char* temp=string;
	string=str.getString();
	delete[] temp;
}


void String::strcat(String str)
{
	for(int i=0;i<str.Length();i++)
	{
		string[cnt+i]=str.getString()[i];
	}
}

bool String::strcmp(String str)
{
	if(Length()==str.Length())
	{
		int i;
		for(i=0;i<Length();i++)
		{
			if(string[i]!=str.getString()[i])
			{
				return false;
			}
		}
		if(i==Length())
		{
			return true;
		}
	}
	return false;
}


int String::Length()
{
	return cnt;
}

char* String::getString()
{
	return string;
}



//////////////////////////////////////////////node
template<class Type>
class Node
{
	public:
		Node<Type>* left;
		Node<Type>* right;
		Type data;
		static Node<Type>* freelist;
		void* operator new(size_t);
		void operator delete(void* temp); 
		Node(Type element,Node<Type>* ln=NULL,Node<Type>* rn=NULL);
		Node(Node<Type>* ln=NULL,Node<Type>* rn=NULL);
		Type getValue();
};



template<class Type>
Node<Type>* Node<Type>::freelist=NULL;

template<class Type>
void* Node<Type>::operator new(size_t)
{
	if(freelist==NULL)
	{
		return ::new Node;
	}
	Node<Type>* temp=freelist;
	freelist=freelist->right;
	return temp;
}

template<class Type>
void Node<Type>::operator delete(void* temp)
{
	((Node<Type>*)temp)->right=freelist;
	freelist=(Node<Type>*)temp;
}



template<class Type>
Node<Type>::Node(Type element,Node<Type>* ln,Node<Type>* rn)
{
	data=element;
	left=ln;
	right=rn;
}

template<class Type>
Node<Type>::Node(Node<Type>* ln,Node<Type>* rn)
{
	left=ln;
	right=rn;
}

template<class Type>
Type Node<Type>::getValue()
{
	return data;
}




////////////////////////////////////////////double linked list
template<class Type>
class DLList
{
	private:
		Node<Type>* head;
		Node<Type>* curr;
		Node<Type>* tail;
		int currSize;
		void init();
		void removeAll();
	public:
		DLList();
		~DLList();
		void clear();
		int Length();
		void insert(Type& num);
		void append(Type& num);
		void remove();
		void moveTohead();
		void moveTotail();
		void pre();
		void next();
		void traversal();
		Node<Type>* getCurr();
		Type getCurr_value();
};



template<class Type>
void DLList<Type>::init()
{
	head=curr=tail=new Node<Type>(NULL);
	currSize=0;
}

template<class Type>
void DLList<Type>::removeAll()
{
	while(head!=NULL)
	{
		curr=head;
		head=head->right;
		delete curr;
	}
}

template<class Type>
int DLList<Type>::Length()
{
	return currSize;
}

template<class Type>
DLList<Type>::DLList()
{
	init();
}

template<class Type>
DLList<Type>::~DLList()
{
	removeAll();
}


template<class Type>
void DLList<Type>::clear()
{
	removeAll();
	init();
}

template<class Type>
void DLList<Type>::insert(Type& num)
{
	if(curr==tail)
	{
		append(num);
	}
	else
	{
		curr->right=new Node<Type>(num.getString(),curr,curr->right);
		currSize++;
	}
	
}

template<class Type>
void DLList<Type>::append(Type& num)
{
	tail=tail->right=new Node<Type>(num.getString(),tail,tail->right);
	currSize++;
}

template<class Type>
void DLList<Type>::remove()
{
	if(head==tail)
	{
		return ;
	}
	moveTohead();
	Node<Type>* temp=curr->right;
	if(temp==tail)
	{
		tail=tail->left;
		delete temp;
		currSize--;
		return;
	}
	curr->right->right->left=curr;
	curr->right=curr->right->right;
	delete temp;
	currSize--;
	curr=curr->left;
}

template<class Type>
void DLList<Type>::moveTohead()
{
	curr=head;
}

template<class Type>
void DLList<Type>::moveTotail()
{
	curr=tail;
}

template<class Type>
void DLList<Type>::pre()
{
	curr=curr->left;
}

template<class Type>
void DLList<Type>::next()
{
	curr=curr->right;
}

template<class Type>
void DLList<Type>::traversal()
{
	assert((currSize!=0,"The list is empty"));
	moveTohead();
	char  tttt[5]="NULL";
	char* temp=tttt;
	String tempstring(temp); 
	next();
	if(head==tail)
	{
		return ;
	}
	while(curr!=NULL)
	{
		if(curr->getValue().strcmp(tempstring))
		{
			cout<<endl;
		}
		else
		{
			cout<<curr->getValue().getString()<<endl;
		}
		curr=curr->right;
	}
}


template<class Type>
Node<Type>* DLList<Type>::getCurr()
{
	return curr->right;
}



template<class Type>
Type DLList<Type>::getCurr_value()
{
	return getCurr()->getValue().getString();
}




/////////////////////////////////////textEdit
template<class Type>
class textEdit
{
	private:
		DLList<Type>* list;
	public:
		textEdit();
		~textEdit();
		void Write();
		void Read();
		void Insert();
		void Delete();
		int  FindFromHead(String str);
		int  FindFromCurr(String str);
		void CorrectAll(String Pstr,String Tstr);
		void CorrectLine(String Pstr,String Tstr);
		void Quit();
		void Help();
		void Down();
		void Up();
		void backTohead();
		void End();
		void goLine(int pos);
		void View();
};

template<class Type>
textEdit<Type>::textEdit()
{
	list=new DLList<Type>;
}

template<class Type>
textEdit<Type>::~textEdit()
{
	delete list;
}

template<class Type>
void textEdit<Type>::Write()
{
	file.open("text.txt",ios::out);
	if(file.fail())
	{
		cout<<"have some wrong when open this file"<<endl;
		exit(-1); 
	}
	char* temp; 
	char  tttt[5]="NULL";
	char* element=tttt;
	String compareelement(element);
	
	list->moveTohead();
	while(list->getCurr()!=NULL)
	{
		temp=list->getCurr_value().getString();
		if(list->getCurr_value().strcmp(compareelement))
		{
			file<<'\n';
		}
		else
		{
			file<<temp;
			file<<'\n';
		}
		list->next();
	}
	file.close();
}


template<class Type>
void textEdit<Type>::Read()
{
	file.open("text.txt",ios::in);
	if(file.fail())
	{
		cout<<"have some wrong when open this file"<<endl;
		exit(-1); 
	}
	list->clear();
	char* temp;
	char ch;
	list->moveTohead();
	while(!file.eof())
	{
		file>>temp;
		String tempstring(temp);
		list->append(tempstring);
	}
	
	file.close();
	list->moveTohead();
}




template<class Type>
void textEdit<Type>::Insert()
{
	int linenumber=0;
	char* temp=new char;
	int curr_length=list->Length();
	cout<<"Please input the line number you want to insert:";
	cin>>linenumber;
	list->moveTohead();
	cout<<"Please input the content you want to insert:";
	cin>>temp;
	String tempstring(temp);
	for(int i=1;i<linenumber;i++)
	{	
		if(i>curr_length)
		{
			char tttt[5]="NULL";
			char* nullrepresent=tttt;
			String anothertemp(nullrepresent);
			list->append(anothertemp);
		}
		list->next();
	}	
	list->insert(tempstring);
} 


template<class Type>
void textEdit<Type>::Delete()
{
	list->remove();
}


template<class Type>
int textEdit<Type>::FindFromHead(String str)
{
	list->moveTohead();
	int i=0;
	if(list->Length()==0)
	{
		return 0;
	}
	while(list->getCurr()!=NULL)
	{
		i++;
		if(!list->getCurr_value().strcmp(str))
		{
			return i;	
		}	
	}	
	return 0;
} 


template<class Type>
int textEdit<Type>::FindFromCurr(String str)
{
	int i=0;
	if(list->Length()==0)
	{
		return 0;
	}
	while(list->getCurr()!=NULL)
	{
		i++;
		if(!list->getCurr_value().strcmp(str))
		{
			return i;	
		}	
	}	
	return 0;
} 



template<class Type>
void textEdit<Type>::CorrectAll(String Pstr,String Tstr)
{
	list->moveTohead();
	if(list->Length()==0)
	{
		return ;
	}
	while(list->getCurr()!=NULL)
	{
		if(!list->getCurr_value().strcmp(Pstr))
		{
			list->getCurr_value().strcpy(Tstr);
		}
	}
}


template<class Type>
void textEdit<Type>::CorrectLine(String Pstr,String Tstr)
{
	if(list->Length()==0)
	{
		return ;
	}
	while(list->getCurr()!=NULL)
	{
		if(!list->getCurr_value().strcmp(Pstr))
		{
			list->getCurr_value().strcpy(Tstr);
		}
	}
	
}



template<class Type>
void textEdit<Type>::Quit()
{
	exit(-1);
}

template<class Type>
void textEdit<Type>::Help()
{
	cout<<"R:��ȡ�ı��ļ����������У��������е�ǰ���κ����ݽ���ʧ����ǰ�����ļ��ĵ�һ�С�"<<endl;
	cout<<"W:��������������д���ı��ļ�����ǰ�л򻺳��������ı䡣"<<endl;
	cout<<"I:���뵥������" <<endl; 
	cout<<"D:ɾ����ǰ�в��Ƶ���һ��"<<endl;
	cout<<"F:�ӵ�ǰ�л��һ�п�ʼ�����Ұ������û������Ŀ�괮�ĵ�һ��"<<endl;
	cout<<"C:�޸ĵ�ǰ�л�ȫ�ĵ�ָ���ַ���Ϊ����ַ���"<<endl; 
	cout<<"Q:�˳��༭������������"<<endl;
	cout<<"H:��ʾ����İ�����Ϣ"<<endl;
	cout<<"N:�ڻ������ڣ�����ǰ������һ��"<<endl;
	cout<<"P:�ڻ������ڣ�����ǰ������һ��"<<endl;
	cout<<"B:�ڻ������У�����ǰ���Ƶ���һ��"<<endl;
	cout<<"E:�ڻ������У�����ǰ���Ƶ�������"<<endl;
	cout<<"G:�ڻ������У�����ǰ���Ƶ�ָ���к�"<<endl;
	cout<<"V:�鿴������ȫ�����ݣ���ӡ���ն���"<<endl; 
}




template<class Type>
void textEdit<Type>::Down()
{
	if(list->Length()==0)
	{
		return ;
	}
	if(list->getCurr()->right!=NULL)
	{
		list->next();
	}
	else
	{
		cout<<"��ǰ����Ϊ�����������һ�У����ܼ�������"<<endl;
	}
} 


template<class Type>
void textEdit<Type>::Up()
{
	if(list->Length()==0)
	{
		cout<<"��������û������"<<endl;
	}
	else if(list->Length()==1)
	{
		cout<<"��ǰ��Ϊ�������ڵ�һ�У����ܼ���ǰ��"<<endl;
	}
	else
	{
		list->pre();
	}
}

template<class Type>
void textEdit<Type>::backTohead()
{
	list->moveTohead();
}


template<class Type>
void textEdit<Type>::End()
{
	list->moveTotail();
}

template<class Type>
void textEdit<Type>::goLine(int pos)
{
	list->moveTohead();
	if(pos<1||pos>list->Length())
	{
		cout<<"The pos is out of range"<<endl;
		return;
	}
	for(int i=1;i<pos;i++)
	{
		list->next();
	}
}


template<class Type>
void textEdit<Type>::View()
{
	cout<<endl<<endl<<"�ļ��������£�"<<endl;
	list->traversal();
	cout<<endl<<endl;
}







/////////////////////////////////////mianWindow
void mainWindow()
{
	cout<<"   ========================================================================="<<endl;
	cout<<"   |**|          ===================Editor=================             |**|"<<endl;
	cout<<"   |**|=================================================================|**|"<<endl;
	cout<<"   |**| R:�����ļ�       W��д���ļ�       I:��������       D:ɾ����ǰ��|**|"<<endl; 
	cout<<"   |**| F:�����ַ���     C������ַ���     Q:�˳��༭��     H:����      |**|"<<endl; 
	cout<<"   |**| N:����+1         P������-1         B:����=1         E:����=last |**|"<<endl; 
	cout<<"   |**|                  G������=ָ��      V:��ӡ������                 |**|"<<endl; 
	cout<<"   ========================================================================="<<endl;
	cout<<"   |**|          ===================&&&&&&=================             |**|"<<endl;
	cout<<"   |**|=================================================================|**|"<<endl;
}


int main(void)
{
	textEdit<String> editor;
	char induction;
	char flag;
	file.open("text.txt",ios::out);
	file.close();
	editor.Read();
	mainWindow();
	while(1)
	{
		cout<<endl<<endl;
		cout<<"��������ѡ������";
		cin>>induction;
		induction=toupper(induction);
		switch(induction)
		{
			case 'R':
				{
					editor.Read();
					cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
					while(1)
					{
						cin>>flag;
						flag=toupper(flag);
						if(flag=='C')
						{
							editor.Read();
							break;
						}
						else if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
			case 'W':
				{
					editor.Write();
					cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
					while(1)
					{
						cin>>flag;
						flag=toupper(flag);
						if(flag=='C')
						{
							editor.Write();
							cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						}
						else if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
					
			case 'I':
				{
					editor.Insert();
					cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
					while(1)
					{
						cin>>flag;
						flag=toupper(flag);
						if(flag=='C')
						{
							editor.Insert();
							cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						}
						else if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					
					break;
				}
					
			case 'D':
				{
					editor.Delete();
					cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
					while(1)
					{
						cin>>flag;
						flag=toupper(flag);
						if(flag=='C')
						{
							editor.Delete();
							cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						}
						else if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;	
						}
					}
					
					break;
				}
					
			case 'F':
				{
					char* tempchar=new char;
					String temp;
					char fromHeadorCurr;
					while(1)
					{
						cout<<"��������ҵ��ַ�����";
						cin>>tempchar;
						temp.strcpy(tempchar);
						cout<<"�ӵ�ǰ�п�ʼ���ң�Y/���ļ��׿�ʼ���ң�N"<<endl;
						cin>>fromHeadorCurr;
						fromHeadorCurr=toupper(fromHeadorCurr);
						if(fromHeadorCurr=='Y')
						{
							int res=editor.FindFromCurr(temp);
							if(res==0)
							{
								cout<<"none"<<endl<<endl;
							}
							else
							{
								cout<<res<<endl<<endl;
							}
							break;
						}
						else if(fromHeadorCurr=='N')
						{
							editor.FindFromHead(temp);
							break; 
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					delete tempchar;
					while(1)
					{
						cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						cin>>flag;
						flag=toupper(flag);
						if(flag=='C')
						{
							if(fromHeadorCurr=='Y')
							{
								int res=editor.FindFromCurr(temp);
								if(res==0)
								{
									cout<<"none"<<endl<<endl;
								}
								else
								{
									cout<<res<<endl<<endl;
								}
							}
							else if(fromHeadorCurr=='N')
							{
								int res=editor.FindFromHead(temp);
								if(res==0)
								{
									cout<<"none"<<endl<<endl;
								}
								else
								{
									cout<<res<<endl<<endl;
								}
							}
						}
						if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
					
			case 'C':
				{
					char* pretemp=new char;
					char* ttemp=new char;
					String Pstr,Tstr;
					char replace;
					while(1)
					{
						cout<<"�������豻�滻���ַ�����";
						cin>>pretemp;
						cout<<"������Ҫ�滻���ַ������ַ�����";
						cin>>ttemp;
						Pstr.strcpy(pretemp);
						Tstr.strcpy(ttemp);
						cout<<"�ӵ�ǰ�п�ʼ�滻��Y/�滻ȫ�ģ�N<<endl";
						cin>>replace;
						replace=toupper(replace);
						if(replace=='Y')
						{
							editor.CorrectLine(Pstr,Tstr);
							break;
						}
						else if(replace=='N')
						{
							editor.CorrectAll(Pstr,Tstr);
							break; 
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					delete pretemp;
					delete ttemp;
					while(1)
					{
						cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						cin>>flag;
						flag=toupper(flag);
						if(flag=='C')
						{
							if(replace=='Y')
							{
								editor.CorrectLine(Pstr,Tstr);
							}
							else if(replace=='N')
							{
								editor.CorrectAll(Pstr,Tstr);
							}
						}
						if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
					
			case 'Q':
				{
					editor.Quit();
					break;
				}
			case 'H':
				{
					cout<<endl<<endl;
					editor.Help();
					while(1)
					{
						cout<<"���������棿Y/�˳��༭����Q"<<endl;
						cin>>flag;
						flag=toupper(flag);
						if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					cout<<endl<<endl;
					break;
				}
					
			case 'N':
				{
					editor.Down();
					char tempdown;
					while(1)
					{
						cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						cin>>tempdown;
						tempdown=toupper(tempdown);
						if(tempdown=='C')
						{
							editor.Down();
						}
						else if(tempdown=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(tempdown=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
					
			case 'P':
				{
					editor.Up();
					char tempup;
					while(1)
					{
						cout<<"��������?C/���������棿Y/�˳��༭����Q"<<endl;
						cin>>tempup;
						tempup=toupper(tempup);
						if(tempup=='C')
						{
							editor.Up();
						}
						else if(tempup=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(tempup=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
					
			case 'B':
				{
					editor.backTohead();
					char tempback;
					while(1)
					{
						cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						cin>>tempback;
						tempback=toupper(tempback);
						if(tempback=='C')
						{
							editor.backTohead();
						}
						else if(tempback=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(tempback=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}

					}
					break;
				}
					
			case 'E':
				{
					editor.End();
					char tempend;
					while(1)
					{
						cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						cin>>tempend;
						tempend=toupper(tempend);
						if(tempend=='C')
						{
							editor.End();
						}
						else if(tempend=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(tempend=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
					
			case 'G':
				{
					int pos;
					cout<<"������Ҫ��������";
					cin>>pos;
					editor.goLine(pos);
					while(1)
					{
						cout<<"����������C/���������棿Y/�˳��༭����Q"<<endl;
						cin>>flag;
						flag=toupper(flag);
						if(flag=='C')
						{
							cout<<"������Ҫ��������";
							cin>>pos;
							editor.goLine(pos);
						}
						else if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
				
			case 'V':
				{
					editor.View();
					while(1)
					{
						cout<<"���������棿Y/�˳��༭����Q"<<endl;
						cin>>flag;
						flag=toupper(flag);
						if(flag=='Y')
						{
							system("cls");
							mainWindow();
							break;
						}
						else if(flag=='Q')
						{
							editor.Quit();
							break;
						}
						else
						{
							cout<<"���벻���Ϲ涨������������"<<endl;
						}
					}
					break;
				}
					
			default:
					break;
		} 
	}
	return 0;
}















































