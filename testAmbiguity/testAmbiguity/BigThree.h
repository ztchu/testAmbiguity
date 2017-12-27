#pragma once
#include <string>

namespace BigThree
{
    class B;

    class A
    {
    public:
        
    private:
        A()
        {

        }
        const std::string val = "test";
        friend class B;
    };

    class B
    {
    public:
        B()
        {

        }
        const A val1;

    };

    void TestBigThree();

    const std::string Repeat("test");
    //enum RegisteredName{ Repeat };
}
