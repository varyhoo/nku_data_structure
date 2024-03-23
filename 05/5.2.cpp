#include<iostream>
#include<limits.h>
using namespace std;
template<class T>
class Node {
public:
	T data;
	Node<T>* next;
};
template<class T>
class Chain {
	friend Node<T>;
public:
	Chain() { first = NULL; }
	Node<T>* first;
};
template<class T>
class Chain_HashTable {
public:
	Chain_HashTable(int div = 23);
	void Insert(const T&);
	bool Search(const T&);
	void Delete(const T&);
	void Output();
	int divisor;
	Chain<T>* hashtable;
	Node<T>* tail;
	int hash(const int& x) { return x % divisor; }
};
template<class T>
Chain_HashTable<T>::Chain_HashTable(int div)
{
	divisor = div;
	hashtable = new Chain<T>[div];
	tail = new Node<T>;
	tail->next = nullptr;
	tail->data = INT_MAX;
}
template<class T>
void Chain_HashTable<T>::Insert(const T& x)
{
	if (Search(x))
	{
		cout << "元素已存在" << endl;
		return;
	}
	int h = hash(x);
	Node<T>* p = new Node<T>;
	p->data = x;
	p->next = 0;
	if (hashtable[h].first)
	{
		p->next = hashtable[h].first;
		hashtable[h].first = p;
	}
	else {
		p->next = tail;
		hashtable[h].first = p;
	}
}
template<class T>
bool Chain_HashTable<T>::Search(const T& x)
{
	int h = hash(x);
	Node<T>* p = hashtable[h].first;
	if (!p)return false;
	while (p->data != x && p->data != INT_MAX)p = p->next;
	if (p->data == x)return true;
	return false;
}
template<class T>
void Chain_HashTable<T>::Delete(const T& x)
{
	if (!Search(x))
	{
		cout << "元素不存在"<<endl;
		return;
	}
	int h = hash(x);
	Node<T>* p = hashtable[h].first;
	if (p->data == x)
	{
		hashtable[h].first = p->next;
		return;
	}
	while (p->next->data != x)
	{
		cout << "*";
		p = p->next;
	}
	Node<T>* q = p->next;
	p->next = p->next->next;
	delete q;
}
template<class T>
void Chain_HashTable<T>::Output()
{

	cout << endl;
	cout << "元素在哈希表中：" << endl;
	for (int i = 0; i < divisor; i++) 
	{
		Node<T>* p = hashtable[i].first;
		if (!p)continue;
		if (p->data == INT_MAX)continue;
		cout << "元素位于第" << i << "个桶中,为：";
		while (p->data != INT_MAX)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
}
int main()
{
	Chain_HashTable<int> h;
	int x;
	cout << "请输入十个元素：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cin >> x;
		h.Insert(x);
	}
	cout << endl;
	cout << "删除三个元素：" << endl;
	for (int i = 0; i < 3; i++)
	{
		cin >> x;
		h.Delete(x);
	}
	h.Output();
}