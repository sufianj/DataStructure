#include <iostream>
#include <stdlib.h>
#include "haxiTable.h"

using std::cout;
using std::endl;

haxiTable::haxiTable()
{
	for(int i(0); i != 101; ++i)
	{
		a[i].n = -1;
		a[i].p_next = NULL;
	}
}

haxiTable::~haxiTable()
{
	struct em *p_em;
	for (int i(0); i != 101; ++i)
	{
		p_current = &a[i];
		while (NULL != p_current->p_next)
		{
			p_em = p_current->p_next->p_next;
			delete p_current->p_next;
			p_current->p_next = p_em;
		}
	} 
}

void haxiTable::print_all()
{
	int j;
	cout << "print all elements!" << endl;
	for (int i(0); i != 101; ++i)
	{
		p_current = &a[i];
		while (NULL != p_current->p_next)
		{
			j = i + 101 * (p_current->p_next->n);
			cout << j << "  ";
			p_current = p_current->p_next;
		}
	}
}

void haxiTable::add_em(int x)
{
	int j, k;
	bool bflag(1);
	k = x % 101;
	j = x / 101;
	p_current = &a[k];
	while (NULL != p_current->p_next)
	{
		if (j == p_current->p_next->n)
		{
			bflag = 0;
			break;
		}
		p_current = p_current->p_next;
	}
	if (bflag)
	{
		p_current->p_next = new (struct em);
		p_current->p_next->n = j;
		p_current->p_next->p_next = NULL;
	}
}