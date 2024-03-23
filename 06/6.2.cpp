/*/2.输入一个中缀表达式，构造表达式树，以文本方式输出树结构。
输入：例如，输入a+b+c*(d+e)
输出：以缩进表示二叉树的层次，左——根、右——叶、上——右子树、下——左子树
―――――――――――――――――――
                 e
            +
                 d
        *
            c
    +
            b
        +
            a

――――――――――――――――――――――*/
#include<iostream>
#include<stack>
#include<string>
#include<queue>
using namespace std;
template<class T>
class BinaryTree;
template<class T>
class TreeNode
{
    friend BinaryTree<T>;
public:
    TreeNode<T>* leftchild, * rightchild;
    T data;
    int level;
    TreeNode() { leftchild = rightchild = NULL; level = 1; }
    TreeNode(T& x) { leftchild = rightchild = NULL; level = 1; data = x; }
    void setLeftChild(TreeNode<T>* t);
    void setRightChild(TreeNode<T>* t);
    void setLeftChild(const T&);
    void setRightChild(const T&);
    void setLevel(TreeNode<T>*);

};
template<class T>
void TreeNode<T>::setLevel(TreeNode<T>* t)
{
    if (t->leftchild)
    {
        t->leftchild->level = t->level + 1;
        setLevel(t->leftchild);
    }
    if (t->rightchild)
    {
        t->rightchild->level = t->level + 1;
        setLevel(t->rightchild);
    }
}
template<class T>
void TreeNode<T>::setLeftChild(TreeNode<T>* t)
{
    leftchild = t;
    t->level = this->level + 1;
    setLevel(t);
}
template<class T>
void TreeNode<T>::setRightChild(TreeNode<T>* t)
{
    rightchild = t;
    t->level = this->level + 1;
    setLevel(t);
}
template<class T>
void TreeNode<T>::setLeftChild(const T& x)
{
    TreeNode<T>* p = new TreeNode<T>;
    p->level = level + 1;
    p->data = x;
    leftchild = p;
}
template<class T>
void TreeNode<T>::setRightChild(const T& x)
{
    TreeNode<T>* p = new TreeNode<T>;
    p->level = level + 1;
    p->data = x;
    rightchild = p;
}
template<class T>
class BinaryTree
{
public:
    TreeNode<T>* root;
    int leafnumber;
    int height;
    BinaryTree() { root = NULL; leafnumber = 0; height = 0; }
    void setRoot(TreeNode<T>* r) { root = r; }
    void BackOrder(TreeNode<T>*);
    void visit(TreeNode<T>*);
    TreeNode<T>* getRoot() { return root; }
};
template<class T>
void BinaryTree<T>::BackOrder(TreeNode<T>* t)
{
    if (t)
    {
        BackOrder(t->rightchild);
        visit(t);
        BackOrder(t->leftchild);
    }
}
template<class T>
void BinaryTree<T>::visit(TreeNode<T>* t)
{
    for (int i = 0; i < t->level - 1; i++)cout << "  ";
    cout << t->data << endl;
}
int priority(char op)
{
    if (op == '*' || op == '/') return 1;
    else if (op == '+' || op == '-')return 0;
    else return -1;
}
void transmation(string& s) 
{
    stack<char> s1, s2;//运算符栈s1,存储中间结果栈s2
    int i = 0;
    while (s[i]) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            //常数,直接入栈s2
            s2.push(s[i++]);
        }
        else if (s[i] == '(') {
            //(,直接压入s1
            s1.push(s[i++]);
        }
        else if (s[i] == ')') {
            //),依次弹出s1栈顶元素，直到遇到'('为止
            while (s1.top() != '(') {
                s2.push(s1.top());
                s1.pop();
            }
            s1.pop();
            i++;
        }
        else {
            //当前扫描为运算符

            if (s1.empty() || s1.top() == '(') {
                //如果s1为空或栈顶运算符为'(',则直接将该运算符入栈
                s1.push(s[i++]);
            }
            else if (priority(s1.top()) < priority(s[i])) {
                //如果当前运算符比栈顶运算符优先级高,也直接入栈
                s1.push(s[i++]);
            }
            else {
                //（当前运算符优先级与栈顶运算符相同或更低）重复else块
                s2.push(s1.top());
                s1.pop();
            }
        }
    }

    //将s1剩余运算符依次弹出并压入s2
    while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
    }

    //此时s2中栈顶元素为所求后缀表达式尾
    int t = s2.size();
    s = s.substr(0, t);
    for (int i = 0; i < t; i++) {
        s[t - i - 1] = s2.top();
        s2.pop();
    }
}
int main()
{
    string s;
    cin >> s;
    transmation(s);
    cout<< s;
    stack<TreeNode<char>*>ss;
    int i = 0;
    while (s[i])
    {
        TreeNode<char>* p = new TreeNode<char>(s[i]);
        if (s[i] >= 'a' && s[i] <= 'z')//操作数->建立一个单节点树并将一个指向它的指针推入栈中
        {
            ss.push(p);
        }
        else//运算符->则从栈中弹出两棵树T1和T2(先弹出T1)并形成一颗以操作符为根的树，其中T1为右儿子，T2为左儿子
        {
            p->setRightChild(ss.top());
            ss.pop();
            p->setLeftChild(ss.top());
            ss.pop();
            ss.push(p);
        }
        i++;
    }
    cout << endl;
    BinaryTree<char> t;
    t.setRoot(ss.top());
    t.BackOrder(t.getRoot());
}