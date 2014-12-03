#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <malloc.h>
#include <time.h>
#include "emilist.h"
#include  "psapi.h"
#pragma  comment(lib,"psapi.lib")
#ifndef TTE_H
#define TTE_H

typedef struct node
{
	int id;//id
	time_t tFrom; //开始时间
	time_t tTo; //结束时间
	char szExeFile[260];   //进程全名 
	int wss;//占用内存大小
	struct node *prior;
	struct node *next;
	bool bflag;
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
	void locate(int ID, int wss, char* PName, time_t tNow);//有的更新没的加上
	void add(int ID, int wss, char* PName, time_t tNow);
	void delete_current();
	void sort_by_wss();
	void print_all();
	void QingliMenhu(owl &owlist);//把已结束的移到owlist里去
};
#endif