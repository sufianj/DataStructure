//���ʽ��ֵר�ö�����
#ifndef MYTREE_H
#define MYTREE_H
#define OPERATOR 0
#define OPERAND 1

typedef struct tNode
{
	bool flag;//��ǽڵ�����ǲ��������Ǳ��ʽ
	double val;//�ڵ��ֵ
	char optr;//�ڵ�Ĳ�����
	struct tNode *lp;//��ֵ
	struct tNode *rp;//��ֵ
}tNode;

void DeleteTree(tNode *T)//���ٶ�����
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

void PrintExpression(tNode *T)//������ʽ
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