#include<iostream>
#include<fstream>
using namespace std;
int a[200];
bool s[200];
class Array_Stack
{
public:
	Array_Stack(int n);
	void pop(int m);
	void fun(int m);
	int* array;
	int len;
};
Array_Stack::Array_Stack(int n)
{
	array = new int[n + 1];
	len = n;
	for (int i = 1; i <= n; i++)
	{
		array[i-1] = i;
	}
}
void Array_Stack::pop(int m)
{
	cout << array[m] << " ";
	for (int j = m; j < len; j++)
	{
		array[j] = array[j + 1];
	}
}
void Array_Stack::fun(int m)
{
	int now = 0;
	while (len > 0)
	{
		now = (now + m - 1) % len;
		pop(now);
		len--;
	}
}
template<class T>
class Chain;
template<class T>
class Node
{
	friend Chain<T>;
private:
	T data;
	Node<T>* next;
};
void Initialize(int n) 
{
	for (int i = 0; i < n; i++)
		a[i] = i + 1, s[i] = 1;
}
template<class T>
class Chain
{
public:
	Chain() { first = last = NULL; len = 0; }
	void pushback(T x);
	void remove(int index, T& x);
	int getlen() { return len; }
private:
	Node<T>* first, * last;
	int len;
};
template<class T>
void Chain<T>::pushback(T x)
{
	Node<T>* p = new Node<T>;
	p->data = x;
	p->next = NULL;
	if (first)
	{
		last->next = p;
		last = p;
	}
	else
	{
		first = last = p;
	}
	len++;
}
template<class T>
void Chain<T>::remove(int index, T& x) {
	if (index < 0) {
		cout << "wrong";
		return;
	}
    Node<T>* p = first;
	if (index == 0) {
		x = first->data;
		first = first->next;
		len--;
		delete p;
		return;
	}//如果删除的是表头
	int i = 1;
	while (p && i < index) {
		p = p->next;
		i++;
	}//找到要删除节点的前一个
	if (!p || !p->next) {
		cout << "wrong";
		return;
	}//如果超界，报错
	Node<T>* q = p->next;
	x = q->data;
	p->next = q->next;
	delete q;
	len--;
}

int main()
{
	int n,m;
	ifstream infile("input.txt");
	infile>> n >> m;
	Array_Stack a(n);
	a.fun(m);
	cout << endl;
	Chain<int>x;
	for (int i = 1; i <= n; i++)
	{
		x.pushback(i);
	}
	int now = 0;
	int count = n;
	while (count--)
	{
		now = (now + m - 1) % x.getlen();
		int a;
		x.remove(now, a);
		cout << a << " ";
	}
}