#ifndef EMILIST_H
#define EMILIST_H
#include <time.h>
typedef struct snode
{
	int id;
	time_t tFrom; //��ʼʱ��
	time_t tTo; //����ʱ��
	char szExeFile[260];   //����ȫ�� 
	struct snode *next;
}snode;

class owl
{
private:
	snode *head;
	snode *current;
	int sum;
public:
	owl();
	~owl();
	void delete_current();
	void print_all();
	void delete_name(char *szExeFile);
	void addAfterHead(int ID, char * szExeFile, time_t tFrom, time_t tTo);
};
#endif