#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>

#include "Console.h"
#include "Color.h"
#include "ICVar.h"
#include "CLuaShared.h"
#include "Hooking.h"
#include "Utils.h"
#include "GUI.h"
#include "Executor.h"

#if _WIN64
#define ConColorMsg "?ConColorMsg@@YAXAEBVColor@@PEBDZZ"
#else
#define ConColorMsg "?ConColorMsg@@YAXABVColor@@PBDZZ"
#endif

typedef __int64(__fastcall* RunStringEx)(PVOID _this, const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns);

RunStringEx oRunStringEx;
PVOID cLuaInterface = nullptr;
CCvar* cvarInterface = nullptr;
std::string cvarName = "";
std::string toRun = "";
std::string lastFileName = "";
bool __fastcall hkRunStringEx(PVOID _this,
#ifndef _WIN64
    void*,
#endif
    const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns)
{
    if (!strcmp(filename, "LuaCmd") || !strcmp(filename, "RunString(Ex)") || !strlen(filename))
        return oRunStringEx(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);
    lastFileName = std::string(filename);
    // To those not understanding what this is: this runs a lua script that sets a convar as "servername - serverip", and I just retrieve it and use it to save.
    oRunStringEx(_this, filename, path, toRun.c_str(), run, printErrors, dontPushErrors, noReturns);
    // This is causing me problems in the x86 implementation...
    // For some reasons, calling it will simply make you crash... Tried fixing in a lots of ways, but just can't figure it out yet and i'm lazy to deeply search, so whoever fixes this, the cheat will work in X86 without any problems as it was first made to work with both.
    uintptr_t cvar = (uintptr_t)cvarInterface->FindVar(cvarName.c_str());
    if (!cvar)
        return oRunStringEx(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);
    std::string ip = CVarStr(cvar);
    Fix(ip); // Fix = make it something "save'able", as some characters are blacklisted for file names.
    if(ip.find(" - loopback") != std::string::npos)
        return oRunStringEx(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);
    std::string SavePath = "C:/GaztoofScriptHook/" + ip + "/" + std::string(filename);
    Sanitize(SavePath);
    StrToAscii(SavePath);
    std::string extension = ToLower(GetExtension(SavePath));
    if (extension == ".lua")
    {
        CreateDirectoryRec((SavePath));
        std::ofstream outfile(SavePath);
        outfile << stringToRun << std::endl;
        PrintWithPrefix("Downloading file " + std::string(filename), Color(0, 145, 255));
    }
    return oRunStringEx(_this, filename, path, stringToRun, run, printErrors, dontPushErrors, noReturns);
}
// This method is only used when you're in the Debug build, as it will run from the console and not the ImGui Menu.
void InjectThread()
{
    while (true)
    {
        std::cout << "Please, enter the path to your .Lua file: ";
        char cInput[256];
        std::cin.getline(cInput, 256);

        std::string input(cInput);

        if (oRunStringEx && cLuaInterface)
        {
            size_t pos = std::string::npos;
            while ((pos = input.find('"')) != std::string::npos)
                input.erase(pos);

            std::string filecontent = readContent(input);
            Execute(input, filecontent);
        }
    }
}

void Main()
{
    srand(time(nullptr));
    cvarName = RandomString(10);
    toRun = "CreateClientConVar(\"";
    toRun += cvarName;
    toRun += "\", \"\", true, false) :SetString(GetHostName() .. \" - \" ..game.GetIPAddress())";

#ifdef _DEBUG
#pragma region Console Setup
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    SetConsoleTitle(L"Epic Gmod Scripthook - Coded by t.me/Gaztoof");
#pragma endregion
#endif

    fn = (MsgFn)GetProcAddress(GetModuleHandleW(L"tier0.dll"), ConColorMsg);
    PrintWithPrefix((char*)"Successfully Injected!", Color(255,255,0));

    InitializeGUI();
#pragma region CVar Setup
    cvarInterface = (CCvar*)GetInterface("vstdlib.dll", "VEngineCvar007");
    if (cvarInterface)
    {
        std::cout << "Found CCVar: " << cvarInterface << std::endl;
        PrintWithPrefix((char*)"Successfully found CCVar!", Color(255,255,0));
    }
#pragma endregion
    
#pragma region CLua Setup
    CLuaShared* LuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");
    int counter = -1;
    do {
        counter++;
        if (counter == 1) std::cout << "Please, join a server..." << std::endl;
        cLuaInterface = LuaShared->GetLuaInterface(0);
        Sleep(5);
    } while (cLuaInterface == nullptr);
    std::cout << "Found CLuaInterface: " << std::hex << cLuaInterface << std::endl;
#pragma endregion

    oRunStringEx = (RunStringEx)VMTHook((PVOID**)cLuaInterface, hkRunStringEx, 111);
    PrintWithPrefix("Successfully Hooked!", Color(255, 255, 0));

#ifdef _DEBUG
    std::thread(InjectThread).detach();
#endif

    //that's dirty ik
    do {
        cLuaInterface = LuaShared->GetLuaInterface(0);
        while (cLuaInterface == nullptr)
        {
            cLuaInterface = LuaShared->GetLuaInterface(0);
            if (cLuaInterface != nullptr)
            {
                oRunStringEx = (RunStringEx)VMTHook((PVOID**)cLuaInterface, hkRunStringEx, 111);
                PrintWithPrefix("Successfully ReHooked!", Color(255, 255, 0));
                break;
            }            
            Sleep(10);
        }
        Sleep(10);

    } while (true);
}

BOOL APIENTRY DllMain(HMODULE hModule, uintptr_t ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        std::thread(Main).detach();
    return TRUE;
}

