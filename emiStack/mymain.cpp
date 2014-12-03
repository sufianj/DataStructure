#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "emiStack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void ParenthesesMatch();//����ƥ��
void conversion();//��ֵת��
int precedence(char);//�������ȼ�
double operate(double a, char theta, double b);//���ؼ�����
void EvaluateExpression();//���ʽ��ֵ

/*struct pos
{
	int x;
	int y;
};*/


main()
{
//	ParenthesesMatch();
//	conversion();
	EvaluateExpression();
	system("pause");
	return 0;
}
/*
void ParenthesesMatch()
{
	char ch1, ch2;
	bool flag = 1;
	emiStack<char> char_stack;
	cout << "please input some parentheses, end by a '#'" << endl;
	ch1 = getchar();
	while ( ch1 != '#')
	{
		if ( ch1 != '(' && ch1 != ')' && ch1 != '{' && ch1 != '}'\
			&& ch1 != '[' && ch1 != ']')//��������ĺϷ���
			cout << "illegal input is not accepeted!" << endl;
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
		ch1 = getchar();
	}
	if (!char_stack.empty())//��ջ������������ƥ��
			flag = 0;
	if (flag)
		cout << "Match!" << endl;
	else
		cout << "Not match.." << endl;
}
*/
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
/*
void conversion()
{
	emiStack<int> int_stack;
	int n;
	cout << "������һ��ʮ������ "<< endl;
	cin >> n;
	while(n)
	{
		int_stack.push(n % 8);
		n /= 8;
	}
	cout << "���İ˽��Ʊ�ʾΪ: " << endl;
	while (! int_stack.empty())
	{
		int_stack.top(n);
		cout << n;
		int_stack.pop();
	}
	cout<< '\n';
}
*/
void EvaluateExpression()
{
	string strtemp;
	bool bdot;
	emiStack<double> OPND;
	emiStack<char> OPTR;
	char c, optrtop, ch2;
	char flag = 'y';
	double a, b;
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
					OPND.push( atof( strtemp.c_str() ) );
					strtemp.erase();
					bdot = 0;
				}
				bool flag2 = 1;//flag2���ڱ��c�Ѿ���������ջ
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
						OPND.push( operate(b, ch2, a) );
					}
					OPTR.PrintAll();
					OPND.PrintAll();
					cout << endl;
				}
			}
			else
			{
				cout << "expression error, u may input some illegal symbols" << endl;
			}
			c = getchar();
		}
		OPND.top(a);
		cout << "the value of your expression is "<< a << endl;
		cout << "Wanna evaluate another expression? [ y / n ]" << endl;
		cin >> flag;
		getchar();
	}
}
