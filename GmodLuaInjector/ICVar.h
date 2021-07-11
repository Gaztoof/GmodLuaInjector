#pragma once
#include "Color.h"

class CCvar
{
public:
    CCvar();

    // Methods of IAppSystem
    virtual bool Connect(void* factory) = 0;
    virtual void Disconnect(void) = 0;
    virtual void* QueryInterface(const char* pInterfaceName) = 0;
    virtual void* Nothing1() = 0;
    virtual void* Nothing2() = 0;
    virtual void* Nothing3() = 0;
    virtual void* Nothing4() = 0;
    virtual void* Nothing5() = 0;

    // Inherited from ICVar
    virtual void* AllocateDLLIdentifier() = 0;
    virtual void			RegisterConCommand(void* pCommandBase) = 0;
    virtual void			UnregisterConCommand(void* pCommandBase) = 0;
    virtual void			UnregisterConCommands(void* id) = 0;
    virtual const char* GetCommandLineValue(const char* pVariableName) = 0;
    virtual void* FindCommandBase(const char* name) = 0;
    virtual const void* FindCommandBase(const char* name) const = 0;
    virtual uintptr_t FindVar(const char* var_name)= 0;
    virtual const void* FindVar(const char* var_name) const = 0;
/*15 + 2!!! all +2*/	virtual void* FindCommand(char const*) = 0;
/*16*/	virtual void* FindCommand(char const*)const = 0;
/*17*/	virtual void* GetCommands(void) = 0;
/*18*/	virtual void* GetCommands(void)const = 0;
/*19*/	virtual void* InstallGlobalChangeCallback(void (*)(void *,char const*,float)) = 0;
/*20*/	virtual void* RemoveGlobalChangeCallback(void (*)(void*,char const*,float)) = 0;
/*21*/	virtual void* CallGlobalChangeCallbacks(void*,char const*,float) = 0;
/*22*/	virtual void* InstallConsoleDisplayFunc(void*) = 0;
/*23*/	virtual void* RemoveConsoleDisplayFunc(void*) = 0;
/*24*/	virtual void* ConsoleColorPrintf(Color const&,char const*,...)const = 0;
/*25*/	virtual void* ConsolePrintf(char const*,...)const = 0;
/*26*/	virtual void* ConsoleDPrintf(char const*,...)const = 0;
/*27*/	virtual void* RevertFlaggedConVars(int) = 0;
/*28*/	virtual void* InstallCVarQuery(void*) = 0;
/*29*/	virtual void* IsMaterialThreadSetAllowed(void)const = 0;
/*30*/	virtual void* QueueMaterialThreadSetValue(void*,char const*) = 0;
/*31*/	virtual void* QueueMaterialThreadSetValue(void*,int) = 0;
/*32*/	virtual void* QueueMaterialThreadSetValue(void*,float) = 0;
/*33*/	virtual void* HasQueuedMaterialThreadConVarSets(void)const = 0;
/*34*/	virtual void* ProcessQueuedMaterialThreadConVarSets(void) = 0;
/*35*/	virtual void* FactoryInternalIterator(void) = 0;
};
