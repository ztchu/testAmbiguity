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