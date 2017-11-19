#include "Enum.h"
#include <iostream>

namespace Enum
{
    Person::Person(int age, const std::string & name)
    {

    }

    MyName Person::GetName() const
    {
        return _name;
    }

    int Person::GetAge() const
    {
        return _age;
    }

    void TestEnum()
    {
        Person person;
        if (person.GetAge() == 0)
        {
            std::cout << "Age is Okay" << std::endl;
        }
        else
        {
            std::cout << "Age is Failed" << std::endl;
        }

        if (person.GetName() == MyName::None)
        {
            std::cout << "MyName is Okay" << std::endl;
        }
        else
        {
            std::cout << "MyName is Failed" << std::endl;
        }
    }
}