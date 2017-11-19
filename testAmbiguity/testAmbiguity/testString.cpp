#include <iostream>
#include <cmath>
#include <string>

#include "commonTools.h"
#include "testString.h"

bool TestStringSzchar(const std::string &src, const char *dst)
{
	if (src == std::string(dst))
		return true;
	else
		return false;
}

void TestStringSzchar()
{
	std::string src;
	std::cout << "empty string is ";
	if (TestStringSzchar(src, ""))
	{
		std::cout << "equal ";
	}
	else
	{
		std::cout << "not equal ";
	}
	std::cout << "to \"\""  << std::endl;
}

void DeleteFrontAndRearSpace(std::string &str)
{
    if (str.empty())
    {
        return;
    }

    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
}

void TestDeleteFrontAndRearSpace()
{
    std::string str(" qingya   zijian");
    DeleteFrontAndRearSpace(str);
    std::cout << str;// << std::endl;
}

void TestIfStrIsPureNum()
{
    std::string num(".3E+3");
    std::cout << std::stod(num) << std::endl;
    std::string num1("0.336ad");
    std::cout << std::stod(num1) << std::endl;
}

void TestIsInterger()
{
    std::string num("-2147483648");
    std::cout << std::stoi(num, 0, 0) << std::endl;
    std::string num1("56");
    std::cout << std::stoi(num1, 0, 0) << std::endl;
    std::string num2("0xfffAfff");
    std::cout << std::stoi(num2, 0, 0) << std::endl;
    std::string num3(".3E+3");
    std::cout << std::stod(num3) << std::endl;
}

void TestIsDecimalInterger()
{
    std::string num("");
    if (IsDecimalInterger(num))
    {
        std::cout << "is number" << std::endl;
    }
    else
    {
        std::cout << "is not number" << std::endl;
    }
}

void TestTan()
{
    double ans = tan(90 / 180.0 * 3.14159265358979323846);
    std::cout << ans << std::endl;
}

void TestTranslateAngleToPoint()
{
    //Location point1, point2;
    RelativeRect rect;
    double angle = 359;
    rect = TranslateAngleToPoint(angle);
    {
        std::cout << "x:" << rect.left << "," << "y:" << rect.top << std::endl;
        std::cout << "x:" << rect.right << "," << "y:" << rect.bottom << std::endl;
    }
}

std::string GetFamousAuthor(int index)
{
    switch (index % 3)
    {
    case 0: return "qingya";
        break;
    case 1: return "zijian";
        break;
    case 2: return "zhuiyuan";
        break;
    }
}

void TestGetFamousAuthor()
{
    int index = 2;
    std::cout << GetFamousAuthor(index) << std::endl;
    std::cout << GetFamousAuthor(index).c_str() << std::endl;
    const char *ptr = GetFamousAuthor(index).c_str();   //��ʱ��������
    std::cout << ptr << std::endl;
}

void TestStringClass()
{
    String str("qingya");
    const char *ptr = str;
    std::cout << ptr << std::endl;

    std::cout << std::endl;
    double angle = 45;
    RelativeRect rect1;
    rect1 = TranslateAngleToPointA(angle);
    {
        std::cout << "x:" << rect1.left << "," << "y:" << rect1.top << std::endl;
        std::cout << "x:" << rect1.right << "," << "y:" << rect1.bottom << std::endl;
    }
}

void TestStrCompare()
{
    std::string sr("qingya.pptx");
    if (sr.compare(sr.length() - 5, 5, ".pptx") == 0)
    {
        std::cout << "okay" << std::endl;
    }
    else
    {
        std::cout << "failed." << std::endl;
    }
}

void TestUppercaseToLowercase()
{
    std::string str("s");

    if (str[0] >= 97 && str[0] <= 122)
    {
        str[0] -= 32;
    }
    std::cout << str << std::endl;

    std::string str1("s");
    if (str1.compare(0, str1.length(), "Z") > 0)
    {
        std::cout << str1 << std::endl;
    }
}

void TestFindLastNotOf()
{
    std::string str("qingya");
    str.erase(str.find_last_not_of(" ") + 1);
    std::cout << str << std::endl;
}

void TestStringL()
{
    std::string str("qingya");
    std::cout << L"qingya" << std::endl;
}

enum class Qing {qing, zi};

void TestEnumClass()
{
    Qing var = Qing::qing;
    std::cout << static_cast<int>(var) << std::endl;
    std::cout << static_cast<int>(Qing::zi) << std::endl;
}

void TestCharInitString()
{
    char str[] = { "qingya" };
    std::string qing(str, 4);
    std::cout << qing << std::endl;
}

