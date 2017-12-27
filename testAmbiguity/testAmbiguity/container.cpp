#include "container.h"

#include <map>
#include <iostream>
#include <sstream>
#include <vector>


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
    delete ptr;
}

int StaticMember::_sNum = 0;
void TestStaticMember()
{
    StaticMember mem(3);
    StaticMember::InitStaticMember(5);

    StaticMember mem1(1), mem2(2);
    mem1 = mem2;
    mem1 = StaticMember(2);
}

void TestStringStream()
{
    std::stringstream ss;
    ss << "value:" << 2 << std::endl;
    std::cout << ss.str() << std::endl;
}

Union_Test::Union_Test(const std::string &str)
{
    _index = _Union_Test_str;
    _qing = str;
}

Union_Test::Union_Test(int val)
{
    _index = _Union_Test_int;
    _val = val;
}

std::string Union_Test::GetStr() const
{
    return _qing;
}

void TestUnionStr()
{
    Union_Test str(3);
    
}

auto AddTwoNumber(int a, int b)
{
    return a + b;
}

void TestAtuoReturn()
{
    int ans = AddTwoNumber(1, 3);
    std::cout << ans << std::endl;
}

void TestVector()
{
    std::vector<int> vec;
    int ans = vec.front();
}
}

void ReplaceAllDistinct(std::string &src, const std::string &oldValue, const std::string &newValue)
{
    for (auto pos = 0; pos != std::string::npos; pos += newValue.length())
    {
        if ((pos = src.find(oldValue, pos)) != std::string::npos)
        {
            src.replace(pos, oldValue.length(), newValue);
        }
        else
        {
            break;
        }
    }
}

void TestReplaceAllDistinct()
{
    std::string src("a < b; b&&c; c > d");
    ReplaceAllDistinct(src, "<", "&lt;");
    ReplaceAllDistinct(src, ">", "&gt;");
    ReplaceAllDistinct(src, "&", "&amp;");
    std::cout << src << std::endl;
}

auto FuncTestAuto()
{
    int a = 3;
    return a;
}
