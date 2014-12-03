#include <iostream>
#include <fstream>
#include <string.h>
#include "smatrix.h"
#include "EmiTree.h"

using namespace std;

main()
{
/*	SMatrix sm;
	sm.CreatMatrix();
	sm.PrintMatrix(1);
	sm.PrintMatrix(0);
	cout << endl;
	sm.TransposeMatrix();
	sm.PrintMatrix(1);
	sm.PrintMatrix(0);
	cout << endl;
	sm.TransposeMatrix();
	sm.PrintMatrix(1);
	sm.PrintMatrix(0);*/
	EmiTree T;
//	char PreO[5] = "badc";
//	char InO[5] = "adbc";
//	T.root = T.CreateViaPreNIn(0, 0, 4, InO, PreO);
/*	ofstream output;
	output.open("input.txt", ios::out);
	output << "abcdefg" << endl;
	output << "cbdafeg" << endl;
	output.close();*/
	ifstream input;
	input.open("input.txt", ios::in);
	int itop = 0;
	char PreO[30] = "", InO[30] = "";
	char c = input.get();
	while ('\n' != c)
	{
		PreO[itop++] = c;
		c = input.get();
		cout << c;//test
	}
	c = input.get();
	itop = 0;
	cout << endl;//test
	while ('\n' != c)
	{
		InO[itop++] = c;
		c = input.get();
		cout << c;//test
	}
	if (strlen(InO) != strlen(PreO))
	{
		cout << "前序和中序的结点个数不一致！" << endl;
		system("pause");
		exit(0);
	}
	T.root = T.CreateViaPreNIn(0, 0, strlen(InO), InO, PreO);
	input.close();
//	T.root = T.AddChild();
	T.PrintChild(T.root);
	cout << endl;
	T.PreOrderTraverse(T.root, PrintNode);
	cout << endl;
//	T.PostOrderTraverse(T.root, PrintNode);
//	cout << endl;
	T.InOrderTraverse(T.root, PrintNode);
	cout << endl;
//	tnode *newT = T.CopyTree(T.root);
//	T.PreOrderTraverse(newT, PrintNode);
//	cout << endl;
//	T.LevelOrderTraverse(T.root, PrintNode);
//	cout << endl;
//	cout << "your tree's depth is " << T.Depth(T.root) << endl;//从零开始求
//	T.InOrderTraverse62(T.root, PrintNode);
//	T.PreOrderTraverse1(T.root, PrintNode);
//	cout << endl;
//	int pros;
//	T.Prosperity(T.root, pros);
//	cout << pros << endl;
/*	T.ExchangeLnR(T.root);
	T.PrintChild(T.root);
	T.ExchangeLnR(T.root);
	T.PrintChild(T.root);*/
//	cout << "IsComplete?" << T.IsComplete(T.root) << endl;
//	cout << "there're " << T.GetLeaveSum(T.root) << " leaves" << endl;
	return 0;
}