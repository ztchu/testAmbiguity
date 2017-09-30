#pragma once

#include <string>
//class string;

bool TestStringSzchar(const std::string &src, const char *dst);

void TestStringSzchar();

void DeleteFrontAndRearSpace(std::string &str);
void TestDeleteFrontAndRearSpace();

void TestIfStrIsPureNum();
void TestIsInterger();
void TestIsDecimalInterger();

void TestTan();
void TestTranslateAngleToPoint();

void TestGetFamousAuthor();

class String
{
public:
    String(const char *str)
    {
        _data = new char[strlen(str) + 1];
        strcpy_s(_data, strlen(str) + 1, str);
    }
    ~String()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }
    }
    inline operator const char *()
    {
        return _data;
    }
private:
    char *_data = nullptr;
};

void TestStringClass();
void TestTranslateAngleToPoint();

void TestStrCompare();

void TestUppercaseToLowercase();

void TestFindLastNotOf();

void TestStringL();