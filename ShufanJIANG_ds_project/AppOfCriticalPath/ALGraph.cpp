#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include "emiStack.h"
#include "ALGraph.h"
using namespace std;

ALGraph::ALGraph():arcnum(0), vexnum(0)
{
	int i, cnt, len, vex;
	ifstream input1, input2;
/*	cout << "请输入结点总数 (<= 20)" << endl;
	cin >> vexnum;
	if (vexnum > 20 || vexnum < 0)
	{
		cerr << "illegal input!" << endl;
		system("pause");
		exit(0);
	}//end if*/
	vexnum = 10;////
	input1.open("time.txt");
	input2.open("event.txt");
	indegree = new int[vexnum];
	ve = new int[vexnum];
	vl = new int[vexnum];
	for (i = 0; i != vexnum; ++i)
		indegree[i] = 0;
	for (i = 0; i != vexnum-1; ++i)
	{
//		vertices[i].info += ('a' + i);//////////////
		input2 >> vertices[i].info;
//		cout << "请输入以结点" << i 
//			<< "为头的一条弧的权值，不能为0 :" << endl;/////////////
//		cin >> len;////////////
		input1 >> len;
		cnt = 0;
		if (0 >= len)
			vertices[i].firstarc = NULL;
		else
		{	
			++cnt;
			ArcNode *pArc = vertices[i].firstarc = new ArcNode;
//			cout << "请输入该弧弧尾结点的编号：";
//			cin >> vex;////////////////////
			input1 >> vex;
			++indegree[vex];
			pArc->adjvex = vex;
			pArc->weight = len;
//			cout << "请输入下一条以结点" << i
//				<< "为头的一条弧的权值，0表示没有弧了 :" << endl;
//			cin >> len; //////////////////////////////////////////////
			input1 >> len;
			while (len > 0 && cnt < vexnum)
			{				
				pArc->nextarc = new ArcNode;
				pArc = pArc->nextarc;
				++cnt;
//				cout << "请输入该弧弧尾结点的编号：";
//				cin >> vex;  /////////////////////////////////////////
				input1 >> vex;
				++indegree[vex];
				pArc->adjvex = vex;
				pArc->weight = len;
//				cout << "请输入下一条以结点" << i 
//					<< "为头的一条弧的权值，0表示没有弧了 :" << endl;
//				cin >> len;///////////////////////////////////////////
				input1 >> len;
			}
			pArc->nextarc = NULL;
			arcnum += cnt;
		}//end else
	}//end for
	vertices[i].firstarc = NULL;
	input2 >> vertices[i].info;
	/*for (i = 0; i != vexnum; ++i)
	{
		ArcNode *p;
		p = vertices[i].firstarc;
		while (p)
		{
			cout << "-" << p->weight << "-" << p->adjvex << "  ";
			p = p->nextarc;
		}
		cout << endl;
	}*/ // test
}

ALGraph::~ALGraph()
{
	ArcNode *p1, *p2;
	delete indegree;
	delete ve;
	delete vl;
	for (int i(0); i != vexnum; ++i)
	{
		p1 = vertices[i].firstarc;
		while (p1)
		{
			p2 = p1;
			p1 = p1->nextarc;
			delete p2;
		}//end while
	}// end for
}

bool ALGraph::TopologicalOrder(emiStack<int> &T)//T为拓扑序列顶点栈
{
	emiStack<int> S;//S为零入度顶点栈
	//Initialization
	int i, j, k, cnt = 0;
	for (i = 0; i != vexnum; ++i)
		ve[i] = 0;
	for (i = 0; i != vexnum; ++i)
		if (0 == indegree[i])
			break;//如果不break呢，就会把有多个源点的情况也搞进去
			S.push(i);
	while (! S.empty())
	{
		ArcNode *p;
		S.top(j);
		S.pop();
		T.push(j);
		++cnt;//cnt记录T栈中顶点的个数
		for (p = vertices[j].firstarc; p; p = p->nextarc)
		{
			k  = p->adjvex; 
			if ( (--indegree[k]) == 0)//入度为零的顶点入栈S
				S.push(k);
			if (ve[j] + p->weight > ve[k])//求j的直接后继k的最早发生时间
				ve[k] = ve[j] + p->weight;
		}//end for
	}// end while
	if (cnt < vexnum)//那就是说该有向网中有回路
		return false;
	else 
		return true;
	return true;
}//TopologicalPath

bool ALGraph::CriticalPath()
{
	emiStack<int> T;
	int i, j, k, dut, ee, el;
	char tag;
	string str;
	ArcNode *pArc;
	if (!TopologicalOrder(T))
	{
		cerr << "该有向网有回路！" << endl;
		system("pause");
		return false;
	}
	else
	{
		for (i = 0; i != vexnum-1 ; i++)
			vl[i] = INT_MAX;
		vl[vexnum - 1] = ve[vexnum - 1];
		while (!T.empty())
		{
			T.top(j);
			T.pop();
			for (pArc = vertices[j].firstarc; pArc; pArc = pArc->nextarc)
			{
				k = pArc->adjvex;
				dut = pArc->weight;
				if (vl[k] - dut < vl[j])
					vl[j] = vl[k] - dut;
			}//end for
		}//end while
		cout << "以下是小江做饭的流程预算， 加了*的是关键事件" << endl;
		for (j = 0; j != vexnum; ++j)//输出所有的弧，
			for (pArc = vertices[j].firstarc; pArc; pArc = pArc->nextarc)
			{
				k = pArc->adjvex;
				dut = pArc->weight;
				ee = ve[j];
				el = vl[k] - dut;
				tag = (ee == el) ? '*' : '\0';
				cout << vertices[j].info << "- " << dut << "min -> " << vertices[k].info 
					<< " 最早完成时间: 第" << ee
					<< "min  最迟完成时间: 第" << el << "min " << tag << endl;
			}                
		cout << "开始计时";
		system("pause");
		time_t t, last;
		t = last = time(NULL);
		int cnt = 0;
		while (cnt != vl[vexnum-1])
		{
			t = time(NULL);
			if (1 == difftime(t, last))
			{
				++cnt;
				cout << "第 " << cnt << " min"<<endl;
				for (j = 0; j != vexnum; ++j)//输出所有的弧，
					for (pArc = vertices[j].firstarc; pArc; pArc = pArc->nextarc)
					{
						k = pArc->adjvex;
						dut	= pArc->weight;
						ee = ve[j];
						el = vl[k] - dut;
						if ((ee == cnt) && (ee == el))
						cout << "Tips:该" << vertices[j].info << "啦" << endl;
					}
				last = t;
			}//end if
		}//end while
		return true;
	}//end else
}//CriticalPath
//当出现多个汇点时要出错的。