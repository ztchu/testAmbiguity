#include <map>
#include <vector>
#include <iostream>
#include <set>

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

const int MAX_LEN_OF_INTERGER = 10;
const std::string MAX_POSITIVE_INTERGER_STR("2147483647");
const std::string MAX_NEGATIVE_INTERGER_STR("2147483648");
bool IsDecimalInterger(const std::string &numberToBeTested)
{
    std::string tempNum(numberToBeTested);
    int len = tempNum.length();
    bool isNegative = false;
    if (len > 1 && tempNum[0] == '-')
    {
        isNegative = true;
        tempNum = tempNum.substr(1, len - 1);
        len = len - 1;
    }
    if (len <= MAX_LEN_OF_INTERGER)
    {
        if (MAX_LEN_OF_INTERGER == len)
        {
            if (!isNegative && tempNum > MAX_POSITIVE_INTERGER_STR)
            {
                return false;
            }
            if (isNegative && tempNum > MAX_NEGATIVE_INTERGER_STR)
            {
                return false;
            }
        }
        for (auto i = 0; i < tempNum.length(); ++i)
        {
            if ((tempNum[i] >= '0' && tempNum[i] <= '9'))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    else if (len > MAX_LEN_OF_INTERGER)
    {
        return false;
    }

    return true;
}

bool IsHexInterger(const std::string &numberToBeTested)
{
    int len = numberToBeTested.length();
    if (len <= 2 || len > 10)
    {
        return false;
    }
    
    if (numberToBeTested.compare(0, 2, "0x") == 0 || numberToBeTested.compare(0, 2, "0X") == 0)
    {
        for (int i = 2; i < len; ++i)
        {
            char ch = numberToBeTested[i];
            if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool IsInterger(const std::string &numberToBeTested)
{
    if (IsHexInterger(numberToBeTested) || IsHexInterger(numberToBeTested))
    {
        return true;
    }
    return false;
}

bool IsFloat(const std::string& numberToBeTested)
{
    std::set<char> reasonableCharSet{ 'e', 'E', '+', '-', '.', '0', '1' };
    std::set<char> uniqueCharSet;
    for (int i = 0; i < numberToBeTested.length(); ++i)
    {
        if (reasonableCharSet.find(numberToBeTested[i]) == reasonableCharSet.end())
        {
            return false;
        }
    }
    return true;
}