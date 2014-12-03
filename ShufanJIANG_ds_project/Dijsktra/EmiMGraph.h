#ifndef EMIMGRAPH_H
#define EMIMGRAPH_H
#include <string>
using namespace std;
#define MAX_VERTEX_NUM 18
typedef enum {DG, DN, UDG, UDN} GraphKind;
typedef struct MGraph
{
	string vexs[MAX_VERTEX_NUM];//����ֵΪ�ַ���
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//���ڽӾ���洢������
	int vexnum;//�����
	int arcnum;//����
	GraphKind kind;//ͼ������
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