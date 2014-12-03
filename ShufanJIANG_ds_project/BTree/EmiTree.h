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
	tnode *root;//���ڵ�
	EmiTree();
	~EmiTree();
	tnode * AddChild();//�ݹ����������
	tnode * CopyTree(tnode *);//�ݹ�ظ���һ����
	tnode* CreateViaPreNIn(int i_pos, int p_pos, int len, char InO[], char PreO[]);//ͨ������������������
	bool DeleteChild(tnode *);//�ݹ��ɾ������
//	int Depth(tnode *, int);//�ݹ�������������
	int Depth(tnode *);//�ݹ�������������
	bool ExchangeLnR(tnode *);//������������
	int GetLeaveSum(tnode *);//���Ҷ�ӽڵ���
	bool InOrderTraverse63(tnode *, bool(*visit)(tnode *));//�ǵݹ��������algorithm6.2
	bool InOrderTraverse62(tnode *, bool(*visit)(tnode *));//algorithm6.3
	bool InOrderTraverse(tnode *, bool (*visit)(tnode *));//�ݹ��������
//	bool InOrderTraverse1(tnode *, bool(*visit)(tnode *));//�ǵݹ����������mark
	bool IsComplete(tnode *);//�ж��Ƿ�Ϊ��ȫ������
	bool LevelOrderTraverse(tnode *, bool(*visit)(tnode *));//�������
	bool PostOrderTraverse(tnode *, bool (*visit)(tnode *));//�ݹ�������
	bool PostOrderTraverse1(tnode *T, bool(*visit)(tnode *));//�ǵݹ���������mark
	bool PreOrderTraverse(tnode *, bool (*visit)(tnode *));//�ݹ��������
	bool PreOrderTraverse1(tnode *, bool(*visit)(tnode *));//�ǵݹ��������
	bool PrintChild(tnode *);//�ݹ���в�ε��������
	bool Prosperity(tnode *, int &);//��ï��
};

bool PrintNode(tnode *p);//һά����ʾһ����
bool reset_mark(tnode *p);//��mark��λ

typedef struct LayerRecord
{
	tnode *p;
	int layer;
}LayerRecord;

#endif