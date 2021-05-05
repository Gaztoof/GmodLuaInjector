#pragma once
#include <Windows.h>
#include <cwchar>
#include <TlHelp32.h>

DWORD GetPID(const char* processName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(processEntry);

	Process32First(hSnapshot, &processEntry);
	do
	{
		if (!strcmp(processEntry.szExeFile, processName))
		{
			CloseHandle(hSnapshot);
			return processEntry.th32ProcessID;
		}
	} while (Process32Next(hSnapshot, &processEntry));

	CloseHandle(hSnapshot);
	return -1;
}
