#include<iostream>
using namespace std;
template<class T>
class LinkedMatrix;
template<class T>
class HeadNode;
template<class T>
class Chain;
template<class T>
class Node {
	friend Chain<T>;
public:
	Node<T>* next;
	T value;
};
template<class T>
class Chain
{
public:
	Chain() { first = last = 0; }
	void Append(const T&);
	void clear() { first = last = 0; }
	Node<T>* first, * last;
};
template<class T>
class CNode {
	friend LinkedMatrix<T>;
	template<class TT> friend istream& operator>>(istream&, const CNode<TT>);
	template<class Ta> friend ostream& operator<< (ostream&, const LinkedMatrix<Ta>&);
public:
	CNode(T val, int c) { value = val, col = c; }
	CNode() {}
	bool operator!=(const CNode<T>& y) { return value != y.value; }
	void Output(ostream& out) { out << col << " " << value; }
	CNode<T>& operator=(const CNode<T>&);
	//private:
public:
	int col;
	T value;
};
template<class T>
class HeadNode
{
	friend LinkedMatrix<T>;
	template<class TT> friend istream& operator>>(istream&, LinkedMatrix<TT>&);
	template<class Ta>friend ostream& operator<<(ostream&, const LinkedMatrix<Ta>&);
public:
	int row;
	Chain<CNode<T>>r;
};
template<class T>
class LinkedMatrix
{
	template<class Ta> friend ostream& operator<< (ostream&, const LinkedMatrix<Ta>&);
	template<class TT> friend istream& operator>> (istream&, LinkedMatrix<TT>&);
public:
	LinkedMatrix() { rows = cols = elements = 0; }
	LinkedMatrix<T>operator+(const LinkedMatrix<T>&);
	LinkedMatrix<T>operator-(const LinkedMatrix<T>&);
	void Multiplication(const LinkedMatrix<T>&, LinkedMatrix<T>&);
	int rows, cols, elements;
	Chain<HeadNode<T>>c;
	void display();
};
template<class T>
istream& operator>>(istream& in, const CNode<T>x)
{
	in >> x.col >> x.value;
	return in;
}
template<class T>
CNode<T>& CNode<T>::operator=(const CNode<T>& x)
{
	this->col = x.col;
	this->value = x.value;
	return *this;
}
template<class T>
void Chain<T>::Append(const T& x)
{
	Node<T>* p = new Node<T>;
	p->value = x;
	p->next = NULL;
	if (first != NULL)
	{
		last->next = p;
		last = p;
	}
	else {
		first = last = p;
	}
}
template<class T>
ostream& operator<<(ostream& out, const LinkedMatrix<T>& x) {
	Node<HeadNode<T>>* current = x.c.first;
	while (current) {
		Node<CNode<T>>* curr = current->value.r.first;
		while (curr)
		{
			out << "row:" << current->value.row << " column:" << curr->value.col << " value:" << curr->value.value << endl;
			curr = curr->next;
		}
		current = current->next;
	}
	return out;
}
template<class T>
istream& operator>>(istream& in, LinkedMatrix<T>& x)
{
	cout << "请输入行数和列数：";
		in >> x.rows >> x.cols;
	cout << "请输入矩阵中非零元素的个数:";
	in >> x.elements;
	HeadNode<T> H;
	H.row = 0;
	int row, col, rownow = 0;
	T val;
	for (int i = 0; i < x.elements; i++)
	{
		cout << "输入元素对应的行数、列数和值：";
		in >> row >> col >> val;
		if (row != H.row)
		{
			if (H.row)
			{
				x.c.Append(H);
			}
			H.row = row;
			H.r.clear();
		}
		CNode<T> p(val, col);
		H.r.Append(p);
	}
	if (H.row)
	{
		x.c.Append(H);
	}
	return in;
}
template<class T>
LinkedMatrix<T> LinkedMatrix<T>::operator+(const LinkedMatrix<T>& x) {
	LinkedMatrix<T> res;
	res.rows = max(this->rows, x.rows);
	res.cols = max(this->rows, x.rows);
	Node<HeadNode<T>>* p, * q;
	p = this->c.first;
	q = x.c.first;
	while (q && p)
	{
		int indt = p->value.row, indx = q->value.row;
		if (indt == indx) {//如果是同一行
			HeadNode<T> H;
			H.row = indt;
			Node<CNode<T>>* pp, * qq;
			pp = p->value.r.first;
			qq = q->value.r.first;
			while (pp && qq)
			{
				int indtt = pp->value.col;
				int indxx = qq->value.col;
				if (indtt == indxx)
				{
					if (pp->value.value + qq->value.value)
					{
						CNode<T> n(pp->value.value + qq->value.value, indtt);
						H.r.Append(n);
						res.elements++;
					}
					pp = pp->next;
					qq = qq->next;
				}
				else if (indtt < indxx)
				{
					CNode<T>n(pp->value.value, indtt);
					H.r.Append(n);
					res.elements++;
					pp = pp->next;
				}
				else
				{
					CNode<T> n(qq->value.value, indxx);
					H.r.Append(n);
					res.elements++;
					qq = qq->next;
				}
			}
			while (pp)
			{
				int indtt = pp->value.col;
				CNode<T> n(pp->value.value, indtt);
				H.r.Append(n);
				res.elements++;
				pp = pp->next;
			}
			while (qq)
			{
				int indtt = qq->value.col;
				CNode<T> n(qq->value.value, indtt);
				H.r.Append(n);
				qq = qq->next;
			}
			res.c.Append(H);
			q = q->next;
			p = p->next;
		}
		else if (indt < indx)
		{
			HeadNode<T> H;
			H.row = indt;
			Node<CNode<T>>* pp;
			pp = p->value.r.first;
			while (pp)
			{
				int indtt = pp->value.col;
				CNode<T> n(pp->value.value, indtt);
				H.r.Append(n);
				res.elements++;
				pp = pp->next;
			}
			res.c.Append(H);
			p = p->next;
		}
		else
		{
			HeadNode<T> H;
			H.row = indx;
			Node<CNode<T>>* qq;
			qq = q->value.r.first;
			while (qq) {
				int indtt = qq->value.col;
				CNode<T> n(qq->value.value, indtt);
				H.r.Append(n);
				res.elements++;
				qq = qq->next;
			}
			res.c.Append(H);
			q = q->next;
		}
	}
		while (p) {
			HeadNode<T> H;
			H.row = p->value.row;
			Node<CNode<T>>* pp = p->value.r.first;
			while (pp) {
				int indtt = pp->value.col;
				CNode<T> n(pp->value.value, indtt);
				H.r.Append(n);
				res.elements++;
				pp = pp->next;
			}
			res.c.Append(H);
			p = p->next;
		}
		while (q) {
			HeadNode<T> H;
			H.row = q->value.row;
			Node<CNode<T>>* pp = q->value.r.first;
			while (pp) {
				int indtt = pp->value.col;
				CNode<T> n(pp->value.value, indtt);
				H.r.Append(n);
				res.elements++;
				pp = pp->next;
			}
			res.c.Append(H);
			q = q->next;
		}
		return res;
}
template<class T>
LinkedMatrix<T> LinkedMatrix<T>::operator-(const LinkedMatrix<T>& x) {
	LinkedMatrix<T> res;
	res.rows = max(this->rows, x.rows);
	res.cols = max(this->rows, x.rows);
	Node<HeadNode<T>>* p, * q;
	p = this->c.first;
	q = x.c.first;
	while (q && p)
	{
		int indt = p->value.row, indx = q->value.row;
		if (indt == indx) {//如果是同一行
			HeadNode<T> H;
			H.row = indt;
			Node<CNode<T>>* pp, * qq;
			pp = p->value.r.first;
			qq = q->value.r.first;
			while (pp && qq)
			{
				int indtt = pp->value.col;
				int indxx = qq->value.col;
				if (indtt == indxx)
				{
					if (pp->value.value - qq->value.value)
					{
						CNode<T> n(pp->value.value + qq->value.value, indtt);
						H.r.Append(n);
						res.elements++;
					}
					pp = pp->next;
					qq = qq->next;
				}
				else if (indtt < indxx)
				{
					CNode<T>n(pp->value.value, indtt);
					H.r.Append(n);
					res.elements++;
					pp = pp->next;
				}
				else
				{
					CNode<T> n(-(qq->value.value), indxx);
					H.r.Append(n);
					res.elements++;
					qq = qq->next;
				}
			}
			while (pp)
			{
				int indtt = pp->value.col;
				CNode<T> n(pp->value.value, indtt);
				H.r.Append(n);
				res.elements++;
				pp = pp->next;
			}
			while (qq)
			{
				int indtt = qq->value.col;
				CNode<T> n(-(qq->value.value), indtt);
				H.r.Append(n);
				qq = qq->next;
			}
			res.c.Append(H);
			q = q->next;
			p = p->next;
		}
		else if (indt < indx)
		{
			HeadNode<T> H;
			H.row = indt;
			Node<CNode<T>>* pp;
			pp = p->value.r.first;
			while (pp)
			{
				int indtt = pp->value.col;
				CNode<T> n(pp->value.value, indtt);
				H.r.Append(n);
				res.elements++;
				pp = pp->next;
			}
			res.c.Append(H);
			p = p->next;
		}
		else
		{
			HeadNode<T> H;
			H.row = indx;
			Node<CNode<T>>* qq;
			qq = q->value.r.first;
			while (qq) {
				int indtt = qq->value.col;
				CNode<T> n(-(qq->value.value), indtt);
				H.r.Append(n);
				res.elements++;
				qq = qq->next;
			}
			res.c.Append(H);
			q = q->next;
		}
	}
	while (p) {
		HeadNode<T> H;
		H.row = p->value.row;
		Node<CNode<T>>* pp = p->value.r.first;
		while (pp) {
			int indtt = pp->value.col;
			CNode<T> n(pp->value.value, indtt);
			H.r.Append(n);
			res.elements++;
			pp = pp->next;
		}
		res.c.Append(H);
		p = p->next;
	}
	while (q) {
		HeadNode<T> H;
		H.row = q->value.row;
		Node<CNode<T>>* pp = q->value.r.first;
		while (pp) {
			int indtt = pp->value.col;
			CNode<T> n(-(pp->value.value), indtt);
			H.r.Append(n);
			res.elements++;
			pp = pp->next;
		}
		res.c.Append(H);
		q = q->next;
	}
	return res;
}
template<class T>
void LinkedMatrix<T>::Multiplication(const LinkedMatrix<T>& x, LinkedMatrix<T>& res) {
	Node<HeadNode<T>>* p = this->c.first;
	HeadNode<T> H;
	while (p) {
		H.row = p->value.row;
		T* temp = new T[x.cols + 1];
		for (int i = 1; i <= x.cols; i++)temp[i] = 0;
		Node<CNode<T>>* q = p->value.r.first;
		while (q) {
			int col = q->value.col;
			Node<HeadNode<T>>* px = x.c.first;
			while (px && px->value.row <= col) {
				if (px->value.row == col) {
					Node<CNode<T>>* qx = px->value.r.first;
					while (qx) {
						temp[qx->value.col] += q->value.value * qx->value.value;
						qx = qx->next;
					}
				}
				px = px->next;
			}
			q = q->next;
		}
		for (int i = 1; i <= x.cols; i++) {
			if (temp[i]) {
				CNode<T> n(temp[i], i);
				H.r.Append(n);
			}
		}
		res.c.Append(H);
		H.r.clear();
		p = p->next;
	}
}
int main() {
	LinkedMatrix<int> a, b, c, d;
	cin >> a >> b;
	c = a + b;
	cout << "-----------------a+b:-----------------";
	cout << endl;
	cout << c;
	cout << endl;
	c = a - b;
	cout << "-----------------a-b-----------------";
	cout << endl;
	cout << c;
	cout << endl;
	a.Multiplication(b, d);
	cout << "-----------------a*b-----------------";
	cout << endl;
	cout << d;
	cout << endl;
}

