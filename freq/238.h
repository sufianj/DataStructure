#ifndef TTE_H
#define TTE_H
typedef struct node
{
	int data;
	int freq;
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
	void locate(int);
	void add(int);
	void delete_current();
	void sort_by_freq();
	void print_all();
};
#endif