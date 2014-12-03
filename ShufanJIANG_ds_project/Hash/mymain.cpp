#include <iostream>
#include <fstream>
#include "HashTable.h"
using namespace std;
main()
{
	HashTable HTable;
	char id[19];
	int p;
	int c;
/*	for (int i(0); i != 10; ++i)
	{
		cout << "input an id number" << endl;
		cin >> id;
		cout << HTable.hash(id) << endl; 
	}*/

	int choice = 5;
	while(choice)
	{
		system("cls");
		cout << " please input your choice :" << endl
			<< " 1 --> insert an id" << endl
			<< " 2 --> search an id" << endl
			<< " 3 --> view all the records" << endl
			<< " 0 --> exit" << endl;
		cin >> choice;
		switch(choice)
		{
		case 0:
			break;
		case 1:
			cout << "please input an id number" << endl;
			cin >> id;
			if (-1 == HTable.InsertHarsh(id))
				cout << "this id exists" << endl;
			else
				cout << "success!" << endl;
			break;
		case 2:
			cout << "please input an id number" << endl;
			cin >> id;
			if (HTable.SearchHash(id, p, c))
				cout << "the id's position is " << p
				<< " and collision is " << c << endl;
			else
				cout << "no such id exists" << endl;
			break;
		case 3:
			HTable.print_all();
			break;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}