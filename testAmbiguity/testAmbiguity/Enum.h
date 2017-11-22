#pragma once
#include <string>

namespace Enum
{
    enum class MyName
    {
        Qingya,
        Zijian,
        None
    };

    class Person
    {
    public:
        Person(int age = 0, const std::string & name = std::string());
        MyName GetName() const;
        int GetAge() const;

    private:
        MyName _name = MyName::None;
        int _age = 0;
    };

    void TestEnum();
}

