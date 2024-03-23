/*
1.读取文本；
2.统计文本中各个字母出现的频率；
3.构建Huffman树；
4.构造Huffman编码；
5.根据Huffman编码压缩文本。
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
};//确保权重小的在前面
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
	//1.统计每个字母出现的频率生成节点压入队列
	priority_queue<TreeNode*, vector<TreeNode*>, cmp>queue;//优先队列
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

	//构造霍夫曼树：构造霍夫曼树的过程，不断取出队列中最小的两个节点，合并它们，并将合并后的节点压回队列中，直到队列中只剩一个节点。
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
TreeNode* HuffmanTree::MergeTreeNode(TreeNode* left, TreeNode* right)//生成新的根节点
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
	/*位运算 1 << 8，表示将二进制数 1 左移 8 位，等价于 2 的 8 次方，256 个元素，
	分别用来存储 ASCII 码值为 0 到 255 的字符的 Huffman 编码。*/
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
	//左零右一
	if (n->GetLeftChild() != 0)
	{
		GenerateHuffmanTable(huffman_code + "0", n->GetLeftChild());//如果当前节点有左子树，将哈夫曼编码字符串添加"0"，然后递归调用该函数，以处理左子树。
	}
	if (n->GetRightChild() != 0)
	{
		GenerateHuffmanTable(huffman_code + "1", n->GetRightChild());//如果当前节点有右子树，将哈夫曼编码字符串添加"1"，然后递归调用该函数，以处理右子树。
	}
}
void HuffmanCode::ReadFile()
{
	ifstream file(filename);
	try {
		if (!file.is_open())
		{
			throw "找不到对应路径的文件";
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
	fstream inFile(filename);//打开待压缩文件
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
	string codestream;//01串
	//逐位读取文件中的字符，根据编码集将其转换为01串存储在codestream中
	inFile.get(ch);
	while (!inFile.eof()) {
		codestream += HuffmanTable[int(ch)];
		inFile.get(ch);
	}
	inFile.close();

	fstream outFile;//打开压缩后文件
	outFile.open(compressfile, ios::out | ios::binary);
	while (codestream.size() >= 8) {
		bitset<8>bits(codestream, 0, 8);//将codestream中的前8位二进制编码转换成一个8位的二进制数
		codestream.erase(0, 8);//删除已经处理的8位二进制编码
		cout << bits;
		outFile << bits;
	}
	if (!codestream.empty()) {
		unsigned long loc = codestream.size();
		bitset<8>bits(codestream, 0, loc);
		outFile << bits;//将剩余的二进制数写入压缩文件
	}
	outFile.close();
}
void HuffmanCode::GenerateUncompressfile() {
	fstream compressfile(compressedFileName);
	char ch;
	string st;
	compressfile.get(ch);
	// 读取压缩文件内容
	while (!compressfile.eof()) {
		st += ch;
		compressfile.get(ch);
	}
	string res;
	TreeNode* p = huffman_tree->GetRoot();
	for (int i = 0; st[i]; i++)
	{
		// 如果当前节点为叶子节点，即找到一个字符
		if (!p->GetLeftChild() && !p->GetRightChild())
		{
			res += p->GetCharacter();
			p = huffman_tree->GetRoot();// 重置为根节点，准备解码下一个字符
		}
		// 根据压缩文件中的"0"和"1"进行移动
		if (st[i] == '0') {
			p = p->GetLeftChild();
		}
		if (st[i] == '1') {
			p = p->GetRightChild();
		}
	}
	// 处理最后一个字符
	if (!p->GetLeftChild() && !p->GetRightChild()) {
		res += p->GetCharacter();
		p = huffman_tree->GetRoot();
	}
	cout << "未压缩的文件是：" << endl << res << endl;
}
int main()
{
	HuffmanCode huffmancode("test.txt");
	huffmancode.ReadFile();
	cout << "现在压缩文件：" << endl;
	huffmancode.OutputHuffmanTable();
	cout << "成功初始化霍夫曼树" << endl;
	huffmancode.GenerateCompressFile();
	cout << endl;
	huffmancode.GenerateUncompressfile();
}