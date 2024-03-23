/*1.所谓双端队列（double-ended queue，deque），就是在列表的两端都可以插入和删除数据。因此它允许的操作有Create、IsEmpty、IsFull、Left、Right、AddLeft、AddRight、DeleteLeft、DeleteRight。使用循环数组方式实现双端队列，要求实现上述操作，并实现一个Print输出操作，能将队列由左至右的次序输出于一行，元素间用空格间隔。队列元素类型设为整型。
输入：input.txt，给出一个操作序列，可能是Create、Print之外的任何操作，需要的情况下，会给出参数。最后以关键字“End”结束，例如：
AddLeft	1
AddLeft	2
DeleteRight
IsFull
DeleteLeft
IsEmpty
AddRight 3
AddLeft 2
AddRight 1
End

输出：程序开始执行时，队列设置为空，按输入顺序执行操作，每个操作执行完后，将结果输出于一行。对于错误命令，输出“WRONG”。对IsEmpty和IsFull命令，试情况输出“Yes”或“No”。对Left和Right命令，若队列空，输出“EMPTY”，否则输出对应队列元素。对Add命令，若队列满，输出“FULL”，否则调用Print，输出队列所有元素。对Del命令，若队列空，输出“EMPTY”，否则输出所有元素。元素间用空格间隔，最后一个元素后不能有空格。最后输出一个回车。

例如，对上例，应输出：
―――――――――
1
2 1
2
No

Yes
3
2 3
2 3 1

――――――――――――――――*/
#include<iostream>
#include<fstream>
using namespace std;
template<class T>
class DoubleEndQuene
{
public:
	DoubleEndQuene(int maxQueneSize = 50);
	bool IsEmpty() { return front == rear; }
	bool IsFull() { return front == (rear + 1) % MaxSize; }
	void Left();
	void Right();
	void AddLeft(const T&);
	void AddRight(const T&);
	void DeleteLeft();
	void DeleteRight();
	void Print();
	//
	int MaxSize;
	int front, rear;//通过使front始终指向队首元素的前一位，而rear始终指向队尾元素当前位置
	T* quene;
};
template<class T>
DoubleEndQuene<T>::DoubleEndQuene(int maxQueneSize)
{
	MaxSize = maxQueneSize+1;
	quene = new T[maxQueneSize];
	front = rear = 0;
}
template<class T>
void DoubleEndQuene<T>::Left()
{
	if (IsEmpty())
	{
		cout << "EMPTY" << endl;
		return;
	}
	cout << quene[front + 1] << endl;
	return;
}
template<class T>
void DoubleEndQuene<T>::Right()
{
	if (IsEmpty())
	{
		cout << "EMPTY" << endl;
		return;
	}
	cout << quene[rear] << endl;
	return;
}
template<class T>
void DoubleEndQuene<T>::AddLeft(const T& x)
{
	if (IsFull())
	{
		cout << "FULL"<<endl;
		return;
	}
	quene[front] = x;
	front = (front - 1 + MaxSize) % MaxSize;
	Print();
	return;
}
template<class T>
void DoubleEndQuene<T>::AddRight(const T& x)
{
	if (IsFull())
	{
		cout << "FULL"<<endl;
		return;
	}
	rear = (rear + 1) % MaxSize;
	quene[rear] = x;
	Print();
	return;
}
template<class T>
void DoubleEndQuene<T>::DeleteLeft()
{
	if (IsEmpty())
	{
		cout << "EMPTY"<<endl;
		return;
	}
	front = (front + 1) % MaxSize;
	Print();
	return;
}
template<class T>
void DoubleEndQuene<T>::DeleteRight()
{
	if (IsEmpty())
	{
		cout << "EMPTY" << endl;
		return;
	}
	rear = (rear - 1 + MaxSize) % MaxSize;
	Print();
}
template<class T>
void DoubleEndQuene<T>::Print()
{
	if (IsEmpty())
	{
		cout << endl;
		return;
	}
	if (front < rear)
	{
		for (int i = front + 1; i <= rear; i++)
		{
			cout << quene[i] << " ";
		}
	}
	else
	{
		for (int i = front + 1; i < MaxSize; i++)cout << quene[i] << " ";
		for (int i = 0; i <= rear; i++)cout << quene[i] << " ";
	}
	cout << endl;
}
int main()
{
	string s;
	DoubleEndQuene<int> a(100);
	int x;
	ifstream infile("input.txt");
	while (infile >> s)
	{
		if (s == "End")return 0;
		if (s == "AddRight")
		{
			infile >> x;
			a.AddRight(x);
		}
		else if (s == "AddLeft")
		{
			infile >> x;
			a.AddLeft(x);
		}
		else if (s == "IsEmpty") 
		{
			if (a.IsEmpty())cout << "Yes" << endl;
			else cout << "No" << endl;
		}
		else if (s == "IsFull")
		{
			if (a.IsFull())cout << "Yes" << endl;
			else cout << "No" << endl;
		}
		else if (s == "Left")
		{
			a.Left();
		}
		else if (s == "Right") 
		{
			a.Right();
		}
		else if (s == "DeleteLeft")
		{
			a.DeleteLeft();
		}
		else if (s == "DeleteRight")
		{
			a.DeleteRight();
		}
	}
}