#include <iostream>
#include <fstream>
#include "heap.h"
using namespace std;

typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
	int val;
	char c;
}HTNode, *HTree;

typedef struct HuffmanCode
{
	bool *code;
	int len;
}hc, *HCode;

void Decode()//译码
{
	ifstream input, input2;
	int n;
	int pos[128];
	bool b;
	input2.open("output", ios::binary);
	input2.read((char *)&n, sizeof(int));
	input2.read((char *)pos, 128 * sizeof(int));
	cout << "编码结果如下: " << endl;
	input2.read((char *)&b, sizeof(bool));
	while (! input2.eof())
	{
		cout << b;
		input2.read((char *)&b, sizeof(bool));
	}
	cout << endl << "译码结果如下：" << endl;

	input.open("output", ios::binary);//读出不同的字符数n
	input.read((char *)&n, sizeof(int));//读出每个字符在树里的位置
	input.read((char *)pos, 128 * sizeof(int));
	int m = 2 * n - 1;
	HTree HT = new HTNode[m + 1];
	input.read((char *)HT, 2 * n * sizeof(HTNode)); //读出huffman树
	int p = m;
	input.read((char *)&b, sizeof(bool));
	while (! input.eof())
	{
		//cout << b;
		if (!HT[p].lchild)
		{				
			cout << HT[p].c;
			p = m;
		}
		if (b)
			p = HT[p].rchild;
		else 
			p = HT[p].lchild;
		input.read((char *)&b, sizeof(bool));
	}
	cout << endl;
	input.close();
	delete HT;
}


void HuffmanCoding(HTree &HT, HCode &HC, wNode *w, int n)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1; 
	//初始化HT
	HT = new HTNode[m + 1];
	int i, s1, s2, j;
	HT[0].weight = 0;
	HT[0].parent = 0;
	HT[0].lchild = 0;
	HT[0].rchild = 0;
	HT[0].c = '\0';
	for (i = 1; i <= n; ++i)
	{
		HT[i].weight = w[i].w;
		HT[i].c = w[i].ch;
		HT[i].parent = 0;
		HT[i].rchild = 0;
		HT[i].lchild = 0;
		HT[i].val = 0;
		HT[0].weight += w[i].w;
	}
	for (; i <= m; ++i)
	{
		HT[i].c = 'N';
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
		HT[i].lchild = 0;
		HT[i].val = 0;
	}
	for(i = n + 1; i <= m; ++i)
	{	//找出权最小的两个构建huffman树
		s1 = 0;
		s2 = 0;
		for (j = 1; j < i; ++j)
			if (HT[j].parent == 0 && HT[j].weight < HT[s1].weight)
				s1 = j;
		HT[s1].parent = i;
		HT[i].lchild = s1;
		for (j = 1; j < i; ++j)
			if (HT[j].parent == 0 && HT[j].weight < HT[s2].weight)
				s2 = j;
		HT[s2].parent = i;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
/*	//从根节点开始层序遍历哈夫曼树求每个字符的哈夫曼编码
	int p(m);
	int queue[40] = {0};
	int f(0), t(0);
	HT[p].val = 1;
	queue[t++] = p;
	int ival,l,r;
	while (f < t)
	{
		p = queue[f++];
		l = HT[p].lchild;
		r = HT[p].rchild;
		if (l != 0 && r != 0)
		{
			ival = HT[p].val << 1;//失败了，因为这样最高位不能是零，搞得每个编码都多了。
			queue[t++] = l;
			HT[l].val = ival;
			queue[t++] = r;
			HT[r].val = ival + 1;
		}
	}*/
//从根节点开始层序遍历哈夫曼树求每个字符的哈夫曼编码
	int cdlen(0), p(m);
	bool* cd = new bool[n];
	while (p)
	{
		if (0 == HT[p].val)
		{
			HT[p].val = 1;
			if (HT[p].lchild != 0)
			{
				p = HT[p].lchild;
				cd[cdlen++] = 0;
			}//if
			else if (0 == HT[p].rchild)
			{
				HC[p - 1].code = new bool[cdlen];
				for (i = 0; i < cdlen; ++i)
					HC[p - 1].code[i] = cd[i];
				HC[p - 1].len = cdlen;
			}//else if
		}//if
		else if(1 == HT[p].val)
		{
			HT[p].val = 2;
			if (HT[p].rchild != 0)
			{
				p = HT[p].rchild;
				cd[cdlen++] = 1;
			}//if
		}//else if
		else
		{
			//HT[p].weight = 0;//课本上的，可省略
			p = HT[p].parent;
			--cdlen;
		}//else
	}//while
}

void main()
{
	ifstream input, input2;
	EmiHeap WH;
	char c;
	int i;
	int pos[128] = {0};//记录每个字符的在堆中的位置
	//用堆实现求每个字符的权值
	input.open("origin.txt", ios::in);
	while (! input.eof())
	{
//		input >> c;//会忽略换行和空格，不用它
		input.get(c);
//		cout << c;
		if (pos[c])
			++(WH[pos[c]].w);
		else
			pos[c] = WH.add(c);
	}
	input.close();
	int n = WH.GetSum();
	HTree HT;
	HCode HC = new hc[n];
	HuffmanCoding(HT, HC, WH.heap, n);
	cout << "字符 " << "权值 " << "编码 " << endl;
	for (i = 1; i <= n; ++i)//输出每个字符的频数和编码
	{
		cout << HT[i].c << "    " << HT[i].weight << "    ";
		for (int j = 0; j != HC[i-1].len; ++j)
			cout << HC[i-1].code[j];
		cout << endl;
	}
	ofstream output;
	output.open("output",ios::binary);
	output.write((char*)&n, sizeof(n));//先存下有多少个不同的字符
	output.write((char *)pos, 128 * sizeof(int));//再存下每个字符在树里的位置
	output.write((char *)HT, 2 * n * sizeof(HTNode));//然后把树存起来
	//把好好的文本文件转成huffman编码的二进制文件
	input2.open("origin.txt", ios::in);
	input2.get(c);
	while (! input2.eof())
	{
		cout << c;
		if (c < 128 && c >= 0)
			if ((pos[c] - 1) >= 0)
			{
				output.write((char *)(HC[pos[c] - 1].code), HC[pos[c] - 1].len * sizeof(bool));
			}
		input2.get(c);
	}
	//退场
	input2.close();
	output.close();
	delete HT;
	for (i = 0; i != n; ++i)
		delete (HC[i].code);
	delete HC;
	Decode();//译码
}

