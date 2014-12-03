//表达式求值专用二叉树
#ifndef MYTREE_H
#define MYTREE_H
#define OPERATOR 0
#define OPERAND 1

typedef struct tNode
{
	bool flag;//标记节点里的是操作数还是表达式
	double val;//节点的值
	char optr;//节点的操作符
	struct tNode *lp;//左值
	struct tNode *rp;//右值
}tNode;

void DeleteTree(tNode *T)//销毁二叉树
{
	if (T)
	{
		if (T->lp)
			DeleteTree(T->lp);
		if (T->rp)
			DeleteTree(T->rp);
		delete T;
	}
}

void PrintExpression(tNode *T)//输出表达式
{
	if (OPERAND == T->flag)
		cout << T->val;
	else
	{
		cout << "( ";
		PrintExpression(T->lp);
		cout << " " << T->optr << " ";
		PrintExpression(T->rp);
		cout << " )";
	}
}
#endif