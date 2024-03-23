#include <stack>
#include <iostream>
#include <fstream>
using namespace std;
template<class T>
class Stack;
template<class T>
class node {
	template<class TT> friend ostream& operator<<(ostream& out, const Stack<TT>& x);
	friend Stack<T>;
private:
	T data;
	node<T>* next;
};

template<class T>
class Stack {
	template<class TT> friend ostream& operator<<(ostream& out, const Stack<TT>& x);
public:
	Stack() { top = 0; length = 0; }
	bool IsEmpty()const { return length == 0; }
	bool IsFull()const { return false; }
	T Top()const;
	void Push(const T& x);
	void Pop(T& x);
private:
	int length;
	node<T>* top;
};

template<class T>
ostream& operator<<(ostream& out, const Stack<T>& x) {
	node<T>* p = x.top;
	while (p) {
		out << p->data << " ";
		p = p->next;
	}
	return out;
}

template<class T>
T Stack<T>::Top()const {
	if (IsEmpty())cout << "wrong";
	return top->data;
}

template<class T>
void Stack<T>::Push(const T& x) {
	node<T>* p = new node<T>;
	p->data = x;
	p->next = top;
	top = p;
	length++;
}

template<class T>
void Stack<T>::Pop(T& x) {
	if (IsEmpty())cout << "wrong";
	node<T>* p = top;
	top = top->next;
	x = p->data;
	delete p;
}

template <class T>
void delete_all(stack<T>& s, const T& x)
{
	if (s.empty())
	{
		cout << "Stack is empty!" << endl;
		return;
	}
	stack<T> temp;
	while (!s.empty())
	{
		if (s.top() == x)
		{
			s.pop();
		}
		else
		{
			temp.push(s.top()); s.pop();
		}
	}
	while (!temp.empty())
	{
		s.push(temp.top());
		temp.pop();
	}
}
int main()
{
	stack<char> m;
	char a, t, n;
	ifstream infile("input.txt");
	infile >> a;
	infile.get(t);
	while (infile >> n) m.push(n);
	delete_all<char>(m, a);
	while (!m.empty())
	{
		cout << m.top();
		m.pop();
		if (!m.empty())
			cout << " ";
	} cout << endl;
}