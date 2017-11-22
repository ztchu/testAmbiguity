#include "dump.h"
#include <iostream>

void TestCreateDumpFile()
{
    int *p = nullptr;
    *p = 4;
}

void TestDeleteNullptr()
{
    int *ptr = new int(4);
    delete ptr;
    //ptr = nullptr;
    //delete ptr;
    if (ptr == nullptr)
    {
        std::cout << "ptr is nullptr when deleted." << std::endl;
    }
    else
    {
        std::cout << "ptr is unknown when deleted." << std::endl;
    }
}