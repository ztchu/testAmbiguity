#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>

#include "commonTools.h"
#define _USE_MATH_DEFINES

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
    if (len == 0)
    {
        return false;
    }
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

const double M_PI = 3.14159265358979323846;
//const double DBL_EPSILON = 1E-6;
bool TranslateAngleToPoint(const double angle, Location &point1, Location &point2)
{
    if (angle >= 360 || angle < 0)
    {
        return false;
    }
    if (90 == angle)
    {
        point1 = { 0, 0 };
        point2 = { 0, 1 };
        return true;
    }
    if (270 == angle)
    {
        point1 = {0, 1};
        point2 = {0, 0};
        return true;
    }

    double tanAns = tan(angle / 180.0 * M_PI);
    if ((angle >= 0 && angle < 90) || (angle > 270 && angle < 360))
    {
        point1.x = 0;
        point2.x = 1;
        if (tanAns > 0)
        {
            point1.y = 0;
            point2.y = tanAns;
        }
        else if (tanAns == 0)
        {
            point1.y = 0;
            point2.y = 0;
        }
        else
        {
            point2.y = 0;
            point1.y = 0 - tanAns;
        }
    }
    else if (angle > 90 && angle < 270)
    {
        point1.x = 1;
        point2.x = 0;
        if (tanAns > 0)
        {
            point1.y = tanAns;
            point2.y = 0;
        }
        else if (tanAns == 0)
        {
            point1.y = 0;
            point2.y = 0;
        }
        else 
        {
            point1.y = 0;
            point2.y = 0 - tanAns;
        }
    }

    double point1Max = std::max(point1.x, point1.y);
    if (point1Max > DBL_EPSILON)
        point1 = { point1.x / point1Max, point1.y / point1Max };

    double point2Max = std::max(point2.x, point2.y);
    if (point2Max > DBL_EPSILON)
        point2 = { point2.x / point2Max, point2.y / point2Max };
    return true;
}