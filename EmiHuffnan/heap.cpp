#include <stdlib.h>
#include <iostream>
#include "heap.h"

using namespace std;

EmiHeap::EmiHeap()
{
	if (! (heap = (wNode *)malloc(10 * sizeof(wNode))))
	{
		cerr << "fail to malloc" << endl;
		system("pause");
		exit(0);
	}
	lenth = 10;
	sum = 0;
}

EmiHeap::~EmiHeap()
{
	free(heap);
}

int EmiHeap::add(char c)
{
	++sum;
	if (sum == lenth)
	{
		if (! (heap = (wNode *)realloc(heap, (lenth + 5) * sizeof(wNode))))
		{
			cerr << "fail to realloc" << endl;
			system("pause");
			exit(0);
		}
		lenth += 5;
	}
	heap[sum].w = 1;
	heap[sum].ch = c;
	return sum;
}

wNode& EmiHeap::operator [](int i)
{
	if (i > sum || i <= 0)
	{
		cerr << "error: i=" << i << " > sum || i <= 0!" << endl;
		system("pause");
		exit(0);
	}
	else
	{
		return heap[i];
	}
}
