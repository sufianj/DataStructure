#include "EmiMGraph.h"
#include <iostream>
#include <fstream>
using namespace std;
closedge_node closedge[MAX_VERTEX_NUM];
void prim(MGraph &G, int u);

main()
{
	//初始化全国省会地图
	MGraph mgraph;
	int i, j;
	ifstream input;
//	ofstream output;
	char str[10];
	mgraph.arcnum = 406;
	mgraph.vexnum = MAX_VERTEX_NUM;
	mgraph.kind = UDN;
/*	mgraph.vexs[0] = "北京";
	mgraph.vexs[1] = "天津";
	mgraph.vexs[2] = "沈阳";
	mgraph.vexs[3] = "长春";
	mgraph.vexs[4] = "哈尔滨";
	mgraph.vexs[5] = "济南";
	mgraph.vexs[6] = "合肥";
	mgraph.vexs[7] = "南京";
	mgraph.vexs[8] = "上海";
	mgraph.vexs[9] = "杭州";
	mgraph.vexs[10] = "南昌";
	mgraph.vexs[11] = "福州";
	mgraph.vexs[12] = "石家庄";
	mgraph.vexs[13] = "郑州";
	mgraph.vexs[14] = "武昌";
	mgraph.vexs[15] = "长沙";
	mgraph.vexs[16] = "广州";
	mgraph.vexs[17] = "南宁";
	mgraph.vexs[18] = "西安";
	mgraph.vexs[19] = "兰州";
	mgraph.vexs[20] = "西宁";
	mgraph.vexs[21] = "乌鲁木齐";
	mgraph.vexs[22] = "成都";
	mgraph.vexs[23] = "贵阳";
	mgraph.vexs[24] = "昆明";
	mgraph.vexs[25] = "太原";
	mgraph.vexs[26] = "呼和浩特";
	mgraph.vexs[27] = "银川";
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
	//从文件中读入省会城市之间的两两距离
	//数据每行一个
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
	cout << "请输入一个省会的代号" << endl;
	for(i = 0; i != 28; ++i)
		cout << mgraph.vexs[i] << " : " << i << endl;
	cin >> i;
	if (i >= 0 && i < 28 )
	{
		cout << "网络布线如下：" << endl;
		prim(mgraph, i);
	}
	return 0;
}

void prim(MGraph &G, int u)//因为省会交通网很稠密，所以俺选择prim算法
{
	int k = u;
	int i, j;
	//初始化辅助数组
	for (j = 0; j != G.vexnum; ++j)
	{
		closedge[j].adjvex = k;
		closedge[j].lowcost = G.arcs[k][j];
	}
	closedge[k].lowcost = 0;
	//选择其余的顶点
	for (i = 1; i != G.vexnum; ++i)
	{	//求出下一个顶点
		int flag = INT_MAX;
		for (j = 0; j != G.vexnum; ++j)
			if ((closedge[j].lowcost != 0) && (closedge[j].lowcost < flag))
			{
				k = j;
				flag = closedge[j].lowcost;
			}
			cout << G.vexs[closedge[k].adjvex] << "----" << G.arcs[k][closedge[k].adjvex]
				<< "----" << G.vexs[k] << endl;
		
		closedge[k].lowcost = 0;//k并入已选择的集合
		for (j = 0; j != G.vexnum; ++j)//更新最小边
		{
			if (G.arcs[k][j] < closedge[j].lowcost)
			{
				closedge[j].adjvex = k;
				closedge[j].lowcost = G.arcs[k][j];
			}
		}
	}
}