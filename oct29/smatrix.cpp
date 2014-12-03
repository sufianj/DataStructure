#include "smatrix.h"
#include <iostream>
#include <memory.h>

using std::cin;
using std::cout;
using std::endl;

SMatrix::SMatrix():top(0),col(0),row(0)
{
	for(int i(0); i != 30; ++i)
	{
		earray[i].data = 0;
		earray[i].i = 0;
		earray[i].j = 0;
	}
}

void SMatrix::CreatMatrix()
{
	int n;
	cout << "please input col: ";
	cin >> col;
	cout << endl << "please input row: ";
	cin >> row;
	cout << endl << "please input " << col*row << "numbers" << endl;
	for (int i(0); i != row; ++i)
		for (int j(0); j != col; ++j)
		{
			cin >> n;
			if (n)
			{
				earray[top].i = i;
				earray[top].j = j;
				earray[top].data = n;
				++top;
			}
		}
}

void SMatrix::PrintMatrix(bool mode)const
{
	int k = 0;
	if (mode)
	{
		for (int i(0); i != row; ++i)
		{
			for (int j(0); j != col; ++j)
				if ( k <= top && i == earray[k].i && j == earray[k].j)
				{
					cout << earray[k].data << " ";
					++k;
				}
				else
				{
					cout << "0 ";
				}
			cout << endl;
		}
	}
	else
	{
		cout << "i  j  data " << endl;
		for (k = 0; k != top; ++k)
			cout << earray[k].i << "  " <<\
				earray[k].j << "  " << earray[k].data << endl;
	}
	
}
void SMatrix::TransposeMatrix()
{
	elem temp[30];
	int num[30];
	int cpot[30];
	int i, c, q;
	for (i = 0; i != 30; ++i)
	{
		num[i] = 0;
		cpot[i] = 0;
	}
	for (i = 0; i != top; ++i)
	{
		++num[earray[i].j];
	}
	cpot[0] = 0;
	for (i = 1; i != col; ++i)
		cpot[i] = cpot[i - 1] + num[i - 1];
	for (i = 0; i != top; ++i)
	{
		c = earray[i].j;
		q = cpot[c];
		temp[q].data = earray[i].data;
		temp[q].i = c;
		temp[q].j = earray[i].i;
		++cpot[c];
	}
	for (i = 0; i != top; ++i)
		earray[i] = temp[i];
	i = row;
	row = col;
	col = i;
}
