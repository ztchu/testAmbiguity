#include "filePath.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "commonTools.h"


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

void TestOfstreamFile()
{
    std::string file("a.txt");
    std::ofstream fout(file);
    fout << "qingya:12" << std::endl;
    fout << "Count:23" << std::endl;
    fout << "zhuiyuan:43" << std::endl;
}


void TestIfstreamFile()
{
    std::string file("a.txt");
    std::fstream fin(file);

    std::string dst;
    std::streampos position;
    while (!fin.eof() && dst.compare(0, 5, "Count") != 0)
    {
        position = fin.tellg();
        getline(fin, dst);
    }

    int pos = dst.find(':');
    if (pos != std::string::npos)
    {
        dst = dst.substr(pos + 1, dst.length() - pos);
    }

    dst = DeleteSpaceFromStr(dst);
    if (!dst.empty())
    {
        int count = std::stoi(dst);
        ++count;
        fin.seekg(position);
        fin << "Count:" << count << std::endl;
        std::cout << count << std::endl;
    }
    fin.close();

    std::ofstream fout(file, std::ios::app);
    fout << "zijian:35" << std::endl;
    fout.close();
}