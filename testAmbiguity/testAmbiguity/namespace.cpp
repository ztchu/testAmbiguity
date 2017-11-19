#include "namespace.h"

namespace
{
    Example::Example(int num)
        :_num(num)
    {

    }

    int Example::GetNum() const
    {
        return _num;
    }

    int Add(int a, int b)
    {
        return a + b;  //未考虑超出int范围的情况
    }
}


void TestNamespace()
{
    int ans = Add(1, 2);

    Example exp(2);
    exp.GetNum();
}