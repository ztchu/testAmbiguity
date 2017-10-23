#include "container.h"

#include <map>
#include <iostream>


void TestMapContaioner()
{
    std::map<int, int> mat{ {1, 2} };

    auto iter = mat.begin();
    
    std::cout << mat[1] << std::endl;
    std::cout << mat[2] << std::endl;
}

void TestPair()
{
    std::pair<int, int> pa{ 1, 2 };
    pa.first;
}

int StaticStruct::num = 3;
void TestStaticStruct()
{     
    std::cout << StaticStruct::num << std::endl;
}

void TestUnion()
{
    union
    {
        int *_int = nullptr;
        char *_char;
        double *_double;
    };
}

void TestDeleteFunction()
{
    TestDelete a;
    //TestDelete b(a);
}

struct Qing
{
    int a;
    int b;
};

void TestStruct()
{
    Qing *ptr = new Qing{ 1, 2 };
    std::cout << ptr->a << std::endl;
}

int StaticMember::_sNum = 0;
void TestStaticMember()
{
    StaticMember mem(3);
    StaticMember::InitStaticMember(5);

}