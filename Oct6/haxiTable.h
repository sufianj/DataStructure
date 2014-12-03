#ifndef HAXI_H
#define HAXI_H
struct em
{
	int n;
	em *p_next;
};

class haxiTable
{
public:
	haxiTable();
	void add_em(int);
	void print_all();
	~haxiTable();
private:
	struct em a[101];
	int current;
	em *p_current;
};
#endif