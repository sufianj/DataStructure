#ifndef EMIMGRAPH_H
#define EMIMGRAPH_H
#include <string>
using namespace std;
#define MAX_VERTEX_NUM 28
typedef enum {DG, DN, UDG, UDN} GraphKind;
typedef struct MGraph
{
	string vexs[MAX_VERTEX_NUM];//����ֵΪ�ַ���
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//���ڽӾ���洢������
	int vexnum;//�����
	int arcnum;//����
	GraphKind kind;//ͼ������
}MGraph;

typedef struct closedge_node
{
	int adjvex;
	int lowcost;
}closedge_node;
#endif