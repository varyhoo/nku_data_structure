#include<iostream>
using namespace std;
template<class T>
class extendedChain;
template<class T>
class Node
{
	friend extendedChain<T>;
private:
	Node<T>* next;
	T data;
};
template<class T>
class extendedChain
{
private:
	Node<T>* head, * tail, * now = nullptr;
	int length;
public:
	extendedChain() 
	{
		head = 0;
		length = 0;
		tail = 0;
	}
	void PushBack(const T& x);
	void Insert(int k, const T& x);
	void Output(ostream& out)const;
	int Getlength()const { return length; }
	T Getnow();
	void Reset() { now = head; }
};
template<class T>
void extendedChain<T>::PushBack(const T& x)
{
	this->length++;
	Node<T>* newnode = new Node<T>;
	newnode->data = x;
	newnode->next = NULL;
	if (head)//（空or非空）
	{
		tail->next = newnode;
		tail = newnode;
	}
	else
	{
		now = head = tail = newnode;
	}
}
template<class T>
void extendedChain<T>::Insert(int k, const T& x)
{
	if (k < 0)
	{
		cout << "wrong";
		return;
	}//超限
	Node<T>* p = new Node<T>;
	p->data = x;
	if (k == 0)
	{
		p->next = head;
		head = p;
		length++;
		return;
	}
	Node<T>* temp = this->head;
	for (int i = 0; i < k && temp!=NULL; i++)
	{
		temp = temp->next;
	}
	if (!temp)
	{
		cout << "wrong";
		return;
	}//超限
	p->next = temp->next;
	temp->next = p;
	length++;
}
template<class T>
void extendedChain<T>::Output(ostream& out)const
{
	Node<T>* temp = head;
	while (temp)
	{
		out << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}
template<class T>
T extendedChain<T>:: Getnow()
{
	T x = now->data;
	now = now->next;
	return  x;
}
template<class T>
ostream& operator<<(ostream& out, const extendedChain<T>& x) {
	x.Output(out);
	return out;
}
template<class T>
extendedChain<T> meld(extendedChain<T>& a, extendedChain<T>& b)
{
	extendedChain<T> c;
	int i, j;
	for ( i = 1, j = 1; i <= a.Getlength() && j <= b.Getlength(); i++, j++)
	{
		c.PushBack(a.Getnow());
		c.PushBack(b.Getnow());
	}
	for (; i <= a.Getlength(); i++)
	{
		c.PushBack(a.Getnow());
	}
	for (; j <= b.Getlength(); j++)
	{
		c.PushBack(b.Getnow());
	}
	return c;
}
int main()
{
	extendedChain<char>a, b, c;
	for (int i = 'a'; i <= 'u'; i++) a.PushBack(i);
	for (int i = 'A'; i <= 'Z'; i++)b.PushBack(i);
	c = meld(a, b);
	cout << a;
	cout << b;
	cout << c;
}