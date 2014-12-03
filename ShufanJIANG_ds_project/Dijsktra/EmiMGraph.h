#ifndef EMIMGRAPH_H
#define EMIMGRAPH_H
#include <string>
using namespace std;
#define MAX_VERTEX_NUM 18
typedef enum {DG, DN, UDG, UDN} GraphKind;
typedef struct MGraph
{
	string vexs[MAX_VERTEX_NUM];//结点的值为字符串
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//用邻接矩阵存储有向网
	int vexnum;//结点数
	int arcnum;//弧数
	GraphKind kind;//图的种类
}MGraph;
typedef int* ShortPathTable;

void Dijkstra(MGraph &G, 
			  int v0,
			  int Path[MAX_VERTEX_NUM],
			  int D[MAX_VERTEX_NUM],
			  bool set[MAX_VERTEX_NUM]);

void DisplayAllPathfromV0(MGraph &G,
			 int D[MAX_VERTEX_NUM],
			 int v0,
			 int Path[MAX_VERTEX_NUM],
			 bool set[MAX_VERTEX_NUM]);
void PrintPathV0toV(int v0, int v, MGraph &G, int Path[MAX_VERTEX_NUM]);
#endif