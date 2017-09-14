#include <map>
#include <vector>
#include <iostream>

#include "commonTools.h"

void TestTemplateMap()
{
	std::map<std::string, int> matStrInt= { {"qingya", 1}, {"zijian", 2} };
	std::map<char, int> matCharInt = { {'q',1}, {'z', 2} };
	PrintMap(matStrInt);
	PrintMap(matCharInt);	
}

void TestTemplateVector()
{
	std::vector<int> vecInt = { 1, 2, 4, 5 };
	std::vector<char> vecChar = { 'a', 'b', 'c', 'd' };

	PrintVector(vecInt);
	PrintVector(vecChar);
}

bool IsInterger(const std::string &str)
{
    for (auto i = 0; i < str.length(); ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}