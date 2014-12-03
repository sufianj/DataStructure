#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <time.h>
#include  < psapi.h >
#pragma  comment(lib,"psapi.lib")#ifndef TTE_H
#define TTE_H

typedef struct node
{
	int id;
	time_t tFrom; //��ʼʱ��
	time_t tTo; //����ʱ��
	char szExeFile[MAX_PATH];   //����ȫ�� 
	PROCESS_MEMORY_COUNTERS pmc;//ռ���ڴ��С
	struct node *prior;
	struct node *next;
}node;

class twl
{
private:
	node *head;
	node *current;
	int sum;
public:
	twl();
	~twl();
	void locate(int ID, PROCESS_MEMORY_COUNTERS PMC, char* PName, time_t tNow);
	void add(int ID, PROCESS_MEMORY_COUNTERS PMC, char* PName, time_t tNow);
	void delete_current();
	void sort_by_pmc();
	void print_all();
};
#endif