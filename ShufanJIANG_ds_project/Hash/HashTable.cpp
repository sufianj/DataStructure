#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

HashTable::HashTable():count(0)
{
	int i;
	char id[19];
	char str[19];
	for (i = 0; i != SIZEINDEX; ++i)
		htable[i].ID[0] = '\0';
/*	for (i = 0; i != 10; ++i)
	{
		cout << "input id :" << endl;
		cin >> id;
		InsertHarsh(id);
	}
	print_all();*/
	int p;
	ifstream input;
	input.open("in.txt");
	while (!input.eof())
	{
		input.getline(str, 19);
		p = atoi(str);
		input.getline(htable[p].ID, 19);
		input.getline(str, 19);
		htable[p].strAdd = str;
		input.getline(str,19);
		htable[p].strName = str;
		++count;
	}
	print_all();
	system("pause");
}

int HashTable::hash(char id[19])
{
	int i, j, add = 1, sum = 0;
	for (i = 1; i != 17; i += 4)
	{
		sum = 0;
		for (j = i; j != i + 4; ++j)
			sum += id[j] - '0';
		sum = sum % 23;
		add *= sum;
	}
	add += id[0];
	add = add % 997;
	return add;
}

bool HashTable::SearchHash(char id[19], int &p, int &c)
{
	p = hash(id);
	c = 0;
	while (htable[p].ID[0] != '\0' && strcmp(id, htable[p].ID))
	{
		++c;
		p = (p + c) % 1000;
	}
	if (0 == strcmp(htable[p].ID, id))
		return true;
	else
		return false;
}

int HashTable::InsertHarsh(char id[19])
{
	int p, c = 0;
	if (SearchHash(id, p, c))
		return DUPLICATE;
	else
	{
		strcpy(htable[p].ID, id);
		cout << "input name: " << endl;
		cin >> htable[p].strName;
		cout << "input add: " << endl;
		cin >> htable[p].strAdd;
		++count;
		return 1;
	}
}

void HashTable::print_all()
{
	ofstream output;
	output.open("in.txt");
	int i, j;
	for (i = 0, j = 0; i != SIZEINDEX && j != count; ++i)
		if(htable[i].ID[0] != '\0')
		{
			output << i << endl
				<< htable[i].ID << endl 
				<< htable[i].strAdd << endl
				<< htable[i].strName << endl;
			cout << "id:   " << htable[i].ID << endl
				 << "name: " << htable[i].strName << endl
				 << "add:  " << htable[i].strAdd << endl
				 << "pos:  " << i << endl;
			++j;
		}
	output.close();
}