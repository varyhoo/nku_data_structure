/************************************************************

	知识点：拷贝构造函数
	序  号：2
	目  的：程序1由于采用浅拷贝的方式出现错误，因此我们自定
			义拷贝构造函数（深拷贝）令对象直接赋值成为可能。

************************************************************/

#include <iostream>
using namespace std;
#include <string.h>							//定义了若干字符串函数

class MyClass
{
	char *name;								//私有数据成员，指针类型
public:
	MyClass(char *);						//声明构造函数
	MyClass(MyClass &);						//新增：声明拷贝构造函数
	~MyClass();								//声明析构函数
	void print();							//声明功能函数，提供打印功能
};

MyClass::MyClass(char *s)					//定义构造函数
{
	cout<<"执行构造函数;"<<endl;
	name = new char[strlen(s)+1];			//申请内存空间
	strcpy(name,s);							//填充内容
}

MyClass::MyClass(MyClass &t)				//新增：定义拷贝构造函数
{
	cout<<"执行拷贝构造函数;"<<endl;
	name = new char[strlen(t.name)+1];		//申请内存空间
	strcpy(name,t.name);					//填充内容
}

MyClass::~MyClass()							//定义析构函数
{
	cout<<"执行析构函数;"<<endl;
	delete []name;							//释放内存空间
}

void MyClass::print()						//定义打印函数
{
	cout<<"学生姓名是："<<name<<endl;		//输出成员name
}

void main()									//主函数
{
	char *p = new char[20];					//申请可存20个char的内存空间
	cout<<"请输入您的姓名：";
	cin>>p;									//由用户输入姓名
	MyClass Obj_A(p);						//调用MyClass的构造函数，创建对象obj_A
	MyClass Obj_B=Obj_A;					//调用新增的“深拷贝构造函数”，重新申请内存空间，与obj_A隔离
	Obj_A.print();
	Obj_B.print();
}