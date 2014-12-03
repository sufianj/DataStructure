#ifndef SORT_H
#define SORT_H
#define LEN 3000   //基数排序到100000之后就比快速排序慢了

void RadixSort(int);
void HeapSort_c(int &, int *, int);
void InsertSort_c(int &, int *, int);
void FastBubbleSort_b(int &, int *, int);
void TwoWayBubbleSort_b(int &, int *, int);
void BInsertSort_c(int &, int *, int);
void QuickSort_c(int &, int *, int);
void RadixSort_b(int &, int *, int);
void SimpleSelectionSort_b(int &, int*, int);
void Modelb(char *FuncName, int length, void(*mySort)(int &, int *, int));
void modelc(char *FuncName, int length, void(*mySort)(int &, int *, int));
int Partition(int low, int high, int &ncmp, int *c);
void QSort(int low, int high, int  &ncmp, int *c);
void HeapAdjust(int * c, int s, int m, int &ncmp);

#endif