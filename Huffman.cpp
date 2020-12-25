/*
This contains the implementaion of a Huffman class that implements Huffman Coding
*/

#include<iostream>
#include<queue>
#include<sstream>
#include<String>
#include<vector>
using namespace std;

struct Node 
{
	Node* left;
	Node* right;
	char data;
	int freq;
};

class compareNode
{
	public :
	bool operator()(Node*a, Node*b)
	{
		return a->freq > b->freq;
	}
};

string intToBinary(int a)
{
	string ans="";
	char ch;
	int num;
	while(a!=0)
	{
		num = a%2;
		a = a/2;
		ch = '0' + num;
		ans = ch + ans;
	}
	return ans;
}

class Huffman
{
	priority_queue<Node*, vector<Node* >, compareNode> pq;
	Node *head;
	string coded_data[256];
	vector<char> alpha;
	
	void post_order(Node* top, string code)
	{
		bool leaf = true;
		//cout<<top->data<<endl;
		if (top->left!=NULL)
		{
			leaf = false;
			post_order(top->left, code+"0");
		}
		
		if(top->right!=NULL)
		{
			leaf = false;
			post_order(top->right, code+"1");
		}
		
		int pos;
		if (leaf)
		{
			pos = top->data;
			coded_data[pos] = code;
			//cout<<top->data<<"\t"<<code<<endl;
		}
	}
	
	void codeHuff()
	{
		Node *top = head;
		string code = "";
		post_order(head, code);
	}
	
	public:

		void addData(char ch, int freq)
		{
			Node *a = new Node;
			a->data = ch;
			a->freq = freq;
			a->left = NULL;
			a->right = NULL;
			
			pq.push(a);
			alpha.push_back(ch);
		}
		
		void createHuff()
		{
			Node* a;
			Node* b;
			while (pq.size()>1)
			{
				a = pq.top();
				pq.pop();
				b = pq.top();
				pq.pop();
				
				Node *temp = new Node;
				temp->left = a;
				temp->right =b;
				temp->data = '0';
				temp->freq = a->freq + b->freq;
				pq.push(temp);
			}
			
			head = pq.top();
			pq.pop();
			codeHuff();
		}

		
		string decode(string s)
		{
			int len = s.length();
			string ans = "";
			Node *top ;
			top = head;
			for (int i=0; i<len; i++)
			{
				if(s[i]=='0')
					top = top->left;
				else
					top = top->right;
				
				if (top->data!='0')
				{
					ans = ans + top->data;
					top = head;
				}
				
			}
			
			return ans;
		}
		
		string encode(string s)
		{
			string coded = "";
			int len = s.length();
			int pos;
			for(int i=0; i<len; i++)
			{
				pos = s[i];
				coded = coded + coded_data[pos];
			}
			return coded;
		}
		
		void printHuff()
		{
			for(char ch: alpha)
				cout<<ch<<"\t"<<encode(string(1,ch))<<endl;
		}
		
};

int main()
{
	int t;
	cin>>t;
	Huffman huff;
	for(int i=0; i<t; i++)
	{
		char a;
		int freq;
		cin>>a;
		cin>>freq;
		huff.addData(a,freq);
	}
	huff.createHuff();
	huff.printHuff();
	string s = huff.encode("DADABAC");
	cout<<s<<"\t"<<huff.decode(s);
	return 0;
}

/*
5
A 15
B 7
C 6
D 6
E 5
*/
