#pragma once
#include <iostream>

void TestMapContaioner();

struct StaticStruct
{
    static int num;
};
void TestStaticStruct();

class TestDelete
{
public:
    TestDelete(){}
    TestDelete(const TestDelete& other) = delete;
    TestDelete& operator= (const TestDelete& other) = delete;
};

void TestStruct();

class StaticMember
{
public:
    StaticMember(int val):_val(val)
    {

    }

    static void InitStaticMember(int num)
    {
        _sNum = num;
    }

    StaticMember& operator=(const StaticMember& other)
    {
        _val = other._val;
        std::cout << "operator=(const StaticMember& other)" << std::endl;

        return *this;
    }

    StaticMember& operator=(StaticMember& other)
    {
        _val = other._val;
        std::cout << "operator=(StaticMember& other)" << std::endl;
        return *this;
    }

private:
    static int _sNum;
    int _val;
};

void TestStaticMember();

void TestStringStream();


class Union_Test
{
public:
    Union_Test(const std::string &str);
    Union_Test(int val);
    ~Union_Test()
    {

    }
    std::string GetStr() const;
    
private:
    int _index = -1;
    union
    {
#define _Union_Test_str 1
        std::string _qing;
#define _Union_Test_int 2
        int _val;
    };
};

void TestUnionStr();

//auto AddTwoNumberB(int a, int b)
//{
//    return a + b;
//}

void TestAtuoReturn();

void TestVector();
void TestStringStream();

void ReplaceAllDistinct(std::string &src, const std::string &oldValue, const std::string &newValue);
void TestReplaceAllDistinct();

auto FuncTestAuto();
