#include "238.h"
#include <stdio.h>
main()
{
	twl twlist;
	for (int i(0); i != 4; ++i)
		twlist.add(i+1);
	twlist.print_all();
	twlist.locate(3);
	twlist.locate(3);
	twlist.locate(4);
	twlist.locate(7);
	twlist.locate(2);
	twlist.locate(1);
	twlist.locate(3);
	twlist.locate(4);
	twlist.print_all();
	return 0;
}