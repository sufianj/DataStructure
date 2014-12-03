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
	int lenth;//�ѵ�����
	int sum;//����Ԫ�ص�����

public:
	wNode *heap;//��̬����Ķѣ���ʼ��ʱ����10��
	EmiHeap();
	~EmiHeap();
	int add(char);//���������ַ�,�����ظ��ַ��ڶ��е�λ��,ʧ��ʱ����-1
	void adjust(int n, int len);
	void sortbyw(int pos[128]);
	int GetLenth(){return lenth;}
	int GetSum(){return sum;}
	wNode& operator[](int i);//����heap���±�Ϊi��Ԫ�ص�����
};
#endif