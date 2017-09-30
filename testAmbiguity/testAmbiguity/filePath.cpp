#include "filePath.h"
#include <string>
#include <vector>
#include <iostream>

#ifdef _WIN32

#include <Shlobj.h>  
#pragma comment(lib, "shell32.lib")

#endif

std::string GetAppDataPath(int index)
{
    char sLogDataPath[_MAX_PATH] = { 0 };
    LPITEMIDLIST pidl = nullptr;
    SHGetSpecialFolderLocation(nullptr, index, &pidl);
    if (pidl == nullptr || !SHGetPathFromIDListA(pidl, sLogDataPath))
    {
        return std::string();
    }
    else
    {
        return std::string(sLogDataPath);
    }
}

void TestGetSpecialFolderPath()
{
    std::vector<int> specialIndex{ CSIDL_APPDATA, CSIDL_LOCAL_APPDATA, CSIDL_COMMON_APPDATA, CSIDL_COMMON_STARTUP };
    for (auto &index : specialIndex)
    {
        std::string fOlderPath(GetAppDataPath(index));
        std::cout << fOlderPath << std::endl;
    }
}