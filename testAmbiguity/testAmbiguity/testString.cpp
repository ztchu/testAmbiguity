#include <iostream>

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
    std::string num("-2147483648");
    if (IsDecimalInterger(num))
    {
        std::cout << "is number" << std::endl;
    }
    else
    {
        std::cout << "is not number" << std::endl;
    }
}