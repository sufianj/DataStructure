#include "EmiMGraph.h"
#include <iostream>
#include <fstream>
using namespace std;
closedge_node closedge[MAX_VERTEX_NUM];
void prim(MGraph &G, int u);

main()
{
	//��ʼ��ȫ��ʡ���ͼ
	MGraph mgraph;
	int i, j;
	ifstream input;
//	ofstream output;
	char str[10];
	mgraph.arcnum = 406;
	mgraph.vexnum = MAX_VERTEX_NUM;
	mgraph.kind = UDN;
/*	mgraph.vexs[0] = "����";
	mgraph.vexs[1] = "���";
	mgraph.vexs[2] = "����";
	mgraph.vexs[3] = "����";
	mgraph.vexs[4] = "������";
	mgraph.vexs[5] = "����";
	mgraph.vexs[6] = "�Ϸ�";
	mgraph.vexs[7] = "�Ͼ�";
	mgraph.vexs[8] = "�Ϻ�";
	mgraph.vexs[9] = "����";
	mgraph.vexs[10] = "�ϲ�";
	mgraph.vexs[11] = "����";
	mgraph.vexs[12] = "ʯ��ׯ";
	mgraph.vexs[13] = "֣��";
	mgraph.vexs[14] = "���";
	mgraph.vexs[15] = "��ɳ";
	mgraph.vexs[16] = "����";
	mgraph.vexs[17] = "����";
	mgraph.vexs[18] = "����";
	mgraph.vexs[19] = "����";
	mgraph.vexs[20] = "����";
	mgraph.vexs[21] = "��³ľ��";
	mgraph.vexs[22] = "�ɶ�";
	mgraph.vexs[23] = "����";
	mgraph.vexs[24] = "����";
	mgraph.vexs[25] = "̫ԭ";
	mgraph.vexs[26] = "���ͺ���";
	mgraph.vexs[27] = "����";
	output.open("province.txt");
	for (i = 0; i != 28; ++i)
		output << mgraph.vexs[i] << endl;
	output.close();*/
	input.open("province.txt");
	for (i = 0; i != 28; ++i)
	{
		input.getline(str, 10);
		mgraph.vexs[i] = str;
//		cout << mgraph.vexs[i] << endl;
	}
	input.close();
	//���ļ��ж���ʡ�����֮�����������
	//����ÿ��һ��
	input.open("d.txt");
	input.getline(str, 10);
	for (i = 0; i != MAX_VERTEX_NUM; ++i)
	{		
		mgraph.arcs[i][i] = 0; 
		for (j = i + 1; j != MAX_VERTEX_NUM; ++j)
		{
			mgraph.arcs[j][i] = mgraph.arcs[i][j] = atof(str);
	//		cout << mgraph.arcs[j][i] << endl;
			input.getline(str, 10);
		}
	}
	input.close();
	cout << "������һ��ʡ��Ĵ���" << endl;
	for(i = 0; i != 28; ++i)
		cout << mgraph.vexs[i] << " : " << i << endl;
	cin >> i;
	if (i >= 0 && i < 28 )
	{
		cout << "���粼�����£�" << endl;
		prim(mgraph, i);
	}
	return 0;
}

void prim(MGraph &G, int u)//��Ϊʡ�ύͨ���ܳ��ܣ����԰�ѡ��prim�㷨
{
	int k = u;
	int i, j;
	//��ʼ����������
	for (j = 0; j != G.vexnum; ++j)
	{
		closedge[j].adjvex = k;
		closedge[j].lowcost = G.arcs[k][j];
	}
	closedge[k].lowcost = 0;
	//ѡ������Ķ���
	for (i = 1; i != G.vexnum; ++i)
	{	//�����һ������
		int flag = INT_MAX;
		for (j = 0; j != G.vexnum; ++j)
			if ((closedge[j].lowcost != 0) && (closedge[j].lowcost < flag))
			{
				k = j;
				flag = closedge[j].lowcost;
			}
			cout << G.vexs[closedge[k].adjvex] << "----" << G.arcs[k][closedge[k].adjvex]
				<< "----" << G.vexs[k] << endl;
		
		closedge[k].lowcost = 0;//k������ѡ��ļ���
		for (j = 0; j != G.vexnum; ++j)//������С��
		{
			if (G.arcs[k][j] < closedge[j].lowcost)
			{
				closedge[j].adjvex = k;
				closedge[j].lowcost = G.arcs[k][j];
			}
		}
	}
}