#include "dump.h"

void TestCreateDumpFile()
{
    int *p = nullptr;
    *p = 4;
}

void TestDeleteNullptr()
{
    int *ptr = new int(4);
    delete ptr;
    ptr = nullptr;
    delete ptr;
}