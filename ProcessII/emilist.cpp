#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "emilist.h"

owl::owl():sum(0)
{
	head = new snode;
	head->next = NULL;
	current = head;
}

owl::~owl()
{
	snode *p;
	current = head;
	while (current)
	{
		p = current->next;
		delete current;
		--sum;
		current = p;
	}
}

void owl::delete_current()
{
	snode *p;
	if (current)
	{	
		p = head;
		while(p->next != current)
			p = p->next;
		p->next = p->next->next;
		delete current;
		--sum;
		current = p->next;
	}
	else
	{
		printf("error : current == NULL\n");
		system("pause");
		exit(0);
	}
}

void owl::addAfterHead(int ID, char *szExeFile, time_t tFrom, time_t tTo)
//��ͷ��������½��
{
	snode *p;
	p = head->next;
	head->next = new snode;
	head->next->next = p;
	p = head->next;
	p->id = ID;
	p->tFrom = tFrom;
	p->tTo = tTo;
	strcpy(p->szExeFile, szExeFile);
	++sum;
}

void owl::print_all()//���ȫ���ѽ����Ľ��̼����ǵĳ���ʱ�䡢����ʱ��
{	
	struct tm *local;  
	current = head->next;
	while (current)
	{	
		local=localtime(&(current->tTo));  
		printf("������: %-18s ����ʱ�� %ds ",current->szExeFile, (int)difftime(current->tTo, current->tFrom));
		printf("����ʱ��Ϊ %02d : %02d : %02d\n", local->tm_hour, local->tm_min, local->tm_sec);
		current = current->next;
	}
}

void owl::delete_name(char *szExeFile)
{
	snode *p = head;
	current = head->next;
	while (current)
	{	
		if (0 == strcmp(szExeFile, current->szExeFile))
		{
			p->next = current->next;
			delete current;
			--sum;
			current = p->next;
			break;
		}
		else
		{
			p = current;
			current = current->next;
		}
	}		
}