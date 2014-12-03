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
	time_t tFrom; //开始时间
	time_t tTo; //结束时间
	char szExeFile[MAX_PATH];   //进程全名 
	PROCESS_MEMORY_COUNTERS pmc;//占用内存大小
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