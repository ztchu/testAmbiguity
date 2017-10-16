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