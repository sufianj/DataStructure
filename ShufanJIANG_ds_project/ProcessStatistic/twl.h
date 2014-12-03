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
	time_t tFrom; //��ʼʱ��
	time_t tTo; //����ʱ��
	char szExeFile[260];   //����ȫ�� 
	int wss;//ռ���ڴ��С
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
	void locate(int ID, int wss, char* PName, time_t tNow);//�еĸ���û�ļ���
	void add(int ID, int wss, char* PName, time_t tNow);
	void delete_current();
	void sort_by_wss();
	void print_all();
	void QingliMenhu(owl &owlist);//���ѽ������Ƶ�owlist��ȥ
};
#endif