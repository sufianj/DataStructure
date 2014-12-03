#ifndef EMIHEAP_H
#define EMIHEAP_H

typedef struct
{ 
	int w;
	char ch;
}wNode;

class EmiHeap
{
private:
	int lenth;//堆的容量
	int sum;//堆中元素的总数

public:
	wNode *heap;//动态分配的堆，初始化时分配10个
	EmiHeap();
	~EmiHeap();
	int add(char);//向堆里添加字符,并返回该字符在堆中的位置,失败时返回-1
	void adjust(int n, int len);
	void sortbyw(int pos[128]);
	int GetLenth(){return lenth;}
	int GetSum(){return sum;}
	wNode& operator[](int i);//返回heap里下标为i的元素的引用
};
#endif