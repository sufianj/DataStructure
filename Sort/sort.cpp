#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include "sort.h"

using namespace std;

int b[LEN];
int a[LEN];
int c[LEN];
int bucket[10][LEN];//基数排序用的桶 要全局变量才能开那么大的空间
int bstr[LEN][5];//把b搞成数组，bstr[i][1]表示b[i]元素的十位上的数
int ord[LEN];//数组b里元素位置的映射

void main()
{
	int i, length;
/*	ofstream output;//文件input.txt里有3000个随机的整数，每个数占一行
	output.open("input.txt");
	srand( (unsigned)time( NULL ) );
	for (i = 0; i != LEN; ++i )
	{
		a[i] = rand();
		output << a[i] << endl;
//		printf("%d\n", a[i]);
	}
	output.close();*/
	ifstream input;
	input.open("input.txt");
	i = 0;
	input >> a[i];
	while (!input.eof())
	{
		++i;
		input >> a[i];
	}
	length = 7;
	printf ("先输出length = %d 的情况证明算法的正确性: \n", length);
	for (i = 0; i != length; ++i)
		printf("%8d", a[i]);
	printf("\n");
	printf("*******original data********\n");
	RadixSort(length);
	for (i = 0; i != length; ++i)
		printf("%8d", b[ord[i]]);
	printf("\n");
	modelc("HeapSort", length, HeapSort_c);
	for (i = 1; i <= length; ++i)
		printf("%8d", c[i]);
	printf("\n");
	Modelb("FastBubbleSort", length, FastBubbleSort_b);
	for (i = 0; i != length; ++i)
		printf("%8d", b[i]);
	printf("\n");
	modelc("BInsertSort", length, BInsertSort_c);
	for (i = 1; i <= length; ++i)
		printf("%8d", c[i]);
	printf("\n");
	modelc("QuickSort", length, QuickSort_c);
	for (i = 1; i <= length; ++i)
		printf("%8d", c[i]);
	printf("\n");
	modelc("InsertSort", length, InsertSort_c);
	for (i = 1; i <= length; ++i)
		printf("%8d", c[i]);
	printf("\n");
	Modelb("SimpleSelectionSort", length, SimpleSelectionSort_b);
	for (i = 0; i != length; ++i)
		printf("%8d", b[i]);
	printf("\n");
	Modelb("2wayBubbleSort", length, TwoWayBubbleSort_b);
	for (i = 0; i != length; ++i)
		printf("%8d", b[i]);
	printf("\n");

	for(length = 500; length != 3000; length += 500)
	{
		printf ("length = %d : \n", length);
		RadixSort(length);
		modelc("HeapSort", length, HeapSort_c);
		Modelb("FastBubbleSort", length, FastBubbleSort_b);
		modelc("BInsertSort", length, BInsertSort_c);
		modelc("QuickSort", length, QuickSort_c);
		modelc("InsertSort", length, InsertSort_c);
		Modelb("SimpleSelectionSort", length, SimpleSelectionSort_b);
		Modelb("2wayBubbleSort", length, TwoWayBubbleSort_b);
	}
//	system("pause");
}

void InsertSort_c(int &ncmp, int *c, int length)
{
	int i, j;
	for (i = 2; i <= length; ++i)
	{
		if (c[i] < c[i - 1])
		{
			c[0] = c[i];//b[0]为监视哨
			c[i] = c[i - 1];
			for (j = i - 2; c[0] < c[j]; --j)
			{
				++ncmp;
				c[j + 1] = c[j];//移位
			}
			c[j + 1] = c[0];//插入
		}
		++ncmp;
	}
}

void FastBubbleSort_b(int &ncmp, int *b, int length)//改良版冒泡
{
	int i, j, temp, lastExchangeIndex;
	i = length - 1;
	while (i > 0)
	{
//		printf("%5d",i);
		lastExchangeIndex = 0;
		for (j = 0; j < i; ++j)
		{
			if (b[j+1] < b[j])
			{
				temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
				lastExchangeIndex = j;
			}
			++ncmp;
		}
		i = lastExchangeIndex;//如果后面的都有序了就不用再比较了
	}//end while
}

void BInsertSort_c(int &ncmp, int *c, int length)//折半插入排序
{
	int i, j;
	int low, high, mid;
	for (i = 2; i <= length; ++i)
	{
		c[0] = c[i];
		low = 1;
		high = i - 1;
		while (low <= high)//在b[low...high]中折半查找有序插入的位置
		{
			mid = (low + high) / 2;
			if (c[0] < c[mid])
				high = mid - 1;
			else 
				low = mid + 1;
			ncmp += 1;
		}//end while
		for (j = i - 1; j >= high + 1; --j)  
			c[j + 1] = c[j];
		c[high + 1] = c[0];
	}//end for
}

int Partition(int low, int high, int &ncmp, int *c)
{
	c[0] = c[low];//用第一个记录作枢轴记录
	int pivotkey = c[low];//枢轴记录关键字
	while (low < high)//从表的两端交替地向中间扫描
	{
		while (low < high && c[high] >= pivotkey)
		{
			--high;
			++ncmp;
		}
		c[low] = c[high];//将比枢轴小的移到低端
		while (low < high && c[low] <= pivotkey)
		{
			++low;
			++ncmp;
		}
		c[high] = c[low];//将比枢轴大的移到高端
	}// end while
	c[low] = c[0];//low == high的位置就是枢轴的位置啦！
	return low;
}//Partition

