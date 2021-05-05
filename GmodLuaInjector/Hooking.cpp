#include <Windows.h>
#include <stdint.h>
PVOID VMTHook(PVOID** src, PVOID dst, int index)
{
	// I could do tramp hooking instead of VMT hooking, but I came across a few problems while implementing my tramp, and VMT just makes it easier.
	PVOID* VMT = *src;
	PVOID ret = (VMT[index]);
	DWORD originalProtection;
	VirtualProtect(&VMT[index], sizeof(PVOID), PAGE_EXECUTE_READWRITE, &originalProtection);
	VMT[index] = dst;
	VirtualProtect(&VMT[index], sizeof(PVOID), originalProtection, &originalProtection);
	return ret;
}