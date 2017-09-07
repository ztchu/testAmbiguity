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