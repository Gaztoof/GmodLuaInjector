#pragma once
#include <Windows.h>
#include <sstream>
#include <string>
#include <streambuf>
#include <fstream>
#include <vector>
void Fix(std::string& src);
void CreateDirectoryRec(std::string input);
std::string GetDirectory(std::string input);
std::string GetExtension(std::string input);
std::string ToLower(std::string input);
std::string Sanitize(std::string& input);
std::string readContent(std::string path);
std::string CVarStr(uintptr_t address);
PVOID GetInterface(const char* moduleName, const char* interfaceName);
void openFileDialog();
std::string RandomString(int length);
std::string StrToAscii(std::string& input);