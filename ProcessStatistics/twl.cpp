#include "twl.h"
#include <stdio.h>
#include <string.h>
twl::twl():sum(0)
{
	head = new node;
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
}

void twl::add(int ID, PROCESS_MEMORY_COUNTERS PMC, char* PName, time_t tNow)
{
	node *p1 = current->next;
	current->next = new node;
	current->next->prior = current;
	current->next->next = p1;
	p1->prior = current->next;
	current = current->next;
	current->id = ID;
	current->pmc = 0;
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

void twl::sort_by_pmc()
{
	
	node *p1, *p2, *p3;
	for (p1 = head->next; p1 != head; p1 = p1->next)
	{
		p3 = p1;
		for (p2 = p1->next; p2 != head; p2 = p2->next)
			if (p2->pmc > p3->pmc)
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

void twl::locate(int ID, PROCESS_MEMORY_COUNTERS PMC, char* PName, time_t tNow)//查找id为x的进程
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
		///////////////:TODO:p1->...
	}//end if
	else if (2 == flag)
	{
		/////////////TODO:p2->.....
	}//end else if
	else
	{
		current = head->next;
		while (current->pmc > PMC && current != head)
		{
			current = current->next;
		}
		if (current != head)
		{	
			current = current->prior;
			add(ID, PMC, PName, tNow);
		}

	}//end else
}

void twl::print_all()
{
	node *p = head->next;
	while(p != head)
	{	
		printf("id: %d,szExeFile: %s pmc: %d\n",p->szExeFile, p->id, p->pmc);
		p = p->next;
	}
	printf("\n");
}