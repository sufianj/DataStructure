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
	int sum;//�ڵ�����
	emiElem<T> *p_top;//ָ��ͷ����ָ��
	emiElem<T> *p_base;//ָ��ǰ�ڵ��ָ��
public:
	void top(T &value);//��value����ջ��Ԫ�ص�ֵ
	emiStack();
	~emiStack();
	void clear();//���
	void pop();//����ջ��Ԫ��
	bool empty()const;//�ж��Ƿ�Ϊ��ջ
	int size()const;//����Ԫ�صĸ���
	void push(const T &e);//��eѹջ
	void PrintAll()const;//���ջ������Ԫ��
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