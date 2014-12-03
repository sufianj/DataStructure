#ifndef EMITREE_H
#define EMITREE_H
#include "stdafx.h"

typedef struct tnode
{
	struct tnode *lp;
	struct tnode *rp;
	int mark;
	char data;
}tnode;

class EmiTree
{
private:
//	tnode *root;
public:
	tnode *root;//根节点
	EmiTree();
	~EmiTree();
	tnode * AddChild();//递归地生成子树
	tnode * CopyTree(tnode *);//递归地复制一棵树
	tnode* CreateViaPreNIn(int i_pos, int p_pos, int len, char InO[], char PreO[]);//通过先序和中序构造二叉树
	bool DeleteChild(tnode *);//递归地删除子树
//	int Depth(tnode *, int);//递归地求子树的深度
	int Depth(tnode *);//递归地求子树的深度
	bool ExchangeLnR(tnode *);//交换左右子树
	int GetLeaveSum(tnode *);//获得叶子节点数
	bool InOrderTraverse63(tnode *, bool(*visit)(tnode *));//非递归中序遍历algorithm6.2
	bool InOrderTraverse62(tnode *, bool(*visit)(tnode *));//algorithm6.3
	bool InOrderTraverse(tnode *, bool (*visit)(tnode *));//递归中序遍历
//	bool InOrderTraverse1(tnode *, bool(*visit)(tnode *));//非递归中序遍历用mark
	bool IsComplete(tnode *);//判断是否为完全二叉树
	bool LevelOrderTraverse(tnode *, bool(*visit)(tnode *));//层序遍历
	bool PostOrderTraverse(tnode *, bool (*visit)(tnode *));//递归后序遍历
	bool PostOrderTraverse1(tnode *T, bool(*visit)(tnode *));//非递归后序遍历用mark
	bool PreOrderTraverse(tnode *, bool (*visit)(tnode *));//递归先序遍历
	bool PreOrderTraverse1(tnode *, bool(*visit)(tnode *));//非递归先序遍历
	bool PrintChild(tnode *);//递归地有层次地输出子树
	bool Prosperity(tnode *, int &);//求繁茂度
};

bool PrintNode(tnode *p);//一维地显示一棵树
bool reset_mark(tnode *p);//把mark复位

typedef struct LayerRecord
{
	tnode *p;
	int layer;
}LayerRecord;

#endif