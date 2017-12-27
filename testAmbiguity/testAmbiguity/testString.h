#pragma once

#include <string>
//class string;

bool TestStringSzchar(const std::string &src, const char *dst);

void TestStringSzchar();

void DeleteFrontAndRearSpace(std::string &str);
void TestDeleteFrontAndRearSpace();

void TestIfStrIsPureNum();
void TestIsInterger();
void TestIsDecimalInterger();

void TestTan();
void TestTranslateAngleToPoint();

void TestGetFamousAuthor();

class String
{
public:
    String(const char *str)
    {
        _data = new char[strlen(str) + 1];
        strcpy_s(_data, strlen(str) + 1, str);
    }
    ~String()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }
    }
    inline operator const char *()
    {
        return _data;
    }
private:
    char *_data = nullptr;
};

void TestStringClass();
void TestTranslateAngleToPoint();

void TestStrCompare();

void TestUppercaseToLowercase();

void TestFindLastNotOf();

void TestStringL();

void TestEnumClass();

void TestCharInitString();

void TestStringToBool();

void TestU8(const std::string &val = u8"��");

//void TestU8(const std::string &val);

class TestU8Str
{
public:
    TestU8Str(const std::string &val)
    {
        if (val == u8"��")
        {
            _text = val;
        }
    }
private:
    std::string _text = u8"��";
};



//class EString
//{
//
//public:
//    static EString& GetInstance()
//    {
//        static EString instance;
//        return instance;
//    }
//    std::string value() const
//    {
//        return _val;
//    }
//
//public:
//    const EString& EmptyEString = "";
//
//public:  //element animation property
//    const EString& RepeatCount = u8"�ظ�����";
//    const EString& ParagraphAnimation = u8"���䶯��";
//
//public:   //transition property
//    const EString& TransitionSound = u8"�л���������";
//    const EString& SettingAutomaticSwitchingTime = u8"�����Զ���Ƭʱ��";
//
//public:   //common property
//    const EString& DelayTime = u8"�ӳ�ʱ��";  //animation & transition property
//
//
//private:
//    EString()
//    {
//
//    }
//    EString(const std::string& val)
//        :_val(val)
//    {
//
//    }
//    EString(const char* val)
//        :_val(val)
//    {
//
//    }
//
//private:
//    std::string _val;
//};

void TestReferenceStr();

template<typename T>
decltype(auto) move(T&& param)
{
    using ReturnType = remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}

