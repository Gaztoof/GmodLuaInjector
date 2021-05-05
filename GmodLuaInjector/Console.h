#pragma once
#include "Color.h"
#include <string>

typedef void(__cdecl* MsgFn)(Color* color, const char* msg, ...);
MsgFn fn;
void PrintWithPrefix(char* text, Color color)
{
    Color col = { 255,160,255,225 };
    fn(&col, (char*)"[GaztoofScriptHook] ");
    Color colT = color;
    fn(&colT, text);
    fn(&colT, (char*)"\n");
}
void PrintWithPrefix(std::string text, Color color)
{
    Color col = { 255,160,255,225 };
    fn(&col, (char*)"[GaztoofScriptHook] ");
    Color colT = color;
    fn(&colT, text.c_str());
    fn(&colT, (char*)"\n");
}
void PrintWithPrefix(const char* text, Color color)
{
    Color col = { 255,160,255,225 };
    fn(&col, (char*)"[GaztoofScriptHook] ");
    Color colT = color;
    fn(&colT, text);
    fn(&colT, (char*)"\n");
}