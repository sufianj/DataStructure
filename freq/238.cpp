#include "238.h"
#include <stdio.h>
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

void twl::add(int x)
{
	node *p1 = current->next;
	current->next = new node;
	current->next->prior = current;
	current->next->next = p1;
	p1->prior = current->next;
	current = current->next;
	current->data = x;
	current->freq = 0;
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

void twl::sort_by_freq()
{
	node *p1, *p2, *p3;
	for (p1 = head->next; p1 != head; p1 = p1->next)
	{
		p3 = p1;
		for (p2 = p1->next; p2 != head; p2 = p2->next)
			if (p2->freq > p3->freq)
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

void twl::locate(int x)
{
	node *p1, *p2;
	int count = 0,flag = 0;
	p1 = p2 = head;
	while (count < sum)
	{
		p1 = p1->next;
		if (x == p1->data)
		{
			flag = 1;
			break;
		}
		p2 = p2->prior;
		if (x == p2->data)
		{
			flag = 2;
			break;
		}
		count += 2;
	}
	if (1 == flag)
	{
		p1->freq += 1;
//		sort_by_freq();
/*		p2 = head->next;
		while (p2->freq > p1->freq && p2 != head)
		{
			p2 = p2->next;
		}
		if (p2 != head)
		{
			p2 = p2->prior;
			p1->next->prior = p1->prior;
			p1->prior->next = p1->next;
			p1->next = p2->next;
			p1->next->prior = p1;
			p2->next = p1;
			p1->prior = p2;
		}*/
		current = head->next;
		while (current->freq > p1->freq && current != head)
		{
			current = current->next;
		}
		if (current != head)
		{	
			current = current->prior;
			add(p1->data);
			current->freq = p1->freq;
			current = p1;
			delete_current();
		}
	}
	else if (2 == flag)
	{
		p2->freq += 1;
//		sort_by_freq();
		current = head->next;
		while (current->freq > p2->freq && current != head)
		{
			current = current->next;
		}
		if (current != head)
		{	
			current = current->prior;
			add(p2->data);
			current->freq = p2->freq;
			current = p2;
			delete_current();
		}
	}
}

void twl::print_all()
{
	node *p = head->next;
	while(p != head)
	{	
		printf("(d: %d, f: %d) ", p->data, p->freq);
		p = p->next;
	}
	printf("\n");
}