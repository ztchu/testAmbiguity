#include "SmartPointer.h"
#include <memory>
#include <iostream>

void TestSmartPointer()
{
    auto ptr = std::make_shared<int>();
    int a = 3;
    *ptr = a;
    std::cout << *ptr << std::endl;
}