//���һ����redBlackTree�����ڳ�����bSTree����д���к�������
//find��insert��delete��ʱ�临�Ӷȱ�����O��logn��
//ascend��ʱ�临�Ӷ�Ӧ����O��n��
#include<iostream>
#include<fstream>
#include<iomanip>
#include<limits>
using namespace std;
template<class T>
class RedBlackNode
{
public:
	T data;//�洢��ֵ
	int color;//�Լ�����ɫ����1��0
	RedBlackNode<T>* LeftChild;//����
	RedBlackNode<T>* RightCild;//�Һ���
	RedBlackNode<T>* parent;//���׽ڵ�
	RedBlackNode(int col, T DATA, RedBlackNode<T>* left = nullptr, RedBlackNode<T>* right = nullptr, RedBlackNode<T>* pa = nullptr)
	{
		color = col;
		data = DATA;
		LeftChild = left;
		RightCild = right;
		parent = pa;
	}
};
template<class T>
class RedBlackTree
{
private:
	RedBlackNode<T>* root;//���ڵ�

public:
	//Ĭ�Ϲ��캯��
	RedBlackTree()
	{
		root = nullptr;
	}
	RedBlackNode<T>* getRoot()
	{
		return root;
	}
	//���ҹؼ���Ϊkey�����Բ��ҷ���
	//�ҵ��˾ͷ���������ԣ����򷵻�nullptr
	//������BST��ͬ
	RedBlackNode<T>* find(T key)
	{
		RedBlackNode<T>* p = this->root;
		while (p)
		{
			if (key < p->data)
			{
				//��Ҫ���ҵ�ֵС��Ŀǰֵ����ȥ����
				p = p->LeftChild;
			}
			else if (key > p->data)
			{
				//������ȥ�Һ���
				p = p->RightCild;
			}
			else
			{
				//������ҵ��ˣ������伴��
				return p;
			}
		}
		//������е�����˵��û�ҵ�
		return nullptr;
	}
	//��������
	void Insert(T key)
	{
		RedBlackNode<T>* leaf = new RedBlackNode<T>((T)INT_MAX, 1);
		//���ж����ֵ�Ƿ��Ѿ�����
		RedBlackNode<T>* p = root;
		RedBlackNode<T>* parent_of_p = nullptr;
		while (p)
		{
			parent_of_p = p;//��¼��ǰλ��
			if (key < p->data)
			{
				p = p->LeftChild;
			}
			else
			{
				p = p->RightCild;
			}

		}
		//��ʱp��ֵ��Ϊ���봦
		//�½ڵ�����Ϊ��ɫ
		RedBlackNode<T>* r = new RedBlackNode<T>(0, key);
		if (root != nullptr)
		{
			//�������Ϊ��
			if (key < parent_of_p->data)
			{
				//С�������������
				parent_of_p->LeftChild = r;
				r->parent = parent_of_p;
			}
			else
			{
				//���������������
				parent_of_p->RightCild = r;
				r->parent = parent_of_p;
			}
			//����Ϊ�ڵ�Ĳ��룬������Ӧ���ж��Ƿ����������ߵ����
			RedBlackNode<T>* pu, * gu, * uncle, * curr;
			curr = r;//ָ�����ڵĽڵ�
			//���������ϸı�temp��ʵ�����ϱ���
			while ((pu = curr->parent) && pu->color == 0)
			{
				//���ڵ������Ϊ��ɫ
				//�������������
				//��uncleָ���游�ڵ����һ������
				gu = pu->parent;
				if (gu->LeftChild == pu)
				{
					uncle = gu->RightCild;
				}
				else
				{
					uncle = gu->LeftChild;
				}
				//���游��һ�����ӵ���ɫ
				if (uncle && uncle->color == 0)
				{
					//�游��һ������Ҳ�Ǻ�ɫ
					//ֱ�ӱ�ɫ
					gu->color = 0;
					pu->color = 1;
					uncle->color = 1;
					curr = gu;
				}
				else
				{
					//�游��һ�������Ǻ�ɫ�򲻴���
					if (curr == pu->LeftChild && pu == gu->LeftChild)
					{
						//LLr
						curr = LLr(gu);
						curr = gu;
					}
					else if (curr == pu->RightCild && pu == gu->LeftChild)
					{
						//LRr
						LRr(gu);
						curr = gu;
					}
					else if (curr == pu->LeftChild && pu == gu->RightCild)
					{
						//RLr
						RLr(gu);
						curr = gu;
					}
					else if (curr == pu->RightCild && pu == gu->RightCild)
					{
						//RRr
						RRr(gu);
						curr = gu;
					}
					//temp = gu;
				}
			}
			root->color = 1;
		}
		else
		{
			//��Ϊ�գ��赱ǰ�ڵ�Ϊ��
			root = r;
			root->color = 1;//���ڵ�����ɫ
			//�����жϻ�������ת�����
		}
	}
	RedBlackNode<T>* LLr(RedBlackNode<T>* gu)
	{
		RedBlackNode<T>* pu = gu->LeftChild;
		RedBlackNode<T>* u = pu->LeftChild;
		gu->LeftChild = pu->RightCild;
		if (pu->RightCild != nullptr)
		{
			pu->RightCild->parent = gu;
		}
		pu->parent = gu->parent;
		if (gu->parent == nullptr)
		{
			root = pu;
		}
		else
		{
			if (gu == gu->parent->LeftChild)
				gu->parent->LeftChild = pu;
			else
				gu->parent->RightCild = pu;
		}
		pu->RightCild = gu;
		gu->parent = pu;
		//�޸���ɫ
		gu->color = 0;
		pu->color = 1;
		return pu;
	}
	RedBlackNode<T>* LRr(RedBlackNode<T>* gu)
	{
		RedBlackNode<T>* pu = gu->LeftChild;
		RedBlackNode<T>* u = pu->RightCild;
		u->parent = gu->parent;
		if (gu->parent == nullptr)
		{
			//��gu�Ǹ��ڵ�ʱ
			root = u;
		}
		else
		{
			if (gu == gu->parent->LeftChild)
				gu->parent->LeftChild = u;
			else
				gu->parent->RightCild = u;
		}
		//pu->RightCild = nullptr;
		pu->RightCild = u->LeftChild;
		if (u->LeftChild)
			u->LeftChild->parent = pu;
		//gu->LeftChild = nullptr;
		gu->LeftChild = u->RightCild;
		if (u->RightCild)
			u->RightCild->parent = gu;
		u->LeftChild = pu;
		pu->parent = u;
		u->RightCild = gu;
		gu->parent = u;
		//�޸���ɫ
		u->color = 1;
		gu->color = 0;
		return u;
	}
	RedBlackNode<T>* RLr(RedBlackNode<T>* gu)
	{
		RedBlackNode<T>* pu = gu->RightCild;
		RedBlackNode<T>* u = pu->LeftChild;
		u->parent = gu->parent;
		if (gu->parent == nullptr)
		{
			//˵��guΪ��
			root = u;
		}
		else
		{
			if (gu == gu->parent->LeftChild)
				gu->parent->LeftChild = u;
			else
				gu->parent->RightCild = u;
		}
		gu->RightCild = u->LeftChild;
		if (u->LeftChild)
			u->LeftChild->parent = gu;
		pu->LeftChild = u->RightCild;
		if (u->RightCild)
			u->RightCild->parent = pu;
		u->LeftChild = gu;
		gu->parent = u;
		u->RightCild = pu;
		pu->parent = u;
		//����ɫ
		u->color = 1;
		gu->color = 0;
		return u;
	}
	RedBlackNode<T>* RRr(RedBlackNode<T>* gu)
	{
		RedBlackNode<T>* pu = gu->RightCild;
		RedBlackNode<T>* u = pu->RightCild;
		pu->parent = gu->parent;
		if (gu->parent == nullptr)
		{
			root = pu;
		}
		else
		{
			if (gu == gu->parent->LeftChild)
				gu->parent->LeftChild = pu;
			else
				gu->parent->RightCild = pu;
		}
		gu->RightCild = pu->LeftChild;
		if (pu->LeftChild)
		{
			pu->LeftChild->parent = gu;
		}
		pu->LeftChild = gu;
		gu->parent = pu;
		//����ɫ
		gu->color = 0;
		pu->color = 1;
		return pu;
	}
	//ɾ���ؼ���Ϊkey����
	void Delete(T key)
	{
		//����find������λ���ýڵ�
		RedBlackNode<T>* node = find(key);
		int color;
		if (node == nullptr)
		{
			cout << "�����ڴ˽ڵ㣡" << endl;
			return;
		}
		//�жϸýڵ����
		//ɾ���ڵ�����������
		if (node->LeftChild && node->RightCild)
		{
			//Ѱ�Ҹýڵ�ĺ�̽ڵ�
			RedBlackNode<T>* replace = node;
			replace = node->LeftChild;
			while (replace->RightCild)
				replace = replace->RightCild;
			//�ٽ���̽ڵ�ֵ������Ҫɾ����ֵ��ת��Ϊ2
			if (node->parent == nullptr)//ɾ���ڵ��Ǹ��ڵ�
			{
				root = replace;
			}
			else//ɾ���ڵ㲻�Ǹ��ڵ�
			{
				//����������ϵ
				if (node == node->parent->LeftChild)
				{
					node->parent->LeftChild = replace;
				}
				else
				{
					node->parent->RightCild = replace;
				}
			}
			//��replace�����ӸĹ�ϵ
			//��̽ڵ�û���Һ���
			RedBlackNode<T>* child = replace->LeftChild;
			RedBlackNode<T>* parent = replace->parent;
			//����replace����ɫ֮�����ж�
			//��Ϊ��ת��Ϊɾ��replace
			color = replace->color;
			if (parent == node)
			{
				//��ɾ���ڵ��Ǻ�̽ڵ�ĸ��ڵ�
				//��parent��Ȼָ���Լ�
				parent = replace;
			}
			else
			{
				//��replace�ĺ���ת�Ƹ�replace�ĸ��ڵ�
				//parent->LeftChild = child;
				parent->RightCild = child;
				if (child)
					child->parent = parent;
				replace->LeftChild = node->LeftChild;
				replace->LeftChild->parent = replace;
			}
			//��node�Ĺ�ϵת��replace
			replace->parent = node->parent;
			replace->color = node->color;
			replace->RightCild = node->RightCild;
			node->RightCild->parent = replace;



			//����Ϊɾ���������������ж��Ƿ���Ҫ����
			if (color == 1)
			{
				//ɾ���ڵ��Ǻ�ɫ��
				DeleteChange(child, parent);
			}
			delete node;
			return;
		}
		//��ɾ���ڵ�ֻ��һ������ʱ
		else if (node->LeftChild != nullptr || node->RightCild != nullptr)
		{
			//��node�ĺ��ӽڵ�ȡ�����Լ�����
			RedBlackNode<T>* child, * parent;
			if (node->LeftChild)
				child = node->LeftChild;
			else
				child = node->RightCild;
			parent = node->parent;
			color = node->color;

			if (child)
				child->parent = parent;
			if (parent)
			{
				//˵�����Ǹ��ڵ�
				if (node == parent->LeftChild)
					parent->LeftChild = child;
				else
					parent->RightCild = child;

			}
			else
			{
				//�Ǹ��ڵ�
				root = child;
			}
			if (color == 1)
				DeleteChange(child, parent);
			delete node;
		}
		//��û�к���
		else
		{
			RedBlackNode<T>* parent = node->parent;
			color = node->color;
			if (parent)
			{
				//���Ǹ��ڵ�
				if (node == parent->LeftChild)
					parent->LeftChild = nullptr;
				else
					parent->RightCild = nullptr;
			}
			else
			{
				//�Ǹ��ڵ�
				root = nullptr;
			}
			if (color == 1)
				DeleteChange(nullptr, parent);
			delete node;
		}

	}
/*
�������ӵ������
��� other �� parent ���Һ��ӣ��� other ����ɫ�Ǻ�ɫ����ʾ������ Lr �͵������
���� other �����Һ��ӵ���ɫ������ֱ������Ӧ����ת����ɫ������
�����Һ��ӵ������
��� other �� parent �����ӣ��� other ����ɫ�Ǻ�ɫ����ʾ������ Rr �͵������
���� other �����Һ��ӵ���ɫ������ֱ������Ӧ����ת����ɫ������
ѭ�������󣬶�ɾ���Ľڵ������ɫ������ȷ������ɫΪ��ɫ��
*/
	//���AVL��ɾ������
	void DeleteChange(RedBlackNode<T>* node, RedBlackNode<T>* parent)
	{
		RedBlackNode<T>* other;
		while ((!node || node->color == 1) && node != root)
		{
			//��Ϊnode�����Ӻ��Һ����������
			if (parent->LeftChild == node)
			{
				//node��parent������
				other = parent->RightCild;
				//��һ�����Ӻ�ɫ
				//��otherһ���������ڲ��ĺ�ɫ�ڵ㺢��
				if (other->color == 0)
				{
					//Lr��
					//Lr0��
					if (other->LeftChild->color == 1 && other->RightCild->color == 1)
					{
						other->color = 1;
						other->LeftChild->color = 0;
						leftRotate(parent);
						//ת��֮��������ƽ��

					}
					//Lr1.1
					else if (other->LeftChild->RightCild->color == 0)
					{
						other->LeftChild->RightCild->color = 1;
						rightRotate(other);
						leftRotate(parent);
						//ƽ��

					}
					//Lr1.2
					else if (other->LeftChild->LeftChild->color == 0)
					{
						other->LeftChild->LeftChild->color = 1;
						rightRotate(other->LeftChild);
						rightRotate(other);
						leftRotate(parent);
					}
					//LR2
					else
					{
						//��LR1.2��תһ��
						other->LeftChild->LeftChild->color = 1;
						rightRotate(other->LeftChild);
						rightRotate(other);
						leftRotate(parent);
					}
					//���������������ͨ��һ����ת���ƽ��
					break;
				}
				else
				{
					//Lb��
					//��һ�����Ӻ�ɫ���������ĺ�����ɫ״�� ��Ϊ�������
					//Lb0
					if ((!other->LeftChild || other->LeftChild->color == 1) && (!other->RightCild || other->RightCild->color == 1))
					{
						//��¼һ��parentԭ������ɫ���ж��Ƿ����
						int color = parent->color;
						//ֱ�ӱ�ɫ
						parent->color = 1;
						other->color = 0;
						//ԭ���Ǻ�ɫ�����ƽ��
						if (color == 0)
							break;
						else
							node = parent;
					}
					//Lb1.1
					else if (other->LeftChild && other->LeftChild->color == 0)
					{
						other->LeftChild->color = parent->color;
						parent->color = 1;
						rightRotate(other);
						leftRotate(parent);
						break;
					}
					//Lb1.2
					else if (other->RightCild && other->RightCild->color == 0)
					{
						other->color = parent->color;
						parent->color = 1;
						other->RightCild->color = 1;
						leftRotate(parent);
						break;
					}
					//Lb2
					else
					{
						other->LeftChild->color = parent->color;
						parent->color = 1;
						rightRotate(other);
						leftRotate(parent);
						break;
					}
				}
			}
			else
			{
				//node��parent���Һ���
				other = parent->LeftChild;
				//��һ���Ӻ�ɫ
				if (other && other->color == 0)
				{
					//Rr0
					//otherһ����������ɫ�ڲ��ڵ㺢��
					if (other->LeftChild->color == 1 && other->RightCild->color == 1)
					{
						other->color = 1;
						other->RightCild->color = 0;
						rightRotate(parent);
					}
					//Rr1.1
					else if (other->RightCild->LeftChild->color == 0)
					{
						other->RightCild->LeftChild->color = 1;
						leftRotate(other);
						rightRotate(parent);
					}
					//Rr1.2
					else if (other->RightCild->RightCild->color == 0)
					{
						other->RightCild->RightCild->color = 1;
						leftRotate(other->RightCild);
						leftRotate(other);
						rightRotate(parent);

					}
					//Rr2������Rr1.2һ��
					else
					{
						other->RightCild->RightCild->color = 1;
						leftRotate(other->RightCild);
						leftRotate(other);
						rightRotate(parent);
					}
					//����Rr������ض�ƽ��
					break;
				}
				else
				{
					//Rb��
					//Rb0;
					if ((!other->LeftChild || other->LeftChild->color == 1) && (!other->RightCild || other->RightCild->color == 1))
					{
						int color = parent->color;
						parent->color = 1;
						other->color = 0;
						if (color == 0)
							break;
						else
						{
							node = parent;
						}
					}
					//Rb1.1
					else if (other->LeftChild && other->LeftChild->color == 0)
					{
						other->color = parent->color;
						parent->color = 1;
						other->LeftChild->color = 1;
						rightRotate(parent);
						break;
					}
					//Rb1.2
					else if (other->RightCild && other->RightCild->color == 0)
					{
						other->RightCild->color = parent->color;
						parent->color = 1;
						leftRotate(other);
						rightRotate(parent);
						break;
					}
					//Rb2
					else
					{
						other->RightCild->color = parent->color;
						parent->color = 1;
						leftRotate(other);
						rightRotate(parent);
						break;
					}
				}
			}
		}
		if (node)
			node->color = 1;
	}
	void leftRotate(RedBlackNode<T>* x)
	{
		//��x���Һ�����y
		RedBlackNode<T>* y = x->RightCild;
		//��y��������Ϊx���Һ���
		x->RightCild = y->LeftChild;
		if (y->LeftChild)
			y->LeftChild->parent = x;
		//��x�ĸ�������Ϊy�ĸ���
		y->parent = x->parent;
		if (x->parent == nullptr)
		{
			//�Ǹ�
			root = y;
		}
		else
		{
			if (x == x->parent->LeftChild)
				x->parent->LeftChild = y;
			else
				x->parent->RightCild = y;
		}
		//�ٽ�x��Ϊy������
		y->LeftChild = x;
		x->parent = y;
	}
	void rightRotate(RedBlackNode<T>* y)
	{
		//��x��y������
		RedBlackNode<T>* x = y->LeftChild;
		//x���Һ�������Ϊy������
		y->LeftChild = x->RightCild;
		if (x->RightCild)
			x->RightCild->parent = y;
		//y����Ϊx�ĸ���
		x->parent = y->parent;
		if (y->parent == nullptr)
			root = x;
		else
		{
			if (y == y->parent->LeftChild)
				y->parent->LeftChild = x;
			else
				y->parent->RightCild = x;

		}
		//��y���x���Һ���
		x->RightCild = y;
		y->parent = x;
	}
	//���ؼ����������
	void ascend(RedBlackNode<T>* temp)
	{
		//���������LVR���������
		if (temp->LeftChild)
			ascend(temp->LeftChild);
		if (temp)
			cout << setw(5) << temp->data;
		if (temp->RightCild)
			ascend(temp->RightCild);
	}
	void print(RedBlackNode<T>* temp, int height)
	{
		if (temp != nullptr)
		{
			print(temp->RightCild, height + 1);
			cout << setw((long int)8 * height) << " ";

			string color;
			if (temp->color == 0)
				color = "redfrom";
			else
			{
				color = "blackfrom";
			}
			cout << temp->data << color;
			if (temp->parent)
				cout << temp->parent->data;
			cout << endl;
			print(temp->LeftChild, height + 1);
		}
	}
};
int main()
{
	RedBlackTree<int> RBT;
	ifstream infile;
	infile.open("input1.txt");
	int temp;
	RedBlackNode<int>* _root = RBT.getRoot();
	for (int i = 0; i < 20; i++)
	{
		infile >> temp;
		cout << temp << " ";
		RBT.Insert(temp);
		_root = RBT.getRoot();
	}
	cout << "����������Ϊ��" << endl;
	RBT.print(_root, 0);
	cout << "ɾ��4��������Ϊ��" << endl;
	RBT.Delete(4);
	_root = RBT.getRoot();
	RBT.print(_root, 0);
	cout << "ɾ��7��������Ϊ��" << endl;
	RBT.Delete(7);
	_root = RBT.getRoot();
	RBT.print(_root, 0);
	cout << endl << "ascend����Ϊ:" << endl;
	RBT.ascend(_root);
}