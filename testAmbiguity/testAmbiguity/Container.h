#pragma once


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
private:
    static int _sNum;
    int _val;
};