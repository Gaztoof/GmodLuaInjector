#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Helpers.hpp"

HANDLE consoleHandle;
#define SetConsoleColor(col) SetConsoleTextAttribute(consoleHandle, col);

void main()
{
    SetConsoleTitle("Garry's Mod Lua Executor / ScriptHook Injector - Coded by t.me/Gaztoof");
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "[*] Waiting for Gmod.exe..." << std::endl;
    DWORD gmodPID = -1;
    do {
        gmodPID = GetPID("gmod.exe");
        Sleep(1000);
    } while (gmodPID == -1);

    SetConsoleColor( FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << "[*] Successfully got PID: " << gmodPID << "\n";

    char currDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currDir);

    std::string filePath = std::string(currDir + std::string("\\GmodLuaInjector.dll"));
    if (std::fstream(filePath).bad())
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "[!] Please, make sure GmodLuaInjector.dll is next to this .exe." << std::endl;
        getchar(); return;
    }
    const char* path = "C:/GaztoofScriptHook/GmodLuaInjector.dll";
    
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, gmodPID);
    if (hProc == INVALID_HANDLE_VALUE)
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "[!] Couldn't create a handle to Garry's Mod.\n" << std::endl;
        getchar(); return;
    }

    LPVOID strAddy = VirtualAllocEx(hProc, NULL, strlen(path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (strAddy == NULL) {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "[!] Couldn't call VirtualAllocEx." << std::endl;
        getchar(); return;
    }
    if (!WriteProcessMemory(hProc, strAddy, path, strlen(path), NULL))
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "[!] Couldn't call WriteProcessMemory." << std::endl;
        getchar(); return;
    }

    LPVOID loadLibraryA = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    HANDLE hThread = CreateRemoteThread(hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryA, strAddy, NULL, NULL);
    if (hThread == INVALID_HANDLE_VALUE)
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "[!] Couldn't call CreateRemoteThread." << std::endl;
        getchar(); return;
    }

    CloseHandle(hProc);
    VirtualFreeEx(hProc, strAddy, 0, MEM_RELEASE);
    std::cout << "[*] Successfully injected." << std::endl;
    getchar();
}
