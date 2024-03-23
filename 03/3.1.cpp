﻿#include<iostream>
using namespace std;

template<class T>
class LowerTriangularMatrix {
	template<class Ta> friend ostream& operator<<(ostream& out, const LowerTriangularMatrix<Ta>& x);
public:
	LowerTriangularMatrix(int dim);
	void Store(const T& x, int i, int j);
	T Retrieve(int i, int j)const { return element[j - 1 + i * (i - 1) / 2]; }
	int GetN() { return n; }
private:
	int n;
	T* element;
};

template<class T>
ostream& operator<<(ostream& out, const LowerTriangularMatrix<T>& x) {
	for (int i = 1; i <= x.n; i++) {
		for (int j = 1; j <= x.n; j++)
			if (i >= j)out << x.Retrieve(i, j) << " ";
			else out << 0 << " ";
		cout << endl;
	}
	return out;
}

template<class T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(int dim) {
	n = dim;
	element = new T[n * (n + 1) / 2];
}

template<class T>
void LowerTriangularMatrix<T>::Store(const T& x, int i, int j) {
	element[j - 1 + i * (i - 1) / 2] = x;
}

template<class T>
class UpperTriangularMatrix {
	template<class Ta> friend ostream& operator<<(ostream& out, const UpperTriangularMatrix<Ta>& x);
	template<class TT> friend void Transposition(LowerTriangularMatrix<TT>&, UpperTriangularMatrix<TT>&);
public:
	UpperTriangularMatrix(int dim);
	void Store(const T& x, int i, int j);
	T Retrieve(int i, int j)const { return element[j - 1 + n * (i - 1) - (i - 1) * (i - 2) / 2]; }
private:
	int n;
	T* element;
};

template<class T>
ostream& operator<<(ostream& out, const UpperTriangularMatrix<T>& x) {
	for (int i = 1; i <= x.n; i++) {
		for (int j = 1; j <= x.n; j++)
			if (i <= j)out << x.Retrieve(i, j) << " ";
			else out << 0 << " ";
		cout << endl;
	}
	return out;
}

template<class T>
UpperTriangularMatrix<T>::UpperTriangularMatrix(int dim) {
	n = dim;
	element = new T[n * (n + 1) / 2];
}

template<class T>
void UpperTriangularMatrix<T>::Store(const T& x, int i, int j) {
	element[j - 1 + n * (i - 1) - (i - 1) * (i - 2) / 2] = x;
}

template<class T>
void Transposition(LowerTriangularMatrix<T>& a, UpperTriangularMatrix<T>& b) {
	int dim = a.GetN();
	b.n = dim;
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++) {
			if (j >= i)b.Store(a.Retrieve(j, i), i, j);
		}
	}
}

int main() {
	LowerTriangularMatrix<int> a(4);
	int c = 1;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			if (i >= j)
				a.Store(c++, i, j);
	UpperTriangularMatrix<int> b(4);
	Transposition(a, b);
	cout << a << endl << b;
}