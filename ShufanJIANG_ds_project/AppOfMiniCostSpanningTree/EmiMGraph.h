#ifndef EMIMGRAPH_H
#define EMIMGRAPH_H
#include <string>
using namespace std;
#define MAX_VERTEX_NUM 28
typedef enum {DG, DN, UDG, UDN} GraphKind;
typedef struct MGraph
{
	string vexs[MAX_VERTEX_NUM];//结点的值为字符串
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//用邻接矩阵存储无向网
	int vexnum;//结点数
	int arcnum;//弧数
	GraphKind kind;//图的种类
}MGraph;

typedef struct closedge_node
{
	int adjvex;
	int lowcost;
}closedge_node;
#endif