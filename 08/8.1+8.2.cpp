/*
1.编写函数，计算AVL树的高度，要求说明该函数是所有算法中最优的。
2.编写函数，返回AVL树中距离根节点最近的叶节点的值。*/
#include<iostream>
using namespace std;
template<class T>
class AVLNode
{
public:
	T data;
	AVLNode<T>* left;
	AVLNode<T>* right;
	int height;
	AVLNode(const T& val) :data(val), left(nullptr), right(nullptr), height(1) {}
};
template<class T>
class AVLTree
{
public:
	AVLNode<T>* root;

	AVLTree() : root(nullptr) {}
	void insert(const T& value);
	int getHeight();
	T getNearestLeafValue();
	int height(AVLNode<T>* p);
	int balanceFactor(AVLNode<T>* p);
	AVLNode<T>* rotateRight(AVLNode<T>* y);
	AVLNode<T>* rotateLeft(AVLNode<T>* x);
	AVLNode<T>* insert(AVLNode<T>* node, const T& value);
	void destroyTree(AVLNode<T>* node);
	int findMinLeafValue(AVLNode<T>* node);
	int findNearestLeafValueHelper(AVLNode<T>* node);
};
/*如果树为空，返回一个标志值（例如-1）表示没有叶节点 
如果是叶节点，返回叶节点的值 
递归地查找左右子树中距离根节点最近的叶节点 
返回左右子树中距离根节点最近的叶节点的值*/
template<class T>
int AVLTree<T>::findNearestLeafValueHelper(AVLNode<T>* node) {
	if (node == nullptr) {
		return std::numeric_limits<T>::max();
	}

	if (node->left == nullptr && node->right == nullptr) {
		return node->data;
	}

	int leftValue = findNearestLeafValueHelper(node->left);
	int rightValue = findNearestLeafValueHelper(node->right);

	return std::min(leftValue, rightValue);
}
template<class T>
int AVLTree<T>::findMinLeafValue(AVLNode<T>* node) {
	while (node->left != nullptr) {
		node = node->left;
	}
	return node->data;
}
template<class T>
int AVLTree<T>::height(AVLNode<T>* p)
{
	if (p == nullptr)
	{
		return 0;
	}
	return p->height;
}
template<class T>
int AVLTree<T>::balanceFactor(AVLNode<T>* p)
{
	if (p == nullptr)
	{
		return 0;
	}
	return height(p->left) - height(p->right);
}
template<class T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* y)
{
	AVLNode<T>* x = y->left;
	AVLNode<T>* T2 = x->right;
	y->left = T2;
	x->right = y;
	y->height = 1 + max(height(y->left), height(y->right));
	x->height = 1 + max(height(x->left), height(x->right));
	return x;
}
template<class T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* x)
{
	AVLNode<T>* y = x->right;
	AVLNode<T>* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));

	return y;
}
template<class T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, const T& value)
{
	if (node == nullptr) {
		return new AVLNode<T>(value);
	}

	if (value < node->data) {
		node->left = insert(node->left, value);
	}
	else if (value > node->data) {
		node->right = insert(node->right, value);
	}
	else {
		return node;//树中对应的元素已经存在，直接返回就行
	}

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = balanceFactor(node);

	// Left Heavy
	if (balance > 1) {
		if (value < node->left->data) {
			return rotateRight(node);
		}
		else {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
	}

	// Right Heavy
	if (balance < -1) {
		if (value > node->right->data) {
			return rotateLeft(node);
		}
		else {
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
	}

	return node;
}
template<class T>
void AVLTree<T>::destroyTree(AVLNode<T>* node)
{
	if (node != nullptr) {
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
	}
}
template<class T>
int findMinLeafValue(AVLNode<T>* node)
{
	while (node->left != nullptr) {
		node = node->left;
	}
	return node->data;
}
template<class T>
void AVLTree<T>::insert(const T& value) {
	root = insert(root, value);
}
template<class T>
int AVLTree<T>::getHeight() {
	return height(root);
}
template<class T>
T AVLTree<T>::getNearestLeafValue() {
	if (root == nullptr) {
		throw runtime_error("Tree is empty.");
	}

	return findMinLeafValue(root);
}
int main() {
	AVLTree<int> avlTree;
	avlTree.insert(3);
	avlTree.insert(2);
	avlTree.insert(1);
	avlTree.insert(4);
	avlTree.insert(5);
	avlTree.insert(6);
	avlTree.insert(7);
	avlTree.insert(10);
	avlTree.insert(9);
	avlTree.insert(8);
	cout << "Height of AVL tree: " << avlTree.getHeight() << endl;
	cout << "Value of the nearest leaf node: " << avlTree.getNearestLeafValue() << endl;
	return 0;
}