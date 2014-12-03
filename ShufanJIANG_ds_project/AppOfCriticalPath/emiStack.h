#ifndef EMISTACK_H
#define EMISTACK_H

#include <iostream>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

template < class T >
class emiElem
{
public:
	T data;
	emiElem *p_next;
};

template < class T >
class emiStack
{
protected:
	int sum;//节点总数
	emiElem<T> *p_top;//指向头结点的指针
	emiElem<T> *p_base;//指向当前节点的指针
public:
	void top(T &value);//用value返回栈顶元素的值
	emiStack();
	~emiStack();
	void clear();//清空
	void pop();//弹出栈顶元素
	bool empty()const;//判断是否为空栈
	int size()const;//返回元素的个数
	void push(const T &e);//将e压栈
	void PrintAll()const;//输出栈内所有元素
};

template < class T >
emiStack< T > :: emiStack()
{
	p_base = new emiElem<T>;
	p_top = p_base;
	p_top->p_next = p_base;
	sum = 0;
}

template <class T>
void emiStack< T > :: PrintAll()const
{
	emiElem< T > *temp = p_top->p_next;
	for (int i(0); i != sum; ++i)
	{
		cout << temp->data << " ";
		temp = temp->p_next;
	}
}

template < class T >
emiStack< T > :: ~emiStack()
{
	while (sum)
		pop();
}

template <class T >
void emiStack< T > :: clear()
{
	while (sum)
		pop();
}

template < class T >
bool emiStack< T > :: empty()const
{
	if (sum)
		return 0;
	else
		return 1;
}

template < class T >
int emiStack< T > :: size()const
{
	return sum;
}

template < class T >
void emiStack< T >::top(T &value)
{
	if (sum)
		value = p_top->p_next->data;
	else
		cout << "top error: the stack is empty~" << endl;
//	cout << "hey!top" << endl;
}

template < class T >
void emiStack< T >::push(const T &e)
{
//	cout << "hey!push" << endl;
	emiElem<T> *temp = new emiElem<T>;
	temp->data = e;
	temp->p_next = p_top->p_next;
	p_top->p_next = temp;
	++sum;
}

template < class T >
void emiStack< T >::pop()
{
	if (sum)
	{
//		cout << p_top->p_next->data << endl;
		emiElem<T> *temp;
		temp = p_top->p_next->p_next;
		delete (p_top->p_next);
		p_top->p_next = temp;
		--sum;
	}
	else
		cout << "pop error: the stack is empty!" << endl;
}

#endif