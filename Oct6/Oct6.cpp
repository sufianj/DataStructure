#include <iostream>
#include "haxiTable.h"

using std::cin;
using std::cout;
using std::endl;

void main()
{
	int i, j;
	haxiTable haxitable;
	cout << "5 % 101 = " << 5 % 101 << endl
		<< "5 / 101 = " << 5 / 101 << endl;
	cout << "please input 10 integers" << endl;
	for (i = 0; i != 10; ++i)
	{
		cin >> j;
		haxitable.add_em(j);
	}
	cout << "different integers are as follows" << endl;
	haxitable.print_all();
}