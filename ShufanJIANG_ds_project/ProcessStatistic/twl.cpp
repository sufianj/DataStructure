#include "twl.h"
#include "emilist.h"
#include <stdio.h>
#include <string.h>
#include "psapi.h"
#include <malloc.h>
#pragma  comment(lib,"psapi.lib")

twl::twl():sum(0)
{
	head = new node;
//	head = (node *)malloc(sizeof(node));
	head->prior = head;
	head->next = head;
	current = head;
}

twl::~twl()
{
	current = head->next;
	while (sum)
		delete_current();
	delete head;
//	free(head);
}

void twl::add(int ID, int wss, char* PName, time_t tNow)
{
	node *p1;
	p1 = current->next;
	current->next = new node;
	current->next->prior = current;
	current->next->next = p1;
	p1->prior = current->next;
	current = current->next;
	current->id = ID;
	current->wss = wss;
	current->bflag = 1;
	current->tFrom = current->tTo = tNow;
	strcpy(current->szExeFile, PName);
	++sum;
}

void twl::delete_current()
{
	node *p = current->next;
	current->next->prior = current->prior;
	current->prior->next = current->next;
	delete current;
	current = p;
	--sum;
}

void twl::sort_by_wss()
{
	
	node *p1, *p2, *p3;
	for (p1 = head->next; p1 != head; p1 = p1->next)
	{
		p3 = p1;
		for (p2 = p1->next; p2 != head; p2 = p2->next)
			if (p2->wss > p3->wss)
				p3 = p2;
		if (p3 != p1)
		{
			p2 = p3->next;
			p3->next = p1->next;
			p3->next->prior = p3;
			p1->next = p2;
			p1->next->prior = p1;
			p2 = p3->prior;
			p3->prior = p1->prior; 
			p3->prior->next = p3;
			p1->prior = p2;
			p1->prior->next = p1;
		}
	}
}

void twl::locate(int ID, int wss, char* PName, time_t tNow)//查找id为x的进程
{
	node *p1, *p2;
	int count = 0,flag = 0;
	p1 = p2 = head;
	while (count < sum)
	{
		p1 = p1->next;
		if (ID == p1->id)
		{
			flag = 1;
			break;
		}
		p2 = p2->prior;
		if (ID == p2->id)
		{
			flag = 2;
			break;
		}
		count += 2;
	}//end while
	if (1 == flag)
	{
		p1->tTo = tNow;
		p1->wss = wss;
		p1->bflag = 1;
	}//end if
	else if (2 == flag)
	{
		p2->tTo = tNow;
		p2->wss = wss;
		p2->bflag = 1;
	}//end else if
	else
	{
		current = head->next;
		while (current->wss > wss && current != head)
		{
			current = current->next;
		}
		current = current->prior;
		add(ID, wss, PName, tNow);

	}//end else
}

void twl::print_all()
{
//	printf("---------test----------, %d", head);
	node *p = head->next;
	while(p != head)
	{	
		printf("进程id: %5d 进程名: %-23s 所占内存: %6dk 持续时间 %3ds\n",\
			p->id, p->szExeFile,  p->wss,(int)difftime(p->tTo, p->tFrom));
		p = p->next;
	}
	printf("\n");
}

void twl::QingliMenhu(owl &owlist)
{
	current = head->next;
	while(current != head)
	{
		if (current->bflag)
		{	
			current->bflag = 0;
			owlist.delete_name(current->szExeFile);
			current = current->next;
		}
		else
		{
			owlist.addAfterHead(current->id, current->szExeFile,\
				current->tFrom, current->tTo);
			delete_current();
		}
	}
}