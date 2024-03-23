/*3.编写二叉树类的成员函数，分别实现以下功能：
①统计二叉树的叶节点的数目
②交换二叉树中所有节点的左右子树
③按层次顺序遍历二叉树：首先访问根节点，然后是它的两个孩子节点，然后是孙子节点，依此类推
④求二叉树的宽度，即同一层次上最多的节点数*/

#include<iostream>
#include<queue>
using namespace std;
//5 4 3 10 9 8 7 16 1 2
template<class T>
class BinarySearchTree;
template<class T>
class TreeNode
{
	friend BinarySearchTree<T>;
public:
	TreeNode() { LeftChild = RightChild = NULL; level = 0; }
	T data;
	TreeNode<T>* LeftChild;
	TreeNode<T>* RightChild;
	int level;
};
template<class T>
class BinarySearchTree
{
public:
	int Maxwidth;
	int leafnumber;
	int* width;
	TreeNode<T>* root;
	//
	BinarySearchTree(int m = 20, TreeNode<T>* init = 0);
	void Insert(T&);
	TreeNode<T>* Search(T&);
	void PreOrder(TreeNode<T>*);
	void Inorder(TreeNode<T>*);
	void visit(TreeNode<T>* x) { cout << x->data << " "; }
	int GetWidth() { return width; }
	int GetMaxwidth() { return Maxwidth; }
	int GetLeafNumber() { return leafnumber; }
	TreeNode<T>* Root() { return root; }
	void exchange(TreeNode<T>*);
	void Traversal();
};
template<class T>
BinarySearchTree<T>::BinarySearchTree(int m, TreeNode<T>* init)
{
	root = init;
	leafnumber = 0;
	width = new int[m + 1];
	for (int i = 1; i <= m; i++) width[i] = 0;
	Maxwidth = 0;
}
template<class T>
void BinarySearchTree<T>::Insert(T& x)
{
	if (!root)
	{
		root = new TreeNode<T>;
		root->data = x;
		root->level = 1;
		width[1] = 1;
		Maxwidth = 1;
		leafnumber++;
		return;
	}
	TreeNode<T>* q = NULL;//q为p的父节点
	TreeNode<T>* p = root;
	while (p)
	{
		if (x < p->data)
		{
			q = p;
			p = p->LeftChild;
		}
		else
		{
			q = p;
			p = p->RightChild;
		}
	}
	p = new TreeNode<T>;
	p->data = x;
	p->level = q->level + 1;
	width[p->level]++;
	Maxwidth = max(Maxwidth, width[p->level]);

	if (x < q->data)//左子节点
	{
		q->LeftChild = p;
		if (q->RightChild)leafnumber++;//+1 or 不变
	}
	else
	{
		q->RightChild = p;
		if (q->LeftChild)leafnumber++;
	}
}
template<class T>
TreeNode<T>* BinarySearchTree<T>::Search(T& x)
{
	TreeNode<T>* p = root;
	while (p)
	{
		if (p->data == x) return p;
		if (x < p->data)p = p->LeftChild;
		else p = p->RightChild;
	}
	return 0;
}
template<class T>
void BinarySearchTree<T>::PreOrder(TreeNode<T>* t)
{
	if (t)
	{
		visit(t);
		PreOrder(t->LeftChild);
		PreOrder(t->RightChild);
	}
}
template<class T>
void BinarySearchTree<T>::Inorder(TreeNode<T>* t)
{
	if (t)
	{
		Inorder(t->LeftChild);
		visit(t);
		Inorder(t->RightChild);
	}
}
template<class T>
void BinarySearchTree<T>::exchange(TreeNode<T>* t)
{
	if (t->LeftChild)exchange(t->LeftChild);
	if (t->RightChild)exchange(t->RightChild);
	TreeNode<T>* temp;
	temp = t->LeftChild;
	t->LeftChild = t->RightChild;
	t->RightChild = temp;
}

template<class T>
void BinarySearchTree<T>::Traversal()
{
	cout << "按层次遍历结果如下：" << endl;
	queue<TreeNode<T>*>que;
	que.push(root);
	while (!que.empty())
	{
		TreeNode<T>* p = que.front();
		cout << p->data << " ";
		que.pop();
		if (p->LeftChild)que.push(p->LeftChild);
		if (p->RightChild)que.push(p->RightChild);
	}
	cout << endl;
}
int main()
{
	BinarySearchTree<int> t;
	int x;
	for (int i = 0; i < 10; i++)
	{
		cin >> x;
		t.Insert(x);
	}
	cout << "leafnumber: " << t.GetLeafNumber() << endl;
	cout << "maxwidth: " << t.GetMaxwidth() << endl;
	cout << "------------------------------" << endl;
	t.Inorder(t.Root());
	cout << endl;
	cout << endl;
	t.Traversal();
	cout << "交换左右子链顺序：" << endl;
	t.exchange(t.Root());
	t.Inorder(t.Root());
}