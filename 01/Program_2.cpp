/************************************************************

	֪ʶ�㣺�������캯��
	��  �ţ�2
	Ŀ  �ģ�����1���ڲ���ǳ�����ķ�ʽ���ִ�����������Զ�
			�忽�����캯��������������ֱ�Ӹ�ֵ��Ϊ���ܡ�

************************************************************/

#include <iostream>
using namespace std;
#include <string.h>							//�����������ַ�������

class MyClass
{
	char *name;								//˽�����ݳ�Ա��ָ������
public:
	MyClass(char *);						//�������캯��
	MyClass(MyClass &);						//�����������������캯��
	~MyClass();								//������������
	void print();							//�������ܺ������ṩ��ӡ����
};

MyClass::MyClass(char *s)					//���幹�캯��
{
	cout<<"ִ�й��캯��;"<<endl;
	name = new char[strlen(s)+1];			//�����ڴ�ռ�
	strcpy(name,s);							//�������
}

MyClass::MyClass(MyClass &t)				//���������忽�����캯��
{
	cout<<"ִ�п������캯��;"<<endl;
	name = new char[strlen(t.name)+1];		//�����ڴ�ռ�
	strcpy(name,t.name);					//�������
}

MyClass::~MyClass()							//������������
{
	cout<<"ִ����������;"<<endl;
	delete []name;							//�ͷ��ڴ�ռ�
}

void MyClass::print()						//�����ӡ����
{
	cout<<"ѧ�������ǣ�"<<name<<endl;		//�����Աname
}

void main()									//������
{
	char *p = new char[20];					//����ɴ�20��char���ڴ�ռ�
	cout<<"����������������";
	cin>>p;									//���û���������
	MyClass Obj_A(p);						//����MyClass�Ĺ��캯������������obj_A
	MyClass Obj_B=Obj_A;					//���������ġ�������캯���������������ڴ�ռ䣬��obj_A����
	Obj_A.print();
	Obj_B.print();
}