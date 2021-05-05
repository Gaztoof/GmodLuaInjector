#pragma once
#include <Windows.h>
#include <string>
#include "Console.h"

typedef __int64(__fastcall* RunStringEx)(PVOID _this, const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns);

extern RunStringEx oRunStringEx;
extern CCvar* cvarInterface;
extern std::string lastFileName;
void Execute(std::string fileName, std::string stringToRun)
{
    CLuaShared* LuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");
    PVOID cLuaInterface = LuaShared->GetLuaInterface(0);

    if (stringToRun != "print('Sorry, but I couldn't find this file')" && cLuaInterface && oRunStringEx)
    {
        if(fileName.length())
        PrintWithPrefix("Executing \"" + fileName + "\"...", Color(0, 154, 255));
        else PrintWithPrefix("Executing script...", Color(0, 154, 255));
        try {
            oRunStringEx(cLuaInterface, lastFileName.c_str(), "", stringToRun.c_str(), true, true, true, true);
        }
        catch (...) {
        }
        PrintWithPrefix("Successfully executed script!", Color(255, 255, 0));
    }
    else {
        PrintWithPrefix("Couldn't find \"" + fileName + "\"!", Color(255, 0, 0));
    }
}