#include "Utils.h"

void Fix(std::string& src)
{
    size_t pos = std::string::npos;
    while ((pos = src.find(":")) != std::string::npos)
        src[pos] = '.';
    while ((pos = src.find('\0')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('\\')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('/')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('*')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('?')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('<')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('>')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('"')) != std::string::npos)
        src.erase(pos);
    while ((pos = src.find('|')) != std::string::npos)
        src.erase(pos);
}
void CreateDirectoryRec(std::string input)
{
    std::string Directory = "";
    size_t pos = std::string::npos;
    while ((pos = input.find('/')) != std::string::npos)
    {
        Directory += input.substr(0, pos) + "/";
        CreateDirectoryA(Directory.c_str(), NULL);
        input.erase(0, pos + 1);
    }
    CreateDirectoryA(Directory.c_str(), NULL);
}
std::string GetDirectory(std::string input)
{
    size_t pos = 0;
    std::string Directory = "";
    while ((pos = input.find("/")) != std::string::npos) {
        input.erase(0, pos + 1);
        Directory += input.substr(0, pos) + "/";
    }
    return Directory;
}
std::string GetExtension(std::string input)
{
    return input.substr(input.find_last_of("."));
}
std::string ToLower(std::string input)
{
    for (int i = 0; i < input.length(); i++)
        input[i] = tolower(input[i]);
    return input;
}
std::string StrToAscii(std::string& input)
{
    std::string output = "";
    for (int i = 0; i < input.length(); i++)
        if (input[i] > ' ' && input[i] < '~')
            output += input[i];
    input = output;
    return output;
}
std::string Sanitize(std::string& input)
{
    size_t pos = std::string::npos;
    std::vector<std::string> blackListed;
    blackListed.push_back("..");
    blackListed.push_back("/aux"); blackListed.push_back("/aux.");
    blackListed.push_back("/con"); blackListed.push_back("/con.");
    blackListed.push_back("/prn"); blackListed.push_back("/prn.");
    blackListed.push_back("/nul"); blackListed.push_back("/nul.");
    blackListed.push_back("/com1"); blackListed.push_back("/com1.");
    blackListed.push_back("/com2"); blackListed.push_back("/com2.");
    blackListed.push_back("/com3"); blackListed.push_back("/com3.");
    blackListed.push_back("/com4"); blackListed.push_back("/com4.");
    blackListed.push_back("/com5"); blackListed.push_back("/com5.");
    blackListed.push_back("/com6"); blackListed.push_back("/com6.");
    blackListed.push_back("/com7"); blackListed.push_back("/com7.");
    blackListed.push_back("/com8"); blackListed.push_back("/com8.");
    blackListed.push_back("/com9"); blackListed.push_back("/com9.");
    blackListed.push_back("/lpt1"); blackListed.push_back("/lpt1.");
    blackListed.push_back("/lpt2"); blackListed.push_back("/lpt2.");
    blackListed.push_back("/lpt3"); blackListed.push_back("/lpt3.");
    blackListed.push_back("/lpt4"); blackListed.push_back("/lpt4.");
    blackListed.push_back("/lpt5"); blackListed.push_back("/lpt5.");
    blackListed.push_back("/lpt6"); blackListed.push_back("/lpt6.");
    blackListed.push_back("/lpt7"); blackListed.push_back("/lpt7.");
    blackListed.push_back("/lpt8"); blackListed.push_back("/lpt8.");
    blackListed.push_back("/lpt9"); blackListed.push_back("/lpt9.");

    for (auto str : blackListed)
    {
        while ((pos = input.find(str)) != std::string::npos)
            input.erase(pos, str.length());
        if (ToLower(input.substr(input.length() - str.length())) == str)
            input = input.substr(0, input.length() - str.length());
    }
    return input;
}
std::string readContent(std::string path)
{
    std::stringstream str;
    std::ifstream stream(path);
    if (stream.is_open())
    {
        while (stream.peek() != EOF)
        {
            str << (char)stream.get();
        }
        stream.close();
        return str.str();
    }
    return "print('Sorry, but I couldn't find this file')";
}
std::string CVarStr(uintptr_t address)
{
    uintptr_t strAddy = *(uintptr_t*)(address + 0x48);
    uint32_t strLen = (*(uint32_t*)(address + 0x50) - 1);
    std::string output("");
    for (int i = 0; i < strLen; i++)
        output += *(char*)(strAddy + i);
    return output;
    //return std::string(strAddy, strLen);
}
typedef PVOID(*CreateInterfaceFn)(const char* Name, int* ReturnCode);
PVOID GetInterface(const char* moduleName, const char* interfaceName)
{
    CreateInterfaceFn createInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(moduleName), "CreateInterface");
    return createInterface(interfaceName, NULL);
}
std::string selectedFilePath = "";
void openFileDialog() {
    OPENFILENAMEA openFileName = { 0 };
    char fileName[260] = "";

    openFileName.lStructSize = sizeof(OPENFILENAMEA);
    openFileName.lpstrDefExt = "lua";
    openFileName.lpstrFile = fileName;
    openFileName.lpstrFilter = "LUA Files (*.lua)\0*.lua\0\0";
    openFileName.hwndOwner = NULL;
    openFileName.nMaxFile = sizeof(fileName);
    openFileName.Flags = OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileNameA(&openFileName))
        selectedFilePath = std::string(fileName);
        //return std::string(fileName);
    //return "";
}
std::string RandomString(int length)
{
    std::string alph = "ABCDEFHIJKLMNOPQRSTUVWXYZabcdefhijklmnopqrstuvwxyz0123456789+-*/";
    std::string out = "";
    for (int i = 0; i < length; i++)
    {
        out += alph[rand() % (alph.length() + 1)];
    }
    return out;
}