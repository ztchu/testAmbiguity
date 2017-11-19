#pragma once

namespace
{
    class Example
    {
    public:
        Example(int num);
        int GetNum() const;
    private:
        int _num;
    };

    int Add(int a, int b);
}

void TestNamespace();