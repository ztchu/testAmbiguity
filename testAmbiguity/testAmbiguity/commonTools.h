#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

template <typename TKey, typename TValue>
void PrintMap(const std::map<TKey, TValue> &map)
{
	for (auto iter = map.begin(); iter != map.end(); ++iter)
	{
		std::cout << iter->first << ": " << iter->second << std::endl;
	}
}

template <typename T>
void PrintVector(const std::vector<T> &vec)
{
	for (auto iter = vec.begin(); iter != vec.end(); ++iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}

void TestTemplateMap();
inline void TestTemplateVector()
{
    std::vector<int> vecInt = { 1, 2, 4, 5 };
    std::vector<char> vecChar = { 'a', 'b', 'c', 'd' };

    PrintVector(vecInt);
    PrintVector(vecChar);
}

struct Size
{
    double Width;
    double Height;
};
struct Location
{
    double x;
    double y;
};

struct RelativeRect
{
    double left;
    double top;
    double right;
    double bottom;
};

bool IsDecimalInterger(const std::string &str);

RelativeRect TranslateAngleToPoint(const double angle);

void TestIsFloat();

RelativeRect TranslateAngleToPointA(double angle);

void TestIfDefine();