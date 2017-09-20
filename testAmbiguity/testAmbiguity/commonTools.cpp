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
    static std::set<char> reasonableCharSet{ 'e', 'E', '+', '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    for (int i = 0; i < numberToBeTested.length(); ++i)
    {
        if (reasonableCharSet.find(numberToBeTested[i]) == reasonableCharSet.end())
        {
            return false;
        }
    }
    return true;
}

void TestIsFloat()
{
    std::string str("indefinite");

    if (IsFloat(str))
    {
        std::cout << "is float" << std::endl;
    }
    else
    {
        std::cout << "is not float" << std::endl;
    }
}

const double M_PI = 3.14159265358979323846;
//const double DBL_EPSILON = 1E-6;
RelativeRect TranslateAngleToPoint(const double angle)
{
    RelativeRect rect{0, 0, 0, 0};
    if (angle >= 360 || angle < 0)
    {
        return rect;
    }
    if (90 == angle)
    {
        //point1 = { 0, 0 };
        //point2 = { 0, 1 };
        /*rect.left = 0;
        rect.top = 0;
        rect.right = 0;
        rect.bottom = 1;*/
        rect = { 0, 0, 0, 1 };
    }
    if (270 == angle)
    {
        //point1 = {0, 1};
        //point2 = {0, 0};
        //rect.right = 0;
        //rect.bottom = 0;
        rect = { 0, 1, 0, 0 };
    }
    
    double tanAns = tan(angle / 180.0 * M_PI);
    if ((angle >= 0 && angle < 90) || (angle > 270 && angle < 360))
    {
        rect.left = 0;
        rect.right = 1;
        if (tanAns > 0)
        {
            rect.top = 0;
            rect.bottom = tanAns;
        }
        else if (tanAns == 0)
        {
            rect.top = 0;
            rect.bottom = 0;
        }
        else
        {
            rect.top = 0 - tanAns;
            rect.bottom = 0;
        }
    }
    else if (angle > 90 && angle < 270)
    {
        rect.left = 1;
        rect.right = 0;

        if (tanAns > 0)
        {
            rect.top = tanAns;
            rect.bottom = 0;
        }
        else if (tanAns == 0)
        {
            rect.top = 0;
            rect.bottom = 0;
        }
        else 
        {
            rect.top = 0;
            rect.bottom = 0 - tanAns;
        }
    }

    double point1Max = std::max(rect.left, rect.top);
    if (point1Max > 1)
    {
        rect.left = rect.left / point1Max;
        rect.top = rect.top / point1Max;
    }

    double point2Max = std::max(rect.right, rect.bottom);
    if (point2Max > 1)
    {
        rect.right = rect.right / point2Max;
        rect.bottom = rect.bottom / point2Max;
    }
    return rect;
}

RelativeRect TranslateAngleToPointA(double angle)
{
    RelativeRect rect{0, 0, 0, 0};
    if (angle >= 360 || angle < 0)
    {
        return rect;
    }
    double sinVal = sin(angle / 180.0 * M_PI);
    double cosVal = cos(angle / 180.0 * M_PI);
    double maxVal = std::max(sinVal > 0 ? sinVal : 0 - sinVal, cosVal > 0 ? cosVal : 0 - cosVal);

    if (maxVal > DBL_EPSILON)
    {
        rect.right = cosVal / maxVal;
        rect.bottom = sinVal / maxVal; //enbx中的坐标轴和ppt中的坐标轴的y轴方向刚好相反
    }

    if (rect.right < 0 - DBL_EPSILON)
    {
        rect.left += 1;
        rect.right += 1;
    }
    if (rect.bottom < 0 - DBL_EPSILON)
    {
        rect.top += 1;
        rect.bottom += 1;
    }
    
    return rect;
}