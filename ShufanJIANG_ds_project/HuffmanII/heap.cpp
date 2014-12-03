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
	////adjust();
	return sum;////
}

void EmiHeap::adjust(int n, int len)
{
	wNode rc;
	int i, s = n; 
	rc.w = heap[s].w;
	rc.ch = heap[s].ch;
	for (i = s << 1; i <= sum; i <<= 1)
	{
		if (i < sum && heap[i].w < heap[i+1].w)
			++i;
		if (heap[i].w < rc.w)
			break;
		heap[s].ch = heap[i].ch;
		heap[s].w = heap[i].w;
		s = i;
	}
	heap[s].ch = rc.ch;
	heap[s].w = rc.w;
}

void EmiHeap::sortbyw(int pos[128])
{
	int i;
	wNode temp;
	for (i = sum >> 2; i != 0; --i)
		adjust(i, sum);
	for (i = sum; i > 1; --i)
	{
		temp.ch = heap[1].ch;
		temp.w = heap[1].w;
		heap[1].ch = heap[i].ch;
		heap[1].w = heap[i].w;
		heap[i].ch = temp.ch;
		heap[i].w = temp.w;
		adjust(1, i - 1);
	}
	for (i = 1; i <= sum; ++i)
		pos[heap[i].ch] = i;
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
