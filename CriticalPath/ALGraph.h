#ifndef ALGRAPH_H
#define ALGRAPH_H
#define MAX_VERTEX_NUM 20
#include <string>
#include "emiStack.h"
using namespace std;

typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	int weight;
}ArcNode;

typedef struct VNode
{
	string info;
	ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

class ALGraph
{
public:
	AdjList vertices;
	int *ve;
	int *vl;
	int vexnum;
	int arcnum;
	int *indegree;
	ALGraph();
	~ALGraph();
	bool TopologicalOrder(emiStack<int> &T);
	bool CriticalPath();
};

#endif