void QSort(int low, int high, int  &ncmp, int *c)//对c[low ... high]里的子序列递归排序
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(low, high, ncmp, c);
		QSort(low, pivotloc - 1, ncmp, c);
		QSort(pivotloc + 1, high, ncmp, c);
	}
}//QSort

void QuickSort_c(int &ncmp, int *c, int length)//快速排序
{
	QSort(1, length, ncmp, c);
}

void SimpleSelectionSort_b(int &ncmp, int *b, int length)
{
	int i, j, min;
	for (i = 0; i != length; ++i)
	{
		min = i;
		for (j = i + 1; j != length; ++j)
			if (b[j] < b[min])
			{
				min = j;
				++ncmp;
			}
		if (min != i)
		{	
			j = b[i];
			b[i] = b[min];
			b[min] = j;
		}
	}
}

void TwoWayBubbleSort_b(int &ncmp, int *b, int length)//双向冒泡
{
	int i, j, temp;
	bool exchange = true;
	i = 0;
	while (exchange)
	{
		exchange = false;
		for (j = i; j != length - i - 1; ++j)//向右扫描
		{
			if (b[j] > b[j + 1])
			{
				exchange = true;
				temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
			}
			++ncmp;
		}
		for (j = length - 1; j != i; --j)//向左扫描
		{
			if (b[j] < b[j - 1])
			{
				exchange = true;
				temp = b[j];
				b[j] = b[j - 1];
				b[j - 1] = temp;
			}
			++ncmp;
		}
		++i;
	}
}

void HeapAdjust(int * c, int s, int m, int &ncmp)//筛选
{
	int i, rc = c[s];
	for (i = s << 1; i <= m; i <<= 1)
	{
		if (i < m && c[i] < c[i + 1])//从值较大的孩子向下筛选
			++i;
		if (c[i] < rc)//rc应插入在s位置上
			break;
		c[s] = c[i];
		s = i;
		ncmp += 2;
	}
	c[s] = rc;//插入
}

void HeapSort_c(int &ncmp, int *c, int length)//堆排序
{
	int i, temp;
	for (i = length / 2; i != 0; --i)//建大顶堆
		HeapAdjust(c, i, length, ncmp);
	for (i = length; i > 1; --i)
	{
		temp = c[i];		//将堆顶记录和未经排序的最后一个记录相交换
		c[i] = c[1];
		c[1] = temp;
		HeapAdjust(c, 1, i - 1, ncmp);//重新调整为大顶堆
	}
}

void Modelb(char *FuncName, int length, void(*mySort)(int &, int *, int))//用全局变量数组b存储数据的函数从零开始
{
	double duration;
	int ncmp(0);
	clock_t start, finish;
	memcpy(b, a, sizeof(b));
	start = clock();

	mySort(ncmp, b, length);
	
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
//	for (int i = 0; i < length; ++i)
//		printf("%d\n", b[i]);
	printf("duration: %fs\n compare %dtimes\n", duration, ncmp);
	printf("********Result of %s********\n", FuncName);
}

void modelc(char *FuncName, int length, void(*mySort)(int &, int *, int))//用全局变量数组c存储数据的函数数据从1开始
{
	double duration;
	int ncmp(0);
	clock_t start, finish;
	memcpy(c + 1, a, sizeof(c));
	start = clock();

	mySort(ncmp, c, length);
	
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
//	for (int i = 1; i <= length; ++i)
//		printf("%d\n", c[i]);
	printf("duration: %fs\n compare %dtimes\n", duration, ncmp);
	printf("********Result of %s********\n", FuncName);
}
	
void RadixSort(int length)
{
	clock_t start, finish;
	double duration;
	memcpy(b, a, sizeof(b));
	int bcnt[10];//每个桶里元素的个数
	int tenPow[6] = {1, 10, 100, 1000, 10000, 100000};//用来取b中元素的个十百千万位
	int i, j, k, n, cnt;
	start = clock();

	for (i = 0; i != length; ++i)
	{
		n = b[i];
		ord[i] = i;
		for (j = 0; j != 5; ++j)
			bstr[i][j] = ( n - n / tenPow[j + 1] * tenPow[j + 1]) / tenPow[j]; 
	}//end for
/*	for (i = 0; i != length; ++i)
	{
		for (j = 0; j != 5; ++j)
			printf("%d", bstr[i][j]);
		printf("\n");
	}*/
//	start = clock();
	for (j = 0; j != 10; ++j)
			bcnt[j] = -1;

	for (i = 0; i != 5; ++i)//从个位开始比较
	{
		for (j = 0; j != length; ++j)//分配
		{
			k = ord[j];
			n = bstr[k][i];
			++bcnt[n];
			bucket[n][bcnt[n]] = k;
		}//end for

		cnt = length;				//收集
		for (j = 9; j >= 0; --j)
		{
			while (bcnt[j] >= 0)
			{
				cnt--;
				ord[cnt] = bucket[j][bcnt[j]];
				--bcnt[j];
			}// end while
		}// end for
	}//end for
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
//	for (i = 0; i != length; ++i)
//		printf("%d\n", b[ord[i]]);
	printf("duration: %fs\n", duration);
	printf("********Result of %RadixSort********\n");
}//end radix sort
