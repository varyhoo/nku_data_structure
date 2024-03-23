#include<iostream>
#include<vector>
using namespace std;

class HashTable {
public:
	HashTable(int div = 23);
	bool Search(const int&);
	void Insert(const int&, const int&);
	void Delete(const int&, const int&);
	void Output();
private:
	const int NONE = -123456789;//预设值
	bool* NeverUsed;
	int* ht;//存key
	int* hv;//存value
	int divisor;//最大值
	int used;//存有元素的计数
	int Hash(const int& x)const { return x % divisor; }
	void Reset(int);//重新分配
};
HashTable::HashTable(int div)
{
	divisor = div;
	ht = new int[div];
	hv = new int[div];
	NeverUsed = new bool[div];
	used = 0;
	for (int i = 0; i < divisor; i++)
	{
		NeverUsed[i] = true;
	}
}
void HashTable::Insert(const int& x, const int& v)
{
	int h = Hash(x);
	int count = 0;
	while (!NeverUsed[h] && count < divisor)
	{
		if (v == hv[h])
		{
			cout << "repeat" << endl;
			return;
		}
		h = (h + 1) % divisor;
		count++;
	}
	try {
		if (NeverUsed[h])
		{
			hv[h] = v;
			ht[h] = x;
			used++;
			NeverUsed[h] = false;
			cout << x << "已经存入表中" << endl;
			if (float(used) / float(divisor) > 0.6)
			{
				cout << "*****************************************************" << endl;
				cout << "哈希表中存入的元素个数已达总容量的60%\n现重建新的哈希表";
				cout << endl << endl; Output();
				cout << endl << endl;
				Reset(divisor * 3);
				cout << endl << endl;
				Output();
				cout << endl << endl;
				return;
			}
		}
	}
	catch (const char* str)
	{
		cout << str << endl;
		return;
	}
}
void HashTable::Delete(const int& x, const int& v)
{
	int h = Hash(x);
	int count = 0;
	try {
		while (!NeverUsed[h] && count < divisor)
		{
			if (ht[h] == x)
			{
				used--;
				ht[h] = NONE;
				cout << "已经删除了" << x << endl;;
				return;
			}
			h = (h + 1) % divisor;
			throw"元素不存在无法删除";
		}
	}
	catch (const char* str)
	{
		cout << str << endl;
		return;
	}
}
bool HashTable::Search(const int& x)
{
	int h = Hash(x);
	while (!NeverUsed[h])
	{
		if (ht[h] == x)
		{
			return true;
		}
		h = (h + 1) % divisor;
	}
	return false;
}
void HashTable::Reset(int x)
{
	vector<int>vec;
	vector<int>vec1;
	for (int i = 0; i < divisor; i++)
	{
		if (!NeverUsed[i] && ht[i] != NONE)
		{
			vec.push_back(ht[i]);
			vec1.push_back(hv[i]);
		}
	}
	divisor = x;
	ht = new int[divisor];
	hv = new int[divisor];
	NeverUsed = new bool[divisor];
	used = 0;
	for (int i = 0; i < divisor; i++)
	{
		NeverUsed[i] = true;
	}
	cout << endl << "重建的哈希表最大容量为" << divisor << endl;
	for (int i = 0; i <= vec.size() - 1; i++)
	{
		Insert(vec[i], vec1[i]);
	}
}
void HashTable::Output()
{
	cout << "哈希表中存入的元素有:" << endl;
	for (int i = 0; i < divisor; i++)
	{
		if (!NeverUsed[i] && ht[i] != NONE)
		{
			if (!NeverUsed[i] && ht[i] != NONE)
			{
				cout << "f(key)=" << i << " key:" << ht[i] << "    value:" << hv[i] << endl;
			}
		}
	}
}
int main()

{
	cout << "存入10个数:";
	HashTable t;
	int x;
	int y;
	for (int i = 0; i < 10; i++)
	{
		cin >> x >> y;
		t.Insert(x, y);
	}
	cout << "删除3个数";
	for (int i = 0; i < 3; i++)
	{
		cin >> x;
		t.Delete(x, y);
	}
	cout << "再次存入10个数据：";
	for (int i = 0; i < 9; i++)
	{
		cin >> x >> y;
		t.Insert(x, y);
	}
	cout << endl;
	t.Output();
}