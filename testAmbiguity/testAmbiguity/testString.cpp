#include <iostream>


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