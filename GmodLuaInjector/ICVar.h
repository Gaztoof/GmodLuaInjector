#pragma once
#include "Color.h"

class CCvar
{
public:
    CCvar();

    // Methods of IAppSystem
    virtual bool Connect(void* factory);
    virtual void Disconnect();
    virtual void* QueryInterface(const char* pInterfaceName);
    virtual void* Nothing1();
    virtual void* Nothing2();
    virtual void* Nothing3();
    virtual void* Nothing4();
    virtual void* Nothing5();

    // Inherited from ICVar
    virtual void* AllocateDLLIdentifier();
    virtual void			RegisterConCommand(void* pCommandBase);
    virtual void			UnregisterConCommand(void* pCommandBase);
    virtual void			UnregisterConCommands(void* id);
    virtual const char* GetCommandLineValue(const char* pVariableName);
    virtual void* FindCommandBase(const char* name);
    virtual const void* FindCommandBase(const char* name) const;
    virtual uintptr_t FindVar(const char* var_name);
    virtual const void* FindVar(const char* var_name) const;
    virtual void* FindCommand(const char* name);
    virtual const void* FindCommand(const char* name) const;
    virtual void* GetCommands(void);
    virtual const void* GetCommands(void) const;
    virtual void			InstallGlobalChangeCallback(void* callback);
    virtual void			RemoveGlobalChangeCallback(void* callback);
    virtual void			CallGlobalChangeCallbacks(void* var, const char* pOldString, float flOldValue);
    virtual void			InstallConsoleDisplayFunc(void* pDisplayFunc);
    virtual void			RemoveConsoleDisplayFunc(void* pDisplayFunc);
    virtual void			ConsoleColorPrintf(const Color& clr, const char* pFormat, ...) const;
    virtual void			ConsolePrintf(const char* pFormat, ...) const;
    virtual void			ConsoleDPrintf(const char* pFormat, ...) const;
    virtual void			RevertFlaggedConVars(int nFlag);
    virtual void			InstallCVarQuery(void* pQuery);
};
