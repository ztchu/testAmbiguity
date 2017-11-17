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
        return a + b;  //δ���ǳ���int��Χ�����
    }
}


void TestNamespace()
{
    int ans = Add(1, 2);

    Example exp(2);
    exp.GetNum();
}