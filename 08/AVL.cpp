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
	T getClosestLeafValue(AVLNode<T>* root) {
		// 如果树为空，返回一个标志值（例如-1）表示没有叶节点
		if (root == nullptr) {
			return -1;
		}

		// 如果是叶节点，返回叶节点的值
		if (root->left == nullptr && root->right == nullptr) {
			return root->data;
		}

		// 递归地查找左右子树中距离根节点最近的叶节点
		int leftClosest = getClosestLeafValue(root->left);
		int rightClosest = getClosestLeafValue(root->right);

		// 返回左右子树中距离根节点最近的叶节点的值
		if (leftClosest != -1 && rightClosest != -1) {
			return std::min(leftClosest, rightClosest);
		}
		else if (leftClosest != -1) {
			return leftClosest;
		}
		else {
			return rightClosest;
		}
	}
	T getNearest();
	AVLNode<T>* findNearestLeafWithMinHeight(AVLNode<T>* node);
};
template<class T>
AVLNode<T>* AVLTree<T>::findNearestLeafWithMinHeight(AVLNode<T>* node) {
	if (node == nullptr) {
		return nullptr;
	}

	if (node->left == nullptr && node->right == nullptr) {
		return node;
	}

	AVLNode<T>* leftNearest = findNearestLeafWithMinHeight(node->left);
	AVLNode<T>* rightNearest = findNearestLeafWithMinHeight(node->right);

	if (leftNearest == nullptr) {
		return rightNearest;
	}
	else if (rightNearest == nullptr) {
		return leftNearest;
	}

	return (leftNearest->height <= rightNearest->height) ? leftNearest : rightNearest;
}
template<class T>
T AVLTree<T>::getNearest()
{
	if (root == nullptr) {
		throw runtime_error("树为空。");
	}

	AVLNode<T>* nearestLeaf = findNearestLeafWithMinHeight(root);
	return nearestLeaf->data;
}
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
		// Duplicate values are not allowed in this example
		return node;
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

	// Insert elements into the AVL tree
	avlTree.insert(2);
	avlTree.insert(1);
	avlTree.insert(0);
	avlTree.insert(3);
	avlTree.insert(4);
	avlTree.insert(5);
	avlTree.insert(6);
	avlTree.insert(9);
	avlTree.insert(8);
	avlTree.insert(7);
	// Calculate and print the height of the AVL tree
	cout << "Height of AVL tree: " << avlTree.getHeight() << endl;

	// Find and print the value of the nearest leaf node
	cout << "Value of the nearest leaf node: " << avlTree.getNearestLeafValue() << endl;
	int closestLeafValue = avlTree.getClosestLeafValue(avlTree.root);
	cout << closestLeafValue;
	cout<<avlTree.getNearest();
	return 0;
}