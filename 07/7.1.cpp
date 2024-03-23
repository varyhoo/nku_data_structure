#include<iostream>
#include<limits>
using namespace std;
//�������ͨ��MaxHeap��ͨ������MinElement��MaxElement��
//ʹ���ڲ���Ԫ����ɾ�����Ԫ��ʱ�������³���ѭ���ж�������Ϊ��ǰԪ����MinElement��MaxElement�Ƚϣ�
//ʱ�临�Ӷ���ԭ�����������һ��
template<class T>
class MaxHeap {
	int CurrentSize,
		MaxSize;
	T* heap;
	T maxElement,
		minElement;
	void MergeUp(int);
	void MergeDown(int);
public:
	int HeapSize()const { return CurrentSize; }
	T Max()const { return heap[1]; }
	MaxHeap(int, T, T);
	void Initialize(T a[], int size, int ArraySize);
	void Insert(T&);
	void Top(T&);
	void Output();
};

template<class T>
void MaxHeap<T>::Output() {
	cout << endl << "the elements in this heap:" << endl;
	for (int i = 1; i <= CurrentSize; i++)cout << heap[i] << " ";
	cout << endl;
}

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize, T Max, T Min) {
	MaxSize = MaxHeapSize;
	maxElement = Max;
	minElement = Min;
	heap = new T[MaxSize * 2 + 1];
	CurrentSize = 0;
	heap[0] = Max;
	for (int i = MaxSize + 1; i < 2 * MaxSize + 1; i++)heap[i] = Min;
}

template<class T>
void MaxHeap<T>::Insert(T& x) {
	if (CurrentSize == MaxSize) {
		cout << "cannot insert a new element,cause the heap is full";
		return;
	}
	heap[++CurrentSize] = x;
	MergeUp(CurrentSize);
}

template<class T>
void MaxHeap<T>::Top(T& x) {
	if (CurrentSize == 0) {
		cout << "cannot delete the heap's max element,cause the heap is empty";
		return;
	}
	x = heap[1];
	heap[1] = heap[CurrentSize--];
	MergeDown(1);
	cout << "already delete " << x << " from the heap" << endl;
}

template<class T>
void MaxHeap<T>::MergeUp(int index) {
	int i = index;
	T x = heap[index];
	while (x > heap[i / 2]) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

template<class T>
void MaxHeap<T>::MergeDown(int index) {
	int i = index * 2;
	T x = heap[index];
	if (heap[i] < heap[i + 1])i++;
	while (x < heap[i] && i <= CurrentSize) {//�ҵ���������ȥ
		heap[i / 2] = heap[i];
		i *= 2;
		if (heap[i] < heap[i + 1])i++;
	}
	heap[i / 2] = x;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize) {
	delete[]heap;
	CurrentSize = size;
	MaxSize = ArraySize;
	heap = new T[MaxSize * 2 + 1];
	for (int i = 1; i <= CurrentSize; i++)heap[i] = a[i - 1];
	for (int i = MaxSize + 1; i < MaxSize * 2 + 1; i++)heap[i] = minElement;
	heap[0] = maxElement;

	//������
	for (int i = CurrentSize / 2; i >= 1; i--) {
		T x = heap[i];
		int c = i * 2;
		if (heap[c] < heap[c + 1])c++;
		while (x < heap[c]) {
			heap[c / 2] = heap[c];
			c *= 2;
			if (heap[c] < heap[c + 1])c++;
		}
		heap[c / 2] = x;
	}
}

int main() {
	int* p;
	int size;
	cin >> size;
	p = new int[size + 1];
	for (int i = 0; i < size; i++)
		cin >> p[i];

	int min = INT_MIN;
	int max = INT_MAX;
	MaxHeap<int> h(10, max, min);
	h.Initialize(p, size, size + 10);

	cout << endl << "now insert 2 elements" << endl;
	for (int i = 0; i < 2; i++) {
		int x;
		cin >> x;
		h.Insert(x);
	}

	h.Output();
	cout << endl << "now delete the max element from the heap" << endl;
	while (h.HeapSize()) {
		int x;
		h.Top(x);
	}
}