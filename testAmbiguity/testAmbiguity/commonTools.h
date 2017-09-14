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
void TestTemplateVector();

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

bool IsDecimalInterger(const std::string &str);

