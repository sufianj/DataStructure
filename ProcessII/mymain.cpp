#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <time.h>
#include <malloc.h>
#include "twl.h"
#include "psapi.h"
#pragma  comment(lib,"psapi.lib")
bool ReadProcess(twl &twlist, time_t t);

int main(int argc, char* argv[])
{
	time_t t; 
	time_t last;
	t = time(NULL);
	last = t;
	twl twlist;
	owl owlist;
	while (1)
	{
		t=time(NULL); 
		if ( difftime(t, last) == 1)//每秒一刷
		{
			system("cls");
			ReadProcess(twlist, t);
			twlist.QingliMenhu(owlist);
			twlist.sort_by_wss();
			twlist.print_all();
			printf("---------已结束的进程--------\n");
			owlist.print_all();
	//		system("pause");
			last = t;
			
		} 
	}
	return 0;
}

bool ReadProcess(twl &twlist, time_t t)//读取进程信息
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProcessSnap, hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("createtoolhelp32snapshot调用失败！\n");
		return ERROR;
	}
	BOOL bMore  = Process32First(hProcessSnap, &pe32);
	while(bMore)
	{
		//开始向链表中读入数据
		pe32.dwSize = sizeof(pe32);
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 
			FALSE, pe32.th32ProcessID);
		if(hProcess == NULL&&GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
		{
			
		}
		if(GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
		{
			twlist.locate(pe32.th32ProcessID, pmc.WorkingSetSize/1024,\
				pe32.szExeFile,t);
		}
		CloseHandle(hProcess);	
		bMore = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	return true;
}