#include "stdafx.h"

#include "EmiTree.h"
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

EmiTree::EmiTree()
{
//	root = AddChild();
	ifstream input;
	input.open("input.txt", ios::in);
	int itop = 0;
	char PreO[30] = "", InO[30] = "";
	char c = input.get();
	while ('\n' != c)
	{
		PreO[itop++] = c;
		c = input.get();
//		cout << c;//test
	}
	c = input.get();
	itop = 0;
//	cout << endl;//test
	while ('\n' != c)
	{
		InO[itop++] = c;
		c = input.get();
//		cout << c;//test
	}
	if (strlen(InO) != strlen(PreO))
	{
//		cout << "前序和中序的结点个数不一致！" << endl;
		system("pause");
		exit(0);
	}
	root = CreateViaPreNIn(0, 0, strlen(InO), InO, PreO);
	input.close();
}

EmiTree::~EmiTree()
{
	DeleteChild(root);
}

tnode * EmiTree::AddChild()
{
	char c;
	tnode *p;
	cout << "请输入该节点的值，#表示空的节点" << endl;
	cin >> c;
	if ('#' != c)
	{
		p = new tnode;
		p->data = c;
		p->lp = AddChild();
		p->rp = AddChild();
		p->mark = 0;
	}
	else
		p = NULL;
	return (p);
}

bool EmiTree::PrintChild(tnode *pNode)
{
	if (NULL == pNode)
		cout << "#";
	else 
	{
		cout << pNode->data << "(";
		PrintChild(pNode->lp);
		cout << ", ";
		PrintChild(pNode->rp);
		cout << ")";
	}
	return true;
}

/*void EmiTree::PrintAll()
{
	PrintChild(root);
}*/

bool EmiTree::DeleteChild(tnode *p)
{
	if (p)
	{
		if (p->lp)
			DeleteChild(p->lp);
		if (p->rp)
			DeleteChild(p->rp);
		delete p;
	}
	return true;
}

bool EmiTree::PreOrderTraverse(tnode *pt, bool (*visit)(tnode *))
{
	if (pt)
	{
		visit(pt);
		PreOrderTraverse(pt->lp, visit);
		PreOrderTraverse(pt->rp, visit);
	}
	return true;
}

bool EmiTree::InOrderTraverse(tnode *pt, bool (*visit)(tnode *))
{
	if (pt)
	{
		InOrderTraverse(pt->lp, visit);
		visit(pt);
		InOrderTraverse(pt->rp, visit);
	}
	return true;
}

bool EmiTree::PostOrderTraverse(tnode *pt, bool (*visit)(tnode *))
{
	if (pt)
	{
		InOrderTraverse(pt->lp, visit);
		InOrderTraverse(pt->rp, visit);
		visit(pt);
	}
	return true;
}

bool PrintNode(tnode *p)
{
	cout << p->data << " "; 
	return true;
}

//DEL bool EmiTree::AddToOutput(tnode *p)
//DEL {
//DEL 	strOutput += p->data;
//DEL 	return true;
//DEL }

tnode * EmiTree::CopyTree(tnode *pfrom)
{
	tnode * pto;
	if (! pfrom)
		pto = NULL;
	else
	{
		pto = new tnode;
		if (pfrom->lp)
			pto->lp = CopyTree(pfrom->lp);
		else
			pto->lp = NULL;
		if (pfrom->rp)
			pto->rp = CopyTree(pfrom->rp);
		else
			pto->rp = NULL;
		pto->data = pfrom->data;
		pto->mark = pto->mark;
	}
	return pto;
}

bool EmiTree::LevelOrderTraverse(tnode *T, bool(*visit)(tnode *))
{
	tnode * que[30];
	tnode *p;
	if (T)
	{
		p = T;
		int f(0), t(0);
		visit(p);
		if (p->lp)
			que[t++] = p->lp;
		if (p->rp)
			que[t++] = p->rp;
		while (t > f)
		{
			p = que[f++];
			visit(p);
			if (p->lp)
				que[t++] = p->lp;
			if (p->rp)
				que[t++] = p->rp;
		}
	}
	return true;
}

/*int EmiTree::Depth(tnode *T, int n)
{
/*	static int depth;
	if (T)
	{
		Depth(T->lp, n+1);
		Depth(T->rp, n+1);
	}
	else if (n > depth)
		depth = n;
	return depth;
}*/

int EmiTree::Depth(tnode *T)
{
	int depth, n1, n2;
	if (T)
	{
		n1 = Depth(T->lp);
		n2 = Depth(T->rp);
		depth = (n1 > n2 ? n1 : n2) + 1;
	}
	else
		depth = 0;
	return depth;
}

bool EmiTree::InOrderTraverse63(tnode *T, bool(*visit)(tnode *))
{
	stack<tnode *> s;
	tnode *p;
	p = T;
	while (p || !s.empty())
	{
		if (p)
		{
			s.push(p);
			p = p->lp;
		}
		else
		{
			p = s.top();
			s.pop();
			if (!visit(p))
				return false;
			p = p->rp;
		}
	}
	return true;
}

