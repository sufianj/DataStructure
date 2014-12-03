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
int bucket[10][LEN];//���������õ�Ͱ Ҫȫ�ֱ������ܿ���ô��Ŀռ�
int bstr[LEN][5];//��b������飬bstr[i][1]��ʾb[i]Ԫ�ص�ʮλ�ϵ���
int ord[LEN];//����b��Ԫ��λ�õ�ӳ��

void main()
{
	int i, length;
/*	ofstream output;//�ļ�input.txt����3000�������������ÿ����ռһ��
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
	printf ("�����length = %d �����֤���㷨����ȷ��: \n", length);
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
			c[0] = c[i];//b[0]Ϊ������
			c[i] = c[i - 1];
			for (j = i - 2; c[0] < c[j]; --j)
			{
				++ncmp;
				c[j + 1] = c[j];//��λ
			}
			c[j + 1] = c[0];//����
		}
		++ncmp;
	}
}

void FastBubbleSort_b(int &ncmp, int *b, int length)//������ð��
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
		i = lastExchangeIndex;//�������Ķ������˾Ͳ����ٱȽ���
	}//end while
}

void BInsertSort_c(int &ncmp, int *c, int length)//�۰��������
{
	int i, j;
	int low, high, mid;
	for (i = 2; i <= length; ++i)
	{
		c[0] = c[i];
		low = 1;
		high = i - 1;
		while (low <= high)//��b[low...high]���۰������������λ��
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
	c[0] = c[low];//�õ�һ����¼�������¼
	int pivotkey = c[low];//�����¼�ؼ���
	while (low < high)//�ӱ�����˽�������м�ɨ��
	{
		while (low < high && c[high] >= pivotkey)
		{
			--high;
			++ncmp;
		}
		c[low] = c[high];//��������С���Ƶ��Ͷ�
		while (low < high && c[low] <= pivotkey)
		{
			++low;
			++ncmp;
		}
		c[high] = c[low];//�����������Ƶ��߶�
	}// end while
	c[low] = c[0];//low == high��λ�þ��������λ������
	return low;
}//Partition

void QSort(int low, int high, int  &ncmp, int *c)//��c[low ... high]��������еݹ�����
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(low, high, ncmp, c);
		QSort(low, pivotloc - 1, ncmp, c);
		QSort(pivotloc + 1, high, ncmp, c);
	}
}//QSort

void QuickSort_c(int &ncmp, int *c, int length)//��������
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

void TwoWayBubbleSort_b(int &ncmp, int *b, int length)//˫��ð��
{
	int i, j, temp;
	bool exchange = true;
	i = 0;
	while (exchange)
	{
		exchange = false;
		for (j = i; j != length - i - 1; ++j)//����ɨ��
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
		for (j = length - 1; j != i; --j)//����ɨ��
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

void HeapAdjust(int * c, int s, int m, int &ncmp)//ɸѡ
{
	int i, rc = c[s];
	for (i = s << 1; i <= m; i <<= 1)
	{
		if (i < m && c[i] < c[i + 1])//��ֵ�ϴ�ĺ�������ɸѡ
			++i;
		if (c[i] < rc)//rcӦ������sλ����
			break;
		c[s] = c[i];
		s = i;
		ncmp += 2;
	}
	c[s] = rc;//����
}

void HeapSort_c(int &ncmp, int *c, int length)//������
{
	int i, temp;
	for (i = length / 2; i != 0; --i)//���󶥶�
		HeapAdjust(c, i, length, ncmp);
	for (i = length; i > 1; --i)
	{
		temp = c[i];		//���Ѷ���¼��δ����������һ����¼�ཻ��
		c[i] = c[1];
		c[1] = temp;
		HeapAdjust(c, 1, i - 1, ncmp);//���µ���Ϊ�󶥶�
	}
}

void Modelb(char *FuncName, int length, void(*mySort)(int &, int *, int))//��ȫ�ֱ�������b�洢���ݵĺ������㿪ʼ
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

void modelc(char *FuncName, int length, void(*mySort)(int &, int *, int))//��ȫ�ֱ�������c�洢���ݵĺ������ݴ�1��ʼ
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
	int bcnt[10];//ÿ��Ͱ��Ԫ�صĸ���
	int tenPow[6] = {1, 10, 100, 1000, 10000, 100000};//����ȡb��Ԫ�صĸ�ʮ��ǧ��λ
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

	for (i = 0; i != 5; ++i)//�Ӹ�λ��ʼ�Ƚ�
	{
		for (j = 0; j != length; ++j)//����
		{
			k = ord[j];
			n = bstr[k][i];
			++bcnt[n];
			bucket[n][bcnt[n]] = k;
		}//end for

		cnt = length;				//�ռ�
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
