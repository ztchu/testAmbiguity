#pragma once
#include <iostream>

namespace TemplateSingleton
{
    template<typename T>
    class Singleton
    {
    public:
        static T *GetInstance();
        ~Singleton();

    private:
        Singleton();
        Singleton(const Singleton& other);
        Singleton& operator=(const Singleton& other);

        static T* _instance;
    };

    template<typename T>
    T* Singleton<T>::_instance = new T();

    template<typename T>
    T *Singleton<T>::GetInstance()
    {
        return _instance;
    }

    template<typename T>
    Singleton<T>::Singleton(const Singleton& other)
    {

    }

    template<typename T>
    Singleton<T>& Singleton<T>::operator=(const Singleton& other)
    {

    }

    template<typename T>
    Singleton<T>::~Singleton()
    {
        if (_instance != nullptr)
        {
            delete _instance;
            _instance = nullptr;
        }
    }

    void TestSingleton();
}

namespace SingletonSchemeA
{
    class Singleton
    {
    public:
        static Singleton *GetInstance();
        

    private:
        Singleton()
        {

        }
        Singleton(const Singleton &other) = delete;
        Singleton &operator=(const Singleton &other) = delete;

    private:
        static Singleton *_instance;

        class CGarbo
        {
        public:
            ~CGarbo()
            {
                if (_instance != nullptr)
                {
                    delete _instance;
                    _instance = nullptr;
                }
                std::cout << "Singleton destructor" << std::endl;
            }

        };
        static CGarbo garbo;
    };

    void Test();
}
