#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <time.h>
#include "twl.h"
#include  <psapi.h>
int main(int argc, char* argv[])
{
	struct tm *local;  
	time_t t; 
	time_t last;
	t = time(NULL);
	last = t;
	bool bMore;
	HANDLE hSnapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
	if (!hSnapshot)
	{
		printf("CreateToolhelp32Snapshot ERROR!\n");
		return 1;
	}
	PROCESSENTRY32 pe32;

	pe32.dwSize = sizeof(PROCESSENTRY32 );

	while (1)
	{
		t=time(NULL); 
		if ( difftime(t, last) == 1)//Ã¿ÃëÒ»Ë¢
		{
			system("cls");
			local=localtime(&t);  
//			printf("Local time is: %d : %d : %d\n%d, %d, %d\n",local->tm_hour, \
//				local->tm_min,local->tm_sec,local->tm_mday, local->tm_mon+1, \
//				local->tm_year+1900);  
			bMore  = Process32First(hProcessSnap, &pe32);
			while (bMore)
			{
			}
			last = t;
		} 
	}

	return 0;
}