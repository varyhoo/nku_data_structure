#include<iostream>
using namespace std;

template<class T>
class DoubleLinkedList;

template<class T>
class DoubleLinkedNode
{
	friend DoubleLinkedList<T>;
private:
	T data;
	DoubleLinkedNode<T>* previous, * next;
};

template<class T>
class DoubleLinkedList
{
	DoubleLinkedNode<T>* head, * tail, * now;
	int length;
public:
	DoubleLinkedList() {
		head = nullptr;
		tail = nullptr;
		length = 0;
	}
	int Getlength()const { return length; };
	void Insert(int k, const T& x);
	void PushBack(const T& x);
	void Split();
	void Output(ostream& out)const;
	T GetNowNode();
	void Reset() { now = head; }
};

template<class T>
void DoubleLinkedList<T>::Output(ostream& out)const
{
	DoubleLinkedNode<T>* temp = new DoubleLinkedNode<T>();
	temp = this->head;
	while (temp != nullptr)
	{
		out << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}//输出相关数据

template<class T>
ostream& operator<<(ostream& out, const DoubleLinkedList<T>& x)
{
	x.Output(out);
	return out;
}//运算符重载

template<class T>
void DoubleLinkedList<T>::Insert(int k, const T& x)
{
	if (k < 0)
	{
		cout << "WRONG";
		return;
	}
	DoubleLinkedNode<T>* temp = head;
	for (int i = 1; i < k && temp; i++)
	{
		temp = temp->next;
	}
	if (!temp)
	{
		cout << "WRONG";
		return;
	}
	DoubleLinkedNode<T>* temp1 = new DoubleLinkedNode<T>;
	temp1->data = x;
	temp1->next = nullptr;
	if (k == 0)
	{
		temp1->next = head->next;
		head = temp1;
		return;
	}
	if (temp->next)
	{
		DoubleLinkedNode<T>* temp2 = temp->next;
		temp2->previous = temp1;
		temp1->next = temp2;
		temp->next = temp1;
		temp1->previous = temp;
	}
	else
	{
		temp->next = temp1;
		temp1->previous = temp;
	}
}

template<class T>
T DoubleLinkedList<T>::GetNowNode()
{
	T x = now->data;
	now = now->next;
	return x;
}

template<class T>
void DoubleLinkedList<T>::PushBack(const T& x)
{
	length++;
	DoubleLinkedNode<T>* p = new DoubleLinkedNode<T>;
	p->data = x;
	p->next = nullptr;
	if (head != nullptr)
	{
		tail->next = p;
		p->previous = tail;
		tail = p;
	}
	else if (head == nullptr)
	{
		head = tail = p;
		now = head;
		head->next = p;
	}
}

template<class T>
void DoubleLinkedList<T>::Split() {
	int len = length;
	int i;
	for (i = 1; i <= len - 1; i += 2) {
		PushBack(GetNowNode());
		GetNowNode();
	}
	if (i <= len)PushBack(GetNowNode());
	Reset();
	GetNowNode();
	for (i = 2; i <= len; i += 2) {
		PushBack(GetNowNode());
		GetNowNode();
	}
}
int main()
{
	DoubleLinkedList<int> c;
	for (int i = 1; i <= 20; i++) { c.PushBack(i); }
	c.Split();
	cout << c;
	
}