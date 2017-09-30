#include "singleton.h"
#include <iostream>

namespace TemplateSingleton
{
    class A
    {
    public:
        A()
        {

        }
        void Print()
        {
            std::cout << "class A" << std::endl;
        }
    };

    void TestSingleton()
    {
        A *ptr = Singleton<A>::GetInstance();
        ptr->Print();

        A *ptr1 = Singleton<A>::GetInstance();
        ptr1->Print();

        if (ptr == ptr1)
        {
            std::cout << "singleton pattern is okay." << std::endl;
        }
        delete ptr;
    }
}

namespace SingletonSchemeA
{
    Singleton *Singleton::_instance = nullptr;
    Singleton *Singleton::GetInstance()
    {
        if (nullptr == _instance)
        {
            _instance = new Singleton();
        }
        return _instance;
    }

    /*Singleton::~Singleton()
    {
        if (_instance != nullptr)
        {
            delete _instance;
            _instance = nullptr;
        }
        std::cout << "Singleton destructor" << std::endl;
    }*/

    //Singleton::CGarbo garbo;

    void Test()
    {
        Singleton *ptr = Singleton::GetInstance();
        Singleton *ptr1 = Singleton::GetInstance();
        if (ptr == ptr1)
        {
            std::cout << "singleton is successful." << std::endl;
        }
    }
}