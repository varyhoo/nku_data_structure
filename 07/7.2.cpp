/*
1.��ȡ�ı���
2.ͳ���ı��и�����ĸ���ֵ�Ƶ�ʣ�
3.����Huffman����
4.����Huffman���룻
5.����Huffman����ѹ���ı���
*/
#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
#include<functional>
#include<bitset>
#include<queue>
using namespace std;
class TreeNode {
private:
	char character;
	int weight;
	TreeNode* LeftChild;
	TreeNode* RightChild;
public:
	TreeNode() { LeftChild = RightChild = NULL; character = 0; }
	TreeNode(char a, int w) { weight = w; character = a; LeftChild = RightChild = NULL; }
	char GetCharacter()const { return character; }
	int GetWeight()const { return weight; }
	TreeNode* GetLeftChild()const { return LeftChild; }
	TreeNode* GetRightChild()const { return RightChild; }

	void setLeft(TreeNode* left) { LeftChild = left; }
	void setRight(TreeNode* right) { RightChild = right; }
	void setWeight(int we) { weight = we; }
	void setCharacter(char ch) { character = ch; }
};
struct cmp {
	bool operator()(TreeNode* a, TreeNode* b)const {
		return a->GetWeight() > b->GetWeight();
	}
};//ȷ��Ȩ��С����ǰ��
class HuffmanTree {
private:
	TreeNode* root;
public:
	HuffmanTree(string&);
	TreeNode* GetRoot() { return root; }
	TreeNode* MergeTreeNode(TreeNode*, TreeNode*);
};
HuffmanTree::HuffmanTree(string& s)
{
	//1.ͳ��ÿ����ĸ���ֵ�Ƶ�����ɽڵ�ѹ�����
	priority_queue<TreeNode*, vector<TreeNode*>, cmp>queue;//���ȶ���
	sort(s.begin(),s.end());
	int count = 0;
	char curcharacter = s[0];
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == curcharacter)
		{
			count++;
		}
		else {
			TreeNode* n = new TreeNode(curcharacter, count);
			queue.push(n);
			curcharacter = s[i];
			count = 1;
		}
	}
	TreeNode* n = new TreeNode(curcharacter, count);
	queue.push(n);

	//�������������������������Ĺ��̣�����ȡ����������С�������ڵ㣬�ϲ����ǣ������ϲ���Ľڵ�ѹ�ض����У�ֱ��������ֻʣһ���ڵ㡣
	while (queue.size() > 1) {
		TreeNode* node1 = queue.top();
		queue.pop();
		TreeNode* node2 = queue.top();
		queue.pop();
		TreeNode* node = MergeTreeNode(node1, node2);
		queue.push(node);
	}
	root = queue.top();
}
TreeNode* HuffmanTree::MergeTreeNode(TreeNode* left, TreeNode* right)//�����µĸ��ڵ�
{
	TreeNode* newroot = new TreeNode;
	newroot->setWeight(left->GetWeight() + right->GetWeight());
	newroot->setLeft(left);
	newroot->setRight(right);
	return newroot;
}
class HuffmanCode {
private:
	HuffmanTree* huffman_tree;
	string str;
	string filename;
	string compressedFileName;
	string HuffmanTable[1 << 8];
	/*λ���� 1 << 8����ʾ���������� 1 ���� 8 λ���ȼ��� 2 �� 8 �η���256 ��Ԫ�أ�
	�ֱ������洢 ASCII ��ֵΪ 0 �� 255 ���ַ��� Huffman ���롣*/
public:
	HuffmanCode(string Filename) { filename = Filename; for (int i = 0; i < 1 << 8; i++)HuffmanTable[i] = "-1";}
	void ReadFile();
	void GenerateCompressFile();
	void GenerateUncompressfile();
	void GenerateHuffmanTable(string ,TreeNode*);
	void OutputHuffmanTable();
};
void HuffmanCode::GenerateHuffmanTable(string huffman_code, TreeNode* n) {
	if (n->GetCharacter() != 0)
	{
		HuffmanTable[int(n->GetCharacter())] = huffman_code;
		return;
	}
	//������һ
	if (n->GetLeftChild() != 0)
	{
		GenerateHuffmanTable(huffman_code + "0", n->GetLeftChild());//�����ǰ�ڵ������������������������ַ������"0"��Ȼ��ݹ���øú������Դ�����������
	}
	if (n->GetRightChild() != 0)
	{
		GenerateHuffmanTable(huffman_code + "1", n->GetRightChild());//�����ǰ�ڵ������������������������ַ������"1"��Ȼ��ݹ���øú������Դ�����������
	}
}
void HuffmanCode::ReadFile()
{
	ifstream file(filename);
	try {
		if (!file.is_open())
		{
			throw "�Ҳ�����Ӧ·�����ļ�";
		}
	}
	catch (const char* str)
	{
		cout << str << endl;
		exit(1);
	}
	char chr;
	file.get(chr);
	while (!file.eof()) {
		str += chr;
		file.get(chr);
	}
	file.close();
}
void HuffmanCode::OutputHuffmanTable()
{
	huffman_tree = new HuffmanTree(str);
	GenerateHuffmanTable("", huffman_tree->GetRoot());
	string OutFileName = filename.substr(0, filename.length() - 4) + "_HuffmanTable.txt";
	fstream OutFileStream(OutFileName, ios::app);
	try {
		if (!OutFileStream.is_open()) {
			throw "OutFileStream not find";
		}
	}
	catch (const char* str) {
		cout << str << endl;
		exit(1);
	}

	for (int i = 0; i < 1 << 8; i++) {
		if (HuffmanTable[i] != "-1") {
			OutFileStream << (char)i << ' ' << HuffmanTable[i] << endl;
		}
	}
	OutFileStream.close();
}
void HuffmanCode::GenerateCompressFile() {
	string compressfile = filename.substr(0, filename.length() - 4) + "_CompressFile.txt";
	compressedFileName = compressfile;
	fstream inFile(filename);//�򿪴�ѹ���ļ�
	try {
		if (!inFile.is_open()) {
			throw "fail to open the file";
		}
	}
	catch (const char* str) {
		cout << str << endl;
		exit(1);
	}
	char ch;
	string codestream;//01��
	//��λ��ȡ�ļ��е��ַ������ݱ��뼯����ת��Ϊ01���洢��codestream��
	inFile.get(ch);
	while (!inFile.eof()) {
		codestream += HuffmanTable[int(ch)];
		inFile.get(ch);
	}
	inFile.close();

	fstream outFile;//��ѹ�����ļ�
	outFile.open(compressfile, ios::out | ios::binary);
	while (codestream.size() >= 8) {
		bitset<8>bits(codestream, 0, 8);//��codestream�е�ǰ8λ�����Ʊ���ת����һ��8λ�Ķ�������
		codestream.erase(0, 8);//ɾ���Ѿ������8λ�����Ʊ���
		cout << bits;
		outFile << bits;
	}
	if (!codestream.empty()) {
		unsigned long loc = codestream.size();
		bitset<8>bits(codestream, 0, loc);
		outFile << bits;//��ʣ��Ķ�������д��ѹ���ļ�
	}
	outFile.close();
}
void HuffmanCode::GenerateUncompressfile() {
	fstream compressfile(compressedFileName);
	char ch;
	string st;
	compressfile.get(ch);
	// ��ȡѹ���ļ�����
	while (!compressfile.eof()) {
		st += ch;
		compressfile.get(ch);
	}
	string res;
	TreeNode* p = huffman_tree->GetRoot();
	for (int i = 0; st[i]; i++)
	{
		// �����ǰ�ڵ�ΪҶ�ӽڵ㣬���ҵ�һ���ַ�
		if (!p->GetLeftChild() && !p->GetRightChild())
		{
			res += p->GetCharacter();
			p = huffman_tree->GetRoot();// ����Ϊ���ڵ㣬׼��������һ���ַ�
		}
		// ����ѹ���ļ��е�"0"��"1"�����ƶ�
		if (st[i] == '0') {
			p = p->GetLeftChild();
		}
		if (st[i] == '1') {
			p = p->GetRightChild();
		}
	}
	// �������һ���ַ�
	if (!p->GetLeftChild() && !p->GetRightChild()) {
		res += p->GetCharacter();
		p = huffman_tree->GetRoot();
	}
	cout << "δѹ�����ļ��ǣ�" << endl << res << endl;
}
int main()
{
	HuffmanCode huffmancode("test.txt");
	huffmancode.ReadFile();
	cout << "����ѹ���ļ���" << endl;
	huffmancode.OutputHuffmanTable();
	cout << "�ɹ���ʼ����������" << endl;
	huffmancode.GenerateCompressFile();
	cout << endl;
	huffmancode.GenerateUncompressfile();
}