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
/*	cout << "������������ (<= 20)" << endl;
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
//		cout << "�������Խ��" << i 
//			<< "Ϊͷ��һ������Ȩֵ������Ϊ0 :" << endl;/////////////
//		cin >> len;////////////
		input1 >> len;
		cnt = 0;
		if (0 >= len)
			vertices[i].firstarc = NULL;
		else
		{	
			++cnt;
			ArcNode *pArc = vertices[i].firstarc = new ArcNode;
//			cout << "������û���β���ı�ţ�";
//			cin >> vex;////////////////////
			input1 >> vex;
			++indegree[vex];
			pArc->adjvex = vex;
			pArc->weight = len;
//			cout << "��������һ���Խ��" << i
//				<< "Ϊͷ��һ������Ȩֵ��0��ʾû�л��� :" << endl;
//			cin >> len; //////////////////////////////////////////////
			input1 >> len;
			while (len > 0 && cnt < vexnum)
			{				
				pArc->nextarc = new ArcNode;
				pArc = pArc->nextarc;
				++cnt;
//				cout << "������û���β���ı�ţ�";
//				cin >> vex;  /////////////////////////////////////////
				input1 >> vex;
				++indegree[vex];
				pArc->adjvex = vex;
				pArc->weight = len;
//				cout << "��������һ���Խ��" << i 
//					<< "Ϊͷ��һ������Ȩֵ��0��ʾû�л��� :" << endl;
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

bool ALGraph::TopologicalOrder(emiStack<int> &T)//TΪ�������ж���ջ
{
	emiStack<int> S;//SΪ����ȶ���ջ
	//Initialization
	int i, j, k, cnt = 0;
	for (i = 0; i != vexnum; ++i)
		ve[i] = 0;
	for (i = 0; i != vexnum; ++i)
		if (0 == indegree[i])
			break;//�����break�أ��ͻ���ж��Դ������Ҳ���ȥ
			S.push(i);
	while (! S.empty())
	{
		ArcNode *p;
		S.top(j);
		S.pop();
		T.push(j);
		++cnt;//cnt��¼Tջ�ж���ĸ���
		for (p = vertices[j].firstarc; p; p = p->nextarc)
		{
			k  = p->adjvex; 
			if ( (--indegree[k]) == 0)//���Ϊ��Ķ�����ջS
				S.push(k);
			if (ve[j] + p->weight > ve[k])//��j��ֱ�Ӻ��k�����緢��ʱ��
				ve[k] = ve[j] + p->weight;
		}//end for
	}// end while
	if (cnt < vexnum)//�Ǿ���˵�����������л�·
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
		cerr << "���������л�·��" << endl;
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
		cout << "������С������������Ԥ�㣬 ����*���ǹؼ��¼�" << endl;
		for (j = 0; j != vexnum; ++j)//������еĻ���
			for (pArc = vertices[j].firstarc; pArc; pArc = pArc->nextarc)
			{
				k = pArc->adjvex;
				dut = pArc->weight;
				ee = ve[j];
				el = vl[k] - dut;
				tag = (ee == el) ? '*' : '\0';
				cout << vertices[j].info << "- " << dut << "min -> " << vertices[k].info 
					<< " �������ʱ��: ��" << ee
					<< "min  ������ʱ��: ��" << el << "min " << tag << endl;
			}                
		cout << "��ʼ��ʱ";
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
				cout << "�� " << cnt << " min"<<endl;
				for (j = 0; j != vexnum; ++j)//������еĻ���
					for (pArc = vertices[j].firstarc; pArc; pArc = pArc->nextarc)
					{
						k = pArc->adjvex;
						dut	= pArc->weight;
						ee = ve[j];
						el = vl[k] - dut;
						if ((ee == cnt) && (ee == el))
						cout << "Tips:��" << vertices[j].info << "��" << endl;
					}
				last = t;
			}//end if
		}//end while
		return true;
	}//end else
}//CriticalPath
//�����ֶ�����ʱҪ����ġ