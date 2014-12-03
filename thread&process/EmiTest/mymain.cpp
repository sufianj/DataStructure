#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int main(int argc, char* argv[])
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
	if (!hSnapshot)
	{
		printf("CreateToolhelp32Snapshot ERROR!\n");
		return 1;
	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32 );
	if (!Process32First (hSnapshot, &pe32))
	{
		printf("Process32First ERROR!\n");
	}
	do
	{
		printf("ProcID:%d----%s",pe32.th32ProcessID, pe32.szExeFile);
	}while(Process32Next (hSnapshot, &pe32));
	return 0;
}