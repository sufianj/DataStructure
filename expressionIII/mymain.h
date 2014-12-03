#include "emiStack.h"
#include "mytree.h"
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int precedence(char ch);
void EvaluateExpression();
double GetVal(tNode *);
double operate(double a, char theta, double b);

double GetVal(tNode *T)
{
	if (OPERATOR == T->flag)
	{
		T->val = operate(GetVal(T->lp), T->optr, GetVal(T->rp));
	}
	return T->val;
}
int precedence(char ch)
{
	int n;
	switch(ch)
	{
	case '*':
	case '/': n = 1; break;
	case '+':
	case '-': n = 2; break;
	case '(': n = 0; break;
	case ')': n = 3; break;
	case '=': n = 4; break;
	default: n = -1; break;
	}
	return n;
}

double operate(double a, char theta, double b)
{
	double d;
	switch (theta)
	{
	case '+': d = a + b; break;
	case '-': d = a - b; break;
	case '*': d = a * b; break;
	case '/':
		if(b)
			 d = a / b;
		else
		{
			cout << "Math Error" << endl;
			exit(1);
		}
	}
	return d;
}	

void EvaluateExpression()
{
	string strtemp;
	bool bdot;
	emiStack<tNode*> OPND;
	emiStack<char> OPTR;
	char c, optrtop, ch2;
	char flag = 'y';
	tNode *a, *b;
	while ( flag == 'y')
	{
		strtemp.erase();
		OPND.clear();
		OPTR.clear();
		OPTR.push('=');
		system("cls");
		cout << "please input an expression, end with a '=' & enter "<< endl;
		c = getchar();
		OPTR.top(optrtop);
		bdot = 0;
		while (c != '\n')
		{
			if ( c <= '9' && c >= '0')
				strtemp += c;
			else if ( c == '.')
			{
				if (bdot)
				{
					cout << "u cannot have 2 dots in a double num" << endl;
					system("pause");
					exit(1);
				}
				else
					strtemp += c;
			}
			else if ( c == '+' || c == '-' || c == '*' ||\
				c == '/' || c == '(' || c == ')' || c == '=')
			{
				if (strtemp.size())
				{
					a = new tNode;
					a->optr = '=';
					a->lp = NULL;
					a->rp = NULL;
					a->flag = OPERAND;
					a->val = atof( strtemp.c_str() );
					OPND.push(a);
					bdot = 0;
					strtemp.erase();
				}
				bool flag2 = 1;//flag2用于标记c已经进操作符栈
				while (flag2)
				{				
					OPTR.top(optrtop);
					if (optrtop == '=' && c == '=')
						flag2 = 0;
					else if (optrtop == '(' && c == ')')
					{
						OPTR.pop();
						flag2 = 0;
					}
					else if (optrtop == '(')
					{
						OPTR.push(c);
						flag2 = 0;
					}
					else if ( precedence(optrtop) > precedence(c) )
					{
						OPTR.push(c);
						flag2 = 0;
					}
					else
					{
						OPND.top(a);
						OPND.pop();
						OPND.top(b);
						OPND.pop();
						OPTR.top(ch2);
						OPTR.pop();
						tNode *p = new tNode;
						p->flag = OPERATOR;
						p->lp = b;
						p->rp = a;
						p->optr = ch2;
						OPND.push(p);
					}
				}
			}
			else
			{
				cout << "expression error, u may input some illegal symbols" << endl;
			}
			c = getchar();
		}
		OPND.top(a);
		cout << "the value of your expression is "<< GetVal(a) << endl;
		cout << "Wanna evaluate another expression? [ y / n ]" << endl;
		cin >> flag;
	}
}

main()
{
	void EvaluateExpression();
	return  0;
}