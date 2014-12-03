#ifndef HASHTABLE_H
#define HSAHTABLE_H
#include <string>
using namespace std;
#define SIZEINDEX 1000
#define DUPLICATE -1
typedef struct HashNode
{
	char ID[19];
	string strName;
	string strAdd;
}HashNode;

class HashTable
{
private:
	HashNode htable[1000];
	int count;
public:
	HashTable();
	int hash(char id[19]);
	bool SearchHash(char id[19], int &p, int &c);
	int InsertHarsh(char id[19]);
	void print_all();
};
#endif