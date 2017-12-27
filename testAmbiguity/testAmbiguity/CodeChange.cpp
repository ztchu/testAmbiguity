#include "CodeChange.h"
#include <string>
//#include <chrono>
//#include <iomanip>
//#include <ctime>
//#include <io.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <Windows.h>
#include <iostream>

std::string Wstring2Utf8(const std::wstring& unicodeStr)
{
    if (unicodeStr.empty()) return "";

    auto dstLength = WideCharToMultiByte(CP_UTF8, 0, unicodeStr.c_str(), -1, static_cast<char*>(nullptr), 0, NULL, NULL);
    auto destData = new char[dstLength + 1];
    memset(destData, 0, dstLength);
    WideCharToMultiByte(CP_UTF8, 0, unicodeStr.c_str(), -1, destData, dstLength, NULL, NULL);
    std::string result = destData;
    delete[] destData;
    return result;
}

std::wstring Utf8ToWstring(const std::string& utf8)
{
    if (utf8.empty()) return L"";

    auto dstLength = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
    auto destData = new wchar_t[dstLength + 1];
    memset(destData, 0, dstLength);
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, destData, dstLength);
    std::wstring result = destData;
    delete[] destData;
    return result;
}

void TestCodeChange()
{
    const std::string source("ℽℿℾⅅⅆⅇⅈⅉ");
    std::cout << source.length() << std::endl;
    //std::string ans = Wstring2Utf8(Utf8ToWstring(source));
    std::wstring wStr = Utf8ToWstring(source);
    std::cout << wStr.length() << std::endl;

}