#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include "EmiMGraph.h"
using namespace std;

main()
{
	int i, j;
	MGraph G;
	ifstream input;
	G.arcnum = 0;
	G.vexnum = MAX_VERTEX_NUM;
	int Path[MAX_VERTEX_NUM];
	int D[MAX_VERTEX_NUM];
	bool set[MAX_VERTEX_NUM];
	G.kind = DN;
	for (i = 0; i != MAX_VERTEX_NUM; ++i)
		for (j = 0; j != MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = INT_MAX;
	input.open("d.txt");
	while (!input.eof())
	{
		input >> i;
		input >> j;
		input >> G.arcs[i][j];
		++G.arcnum;
	}
	input.close();
	input.clear();
	input.open("sitename.txt");
	for (i = 0; i != MAX_VERTEX_NUM; ++i)
		input >> G.vexs[i];
	input.close();
/*	for (i = 0; i != MAX_VERTEX_NUM; ++i)
	{
		for (j = 0; j != MAX_VERTEX_NUM; ++j)
			if (INT_MAX == G.arcs[i][j])
				printf(" INF");
			else
				printf("%4d", G.arcs[i][j]);
		printf("\n");
	} // show adjMatrix*/
/*	G.arcs[0][1] = 5;
	G.arcs[0][3] = 7;
	G.arcs[1][2] = 4;
	G.arcs[2][0] = 8;
	G.arcs[2][5] = 9;
	G.arcs[3][2] = 5;
	G.arcs[3][5] = 6;
	G.arcs[4][3] = 5;
	G.arcs[5][0] = 3;
	G.arcs[5][4] = 1; test: #define max_vertex_num 6*/
	i = 0;
	while (i < 18)
	{
		system("cls");
		cout << "请输入开始景点的编号, 18为退出" << endl;
		for (i = 0; i != MAX_VERTEX_NUM; ++i)
			cout << " " << i << ". " << G.vexs[i] << "   ";
		cout << endl;
		cin >> i;
		if (i >= 0 && i < MAX_VERTEX_NUM)
			Dijkstra(G, i, Path, D, set);
		system("pause");
	}
//	for(i = 0; i != MAX_VERTEX_NUM; ++i)
//		Dijkstra(G, i, Path, D, set);
	return 0;
}

void Dijkstra(MGraph &G, 
			  int v0,
			  int Path[MAX_VERTEX_NUM],
			  int D[MAX_VERTEX_NUM],
			  bool set[MAX_VERTEX_NUM])
{
	int i, v, w, min;
	for (v = 0; v != G.vexnum; ++v)
	{
		set[v] = false;
		D[v] = G.arcs[v0][v];
			if (D[v] < INT_MAX)
				Path[v] = v0;
			else
				Path[v] = -1;
	}//for
	Path[v0] = v0;
//	D[v0] = 0;
	set[v0] = true;
	for (i = 1; i != G.vexnum; ++i)
	{
		min = INT_MAX;
		v = -1;
		for (w = 0; w < G.vexnum; ++w)
			if (!set[w] && D[w] < min && D[w] >= 0)//////////
			{
				v = w;
				min = D[w];
			}
		set[v] = true;
		for (w = 0; w != G.vexnum; ++w)
			if (!set[w]  && (G.arcs[v][w] < INT_MAX)\
				&& (min + G.arcs[v][w] < D[w]))//
			{
				D[w] = min + G.arcs[v][w];
				Path[w] = v;
			}
	}//end for
//	for(i = 0; i!= MAX_VERTEX_NUM; ++i)
//		printf("%d\n", D[i]); 
	DisplayAllPathfromV0(G, D, v0, Path, set);
}//end dijkstra

void DisplayAllPathfromV0(MGraph &G,
			 int D[MAX_VERTEX_NUM],
			 int v0,
			 int Path[MAX_VERTEX_NUM],
			 bool set[MAX_VERTEX_NUM])
{
	int i;
//	printf("all paths from %d:\n", v0);/////////
	cout << "all paths from " << G.vexs[v0] << endl;
	for (i = 0; i != G.vexnum; ++i)
		if(set[i] && v0 != i && Path[i] >= 0)
		{
//			printf("%d -> %d :\n", v0, i);///////////
//			printf("%d---", v0);///////////
			cout << G.vexs[v0] << "-……->" << G.vexs[i] << endl;
			cout << G.vexs[v0] << "---";
			PrintPathV0toV(v0, i, G, Path);
			cout << G.vexs[i] << endl;
			printf("distance: %d km\n", D[i]);
		}
		else 
//			printf("there's no path from %d to %d\n", v0, i);///////////
			cout << "there's no path from " << G.vexs[v0] << " to "
				<< G.vexs[i] << endl;
}

void PrintPathV0toV(int v0, int v, MGraph &G, int Path[MAX_VERTEX_NUM])
{
	int k = Path[v];
	if (k == v0)
	{
//		printf("%dkm---%d\n", G.arcs[k][v], v);//////////
//		cout << G.arcs[k][v] << "km--->" << G.vexs[v] << endl;
		return;
	}
	else
	{		
//		cout << G.vexs[k] << "---";
//		printf("%dkm---%d---", G.arcs[k][v], k);/////////
		PrintPathV0toV(v0, k, G, Path);
		cout << G.vexs[k] << "---";
	}
}
