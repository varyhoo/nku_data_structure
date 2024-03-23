#include<iostream>
using namespace std;
template<class T>
class SparesMatrix;
template<class T>
class Element
{
	friend SparesMatrix<T>;
public:
	Element(int i, int j, T k);
	Element() {}
	int row, col;
	T value;
	template<class T1>
	friend ostream& operator<<(ostream&, const SparesMatrix<T1>&);
};
template<class T>
Element<T>::Element(int i, int j, T k)
{
	row = i;
	col = j;
	value = k;
}
template<class T>
class SparseMatrix
{
	template<class TT>
	friend ostream& operator<<(ostream&, const SparseMatrix<TT>&);
public:
	SparseMatrix(int max);
	SparseMatrix(int max, int col, int row);
	void Add(const SparseMatrix<T>& a, SparseMatrix<T>& b);
	void Append(const Element<T>& x);
	void display();
	void Multiplication(const SparseMatrix<T>&, SparseMatrix<T>&);
	int rows, columns;
	int element;
	Element<T>* a;
	int Max;
};
template<class T>
void SparseMatrix<T>::display()
{
	int k = 0;
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			if (i == (a+k)->row && j == (a+k)->col)
			{
				cout << (a+k)->value << " ";
				k++;
			}
			else cout << 0<<" ";
		}
		cout << endl;
	}
}
template<class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& a) {
	out << "______________________________________" << endl;
	out << "rows=" << a.rows << " columns=" << a.columns << " element= " << a.element << endl;
	for (int i = 0; i < a.element; i++)
		out << "(" << a.a[i].row << "," << a.a[i].col << ")=" << a.a[i].value << endl;

	return out;
}
template<class T>
SparseMatrix<T>::SparseMatrix(int max)
{
	if (max <= 0)cout << "WRONG";
	Max = max;
	a = new Element<T>[Max];
	element = rows = columns = 0;
}
template<class T>
SparseMatrix<T>::SparseMatrix(int max, int col, int row)
{
	if (max <= 0)cout << "WRONG";
	Max = max;
	a = new Element<T>[Max];
	element = 0;
	rows = row;
	columns = col;
}
template<class T>
void SparseMatrix<T>::Add(const SparseMatrix<T>& a, SparseMatrix<T>& b)
{
}
template<class T>
void SparseMatrix<T>::Append(const Element<T>& x)
{
	a[element++] = x;
	rows = max(x.row, rows);
	columns = max(x.col, columns);
}
template<class T>
void  SparseMatrix<T>::Multiplication(const SparseMatrix<T>& b, SparseMatrix<T>& c)//c为储存结果的矩阵
{
	if (columns != b.rows)
	{
		cout << "wrong";
		return;
	}
	c.rows = rows;
	c.columns = columns;
	c.element = 0;

	int* rownext, * rownextb;
	int* rowsize, * rowsizeb;
	rownext = new int[rows + 1];
	rownextb = new int[b.rows + 1];
	rowsize = new int[rows + 1];
	rowsizeb = new int[b.rows + 1];
	for (int i = 1; i <= rows; i++)rowsize[i] = 0;
	for (int i = 0; i < element; i++)rowsize[a[i].row]++;
	rownext[1] = 0;
	for (int i = 2; i <= rows; i++)rownext[i] = rownext[i - 1] + rowsize[i - 1];
	for (int i = 1; i <= b.rows; i++)rowsizeb[i] = 0;
	for (int i = 0; i < b.element; i++)rowsizeb[b.a[i].row]++;
	rownextb[1] = 0;
	for (int i = 2; i <= b.rows; i++)rownextb[i] = rownextb[i - 1] + rowsizeb[i - 1];
	//纸上演示 计算两个矩阵的每行中首位非零元素在数组中的位置
	T* temp = new T[b.columns + 1];
	for (int i = 1; i <= c.rows; i++)
	{
		for (int i = 0; i <= b.columns; i++)
		{
			temp[i] = 0;
		}
		int p;
		if (i < c.rows)
		{
			p = rownext[i + 1];
		}
		else p = element;
		for (int j = rownext[i]; j < p; j++)
		{
			int coll;
			if (a[j].col < b.rows)
			{
				coll = rownextb[a[j].col + 1];
			}
			else coll = b.element;
			for (int k = rownextb[a[j].col]; k < coll; k++)
			{
				int pos = b.a[k].col;
				temp[pos] += a[j].value * b.a[k].value;
			}
		}
		for (int t = 1; t <= b.columns; t++)
		{
			if (temp[t]) {
				Element<T> x;
				x.col = t, x.row = i;
				x.value = temp[t];
				c.Append(x);
			}
		}
	}
}
int main() {
	SparseMatrix<int> a(100), b(100), c(100);
	int am, an, bm, bn, element;
	cin >> am >> an >> element;
	int i, j, value;
	for (int t = 0; t < element; t++) {
		cin >> i >> j >> value;
		Element<int> x(i, j, value);
		a.Append(x);
	}
	cin >> bm >> bn >> element;
	for (int t = 0; t < element; t++) {
		cin >> i >> j >> value;
		Element<int> x(i, j, value);
		b.Append(x);
	}
	a.Multiplication(b, c);
	cout << a << b << c;
	cout << "_____________" << endl;
	a.display();
	cout << "_____________"<<endl;
	b.display();
	cout << "_____________"<<endl;
	c.display();
}