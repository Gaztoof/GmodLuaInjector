#pragma once
#include <string>
#include <vector>

class CLuaShared
{
public:
	virtual void destructor() = 0;
	virtual void Init(void* (*)(const char*, int*), bool, void*, void*) = 0;
	virtual void Shutdown(void) = 0;
	virtual void DumpStats() = 0;
	virtual void* CreateLuaInterface(unsigned char, bool) = 0;
	virtual void CloseLuaInterface(void*) = 0;
	virtual void* GetLuaInterface(unsigned char) = 0;
	virtual void* LoadFile(const std::string& path, const std::string& pathId, bool fromDatatable, bool fromFile) = 0;
	virtual void* GetCache(const std::string&) = 0;
	virtual void MountLua(const char*) = 0;
	virtual void MountLuaAdd(const char*, const char*) = 0;
	virtual void UnMountLua(const char*) = 0;
	virtual void SetFileContents(const char*, const char*) = 0;
	virtual void SetLuaFindHook(void*) = 0;
	virtual void FindScripts(const std::string&, const std::string&, std::vector<std::string>&) = 0;
	virtual const char* GetStackTraces() = 0;
	virtual void InvalidateCache(const std::string&) = 0;
	virtual void EmptyCache() = 0;

};