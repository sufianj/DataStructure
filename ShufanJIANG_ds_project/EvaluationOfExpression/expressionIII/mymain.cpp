//041030303���淫�γ���Ƶڶ�������������
//���ʽ��ֵ���ص��ǿ�����Сѧ������ʽ����������Ȼ���ճ����貢��ǿ���ݴ�����

#include "emiStack.h"
#include "mytree.h"
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

bool check_expression(string strexp);
int precedence(char ch);
void EvaluateExpression();
double GetVal(tNode *, tNode *root);
double operate(double a, char theta, double b);

double GetVal(tNode *T, tNode *root)//��ı��ʽ����������ֵ��������ʽ����ʾ���㲽��
{
	if (OPERATOR == T->flag)
	{
		T->val = operate(GetVal(T->lp, root), T->optr, GetVal(T->rp, root));
		T->flag = OPERAND;
		cout << '=';
		PrintExpression(root);
		cout << endl;
	}
	return T->val;
}
int precedence(char ch)//��������������ȼ�
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

double operate(double a, char theta, double b)//����
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
			cout << "Math Error" << endl;//�㲻��������
			system("pause");
			exit(1);
		}
	}
	return d;
}	

bool ParenthesesMatch(string strexp)
{
	char ch1, ch2;
	int icurrent = 0;
	bool flag = 1;
	emiStack<char> char_stack;
	ch1 = strexp[icurrent];
	while ( icurrent <= strexp.size())
	{
		if ( ch1 != '(' && ch1 != ')' && ch1 != '{' && ch1 != '}'\
			&& ch1 != '[' && ch1 != ']');
		else
		{
			if (char_stack.empty())//��ջΪ�գ������Ž�ջ,�����ű�Ȼ��ƥ��
			{
				if (ch1 == '(' || ch1 == '{' || ch1 == '[')
					char_stack.push(ch1);
				else
				{
					flag = 0;
					break;
				}
			}
			else
			{
				if (ch1 == '(' || ch1 == '{' || ch1 == '[')//�����Ž�ջ����ջ��ͬ�ֵ�������
														//��ʹջ�������ŵ���
					char_stack.push(ch1);
				else
				{
					char_stack.top(ch2);
					if ( (ch2 == '(' && ch1 == ')') ||\
						(ch2 == '{' && ch1 == '}') ||\
						(ch2 == '[' && ch1 == ']'))
						char_stack.pop();
					else
					{
						flag = 0;
						break;
					}
				}
			}
		}	
		++icurrent;
		ch1 = strexp[icurrent];
	}
	if (!char_stack.empty())//��ջ������������ƥ��
			flag = 0;
	return flag;
}

bool check_expression(string strexp)//�������ĺϷ���
{
	bool flag = 1;
	bool b1, b2, b3, b4, b5, b6, b7, b8, b9;
	if (!ParenthesesMatch(strexp))
	{
		cout <<"Parentheses not match!" << endl;
		flag = 0;
	}
	else
	{
		int icurrent = 0;
		char c = strexp[icurrent];
		if ((c == '(' ||(c >= '0' && c <= '9'))\
			&& strexp[strexp.size()-2] == '=')
		{
			while (icurrent != strexp.size()-2 && flag)
			{
				if (c <= '9' && c >= '0')
				{
					b1 = (strexp[icurrent + 1] != '+');
					b2 = (strexp[icurrent + 1] != '-');
					b3 = (strexp[icurrent + 1] != '*');
					b4 = (strexp[icurrent + 1] != '/');
					b5 = (strexp[icurrent + 1] != '=');
					b6 = (strexp[icurrent + 1] != '.');
					b7 = (strexp[icurrent + 1] != ')');
					b8 = (strexp[icurrent + 1] < '0');
					b9 = (strexp[icurrent + 1] > '9');
					if (b1 && b2 && b3 && b4 && b5 && b6 && b7 && (b8 || b9))
						flag = 0;
				}
				else if('.' == c)
				{
					if (strexp[icurrent + 1] > '9'||\
						strexp[icurrent + 1] < '0')
						flag = 0;
				}
				else if ('(' == c )
				{
					b1 = (strexp[icurrent + 1] > '9');
					b2 = (strexp[icurrent + 1] < '0');
					b3 = (strexp[icurrent + 1] != '(');
					if (b3 && (b1 || b2))
						flag = 0;
				}
				else if ('+' == c || '-' == c || '*' == c || '/' == c)
				{
					if ((strexp[icurrent + 1] > '9' ||\
						strexp[icurrent + 1] < '0')&&\
						(strexp[icurrent + 1] != '('))
						flag = 0;
				}
				else if (')' == c)
				{
					b1 = (strexp[icurrent + 1] != '+');
					b2 = (strexp[icurrent + 1] != '-');
					b3 = (strexp[icurrent + 1] != '*');
					b4 = (strexp[icurrent + 1] != '/');
					b5 = (strexp[icurrent + 1] != '=');
					b6 = (strexp[icurrent + 1] != ')');
					if (b1 && b2 && b3 && b4 && b5 && b6)
						flag = 0;
				}
				else if ('=' == c)
					flag = 0;
				++icurrent;
				c = strexp[icurrent];
			}//endwhile
		}//endif
		else
			flag = 0;
	}//endelse
	return flag;
}

void EvaluateExpression()//���ʽ��ֵ
{	
	string strtemp;
	bool bdot;//��¼ÿ�����ж��ٸ�С����
	emiStack<tNode*> OPND;//�������ڵ�ջ��������������һ��������Ҳ������һ�����ʽ��
	emiStack<char> OPTR;//������ջ
	char c, optrtop, ch2;
	char flag = 'y';//��¼�û����벻�������
	tNode *a, *b;
	string strexp;
	int exp_current;
	while ( flag == 'y')
	{
		exp_current = 0;
		strexp.erase();
		strtemp.erase();
		OPND.clear();
		OPTR.clear();
		OPTR.push('=');
		system("cls");
		cout << "please input an expression, end with a '=' & enter "<< endl;//���롮=������Сѧ���ճ�
		cin >> strexp;
		strexp += '\n';
		if (check_expression(strexp))
		{
			c = strexp[exp_current];
			//c = getchar();
			OPTR.top(optrtop);
			bdot = 0;
			while (c != '\n')
			{
				if ( c <= '9' && c >= '0')
					strtemp += c;
				else if ( c == '.')
				{
					if (bdot)//ÿ�������ֻ����һ��С����
					{
						cout << "u cannot have 2 dots in a double num" << endl;
						system("pause");
						exit(1);
					}
					else
					{
						strtemp += c;
						bdot = 1;
					}
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
					bool flag2 = 1;//flag2���ڱ��c�Ѿ���������ջ
					while (flag2)//���ݵ�ǰ�����������ȼ���ջ���������ĵ����ȼ�����ֱ����ǰ��������ջ
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
						{//����һ���ڵ㲢ѹ�������ջ
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
				{//��⵽�Ƿ��ַ������Դ���
					cout << "expression error, u may input some illegal symbols" << endl;
				}
				//c = getchar();
				++exp_current;
				c = strexp[exp_current];
			}
			OPND.top(a);
			cout << endl;
			cout << "the value of your expression is " << GetVal(a, a) << endl;
			DeleteTree(a);
		}
		else
			cout << "Expression Error!" << endl;
		cout << "Wanna evaluate another expression? [ y / n ]" << endl;
		cin >> flag;
		getchar();//����'y'or'n'֮���'\n'
	}
}

main()
{
	EvaluateExpression();
	return  0;
}