bool EmiTree::InOrderTraverse62(tnode *T, bool(*visit)(tnode *))
{
	stack<tnode *> s;
	tnode *p;
	s.push(T);
	while (!s.empty())
	{
		while ((p = s.top()) && p)
			s.push(p->lp);
		s.pop();
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			if (!visit(p))
				return FALSE;
			s.push(p->rp);
		}
	}
	return true;
}

bool reset_mark(tnode *p)
{
	p->mark = 0;
	return true;
}

bool EmiTree::PreOrderTraverse1(tnode *T, bool(*visit)(tnode *))
{
	stack<tnode *> s;
	if (T)
	{
		tnode *p = T;
		PreOrderTraverse(p, reset_mark);
		s.push(p);
		while (!s.empty())
		{
			p = s.top();
			switch(p->mark)
			{
			case 0:
				visit(p);//先序
				++(p->mark);
				if (p->lp)
					s.push(p->lp);
				break;
			case 1:
				//visit(p);//中序
				++(p->mark);
				if (p->rp)
					s.push(p->rp);
				break;
			case 2:
				//visit(p);//后序
				s.pop();
			}
		}
	}
	return true;
}

bool EmiTree::PostOrderTraverse1(tnode *T, bool(*visit)(tnode *))
{
	stack<tnode *> s;
	if (T)
	{
		tnode *p = T;
		PreOrderTraverse(p, reset_mark);
		s.push(p);
		while (!s.empty())
		{
			p = s.top();
			switch(p->mark)
			{
			case 0:
				//visit(p);//先序
				++(p->mark);
				if (p->lp)
					s.push(p->lp);
				break;
			case 1:
				//visit(p);//中序
				++(p->mark);
				if (p->rp)
					s.push(p->rp);
				break;
			case 2:
				visit(p);//后序
				s.pop();
			}
		}
	}
	return true;
}

bool EmiTree::Prosperity(tnode *T, int &pros)
{
	pros = 0;
	LayerRecord queue[100], rnode;
	int f(0), t(0), count, l, max;
	if (T)
	{
		queue[t].p = T;
		queue[t].layer = 1;
		++t;
		while (t > f)
		{
			rnode = queue[f++];
			if (rnode.p->lp)
			{	
				queue[t].p = rnode.p->lp;
				queue[t].layer = rnode.layer + 1;
				++t;
			}
			if (rnode.p->rp)
			{
				queue[t].p = rnode.p->rp;
				queue[t].layer = rnode.layer + 1;
				++t;
			}
		}
		f = 0;
		l = queue[f].layer;
		max = count = 0;
		while (f < t)
		{
			if (l == queue[f].layer)
				++count;
			else
			{
				l = queue[f].layer;
				max = count > max ? count : max;
				count = 1;
			}
			++f;
		}
		pros = max * queue[t-1].layer;
	}
	return true;
}

bool EmiTree::ExchangeLnR(tnode *T)
{
	tnode *temp;
	if (T)
	{
		if (T->lp)
			ExchangeLnR(T->lp);
		if (T->rp)
			ExchangeLnR(T->rp);
		temp = T->lp;
		T->lp = T->rp;
		T->rp = temp;
	}
	return true;
}

bool EmiTree::IsComplete(tnode *T)
{
	bool ans = 1;
	if (T)
	{
		int dl = Depth(T->lp);
		int dr = Depth(T->rp);
		if (dl ==  dr || dl == dr + 1)
		{
			if (IsComplete(T->lp) && IsComplete(T->rp))
				ans = 1;
			else 
				ans = 0;
		}
		else
			ans = 0;
	}
	return ans;
}

int EmiTree::GetLeaveSum(tnode *T)
{
	int ans = 0;
	if (T)
	{
		if (T->lp)
			ans += GetLeaveSum(T->lp);
		if (T->rp)
			ans += GetLeaveSum(T->rp);
		if (NULL == T->lp && NULL == T->rp)
			ans = 1;
	}
	return ans;
}

tnode* EmiTree::CreateViaPreNIn(int i_pos, int p_pos, int len,
									char InO[], char PreO[])
{
	tnode *p;
	if (0 == len)
		p = NULL;
	else
	{
		int i;
		bool find = 0;
		p = new tnode;
		p->data = PreO[p_pos];
	//	cout << "EMItest" << endl;
		int b = i_pos + len;
		for (i = i_pos; i != i_pos + len; ++i)
			if (InO[i] == PreO[p_pos])
			{
				find = 1;
				break;
			}
		if (find)
		{
			if (i == i_pos)
				p->lp = NULL;
			else
				p->lp = CreateViaPreNIn(i_pos, p_pos + 1, i - i_pos, InO, PreO);
			if (i == b - 1)
				p->rp = NULL;
			else
				p->rp = CreateViaPreNIn(i + 1, p_pos + i - i_pos + 1, 
									i_pos + len - i - 1, InO, PreO);
		}
		else
		{
			cout << "please make sure your input is correct" << endl;
			system("pause");
			exit(0);
		}
	}
	return p;
}
