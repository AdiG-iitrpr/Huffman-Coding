#include <bits\stdc++.h>
using namespace std;
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
void decode(Node* root, int &index, string str,string s)
{
	if (root == nullptr) {
		return;
	}
	if (!root->left && !root->right)
	{
        s.push_back(root->ch);
		cout << root->ch;
		return;
	}
	index++;
	if (str[index] =='0')
		decode(root->left, index, str,s);
	else
		decode(root->right, index, str,s);
}
int buildHuffmanTree(string text,string s)
{
	int unique=0;
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}
	unique=8*(freq.size());
	priority_queue<Node*, vector<Node*>, comp> pq;
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}
	while (pq.size() != 1)
	{
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	Node* root = pq.top();
	unordered_map<char, string> huffmanCode;
	int sum=0;int new_len=0;
	encode(root, "", huffmanCode);
	cout << "Huffman Codes with frequency count are :\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << freq[pair.first] << " " << pair.second << '\n';
		sum+=(freq[pair.first]*pair.second.length());
		new_len+=pair.second.length();
	}
	cout << "\nOriginal string was :\n" << text << '\n';
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}
	cout << "\nEncoded string is :\n" << str << '\n';
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str,s);
	}
	return sum+unique+new_len;
}
int main()
{   
	string text;
    string content;
    ifstream myfile ("input.txt");
    if(myfile.is_open()){
        while(getline(myfile,text)){
            content+=text;
            content.push_back('\n');
        }
        myfile.close();
    }
    cout<<content<<endl;
	int l=8*(content.length()-1);
    string s;
	int reduced = buildHuffmanTree(text,s);
	cout<<endl;
	cout<<"Original Message cost is "<<l<<" bytes."<<endl;
	cout<<"Cost of new reduced message is "<<reduced<<" bytes."<<endl;
	return 0;
}
