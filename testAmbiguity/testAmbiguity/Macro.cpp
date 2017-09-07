#include <map>
#include <string>

#include "Macro.h"
#include "commonTools.h"

#define INSERT_DIC_MAP(typeName)\
if (1)\
{\
	int len = strlen(typeName);\
	strCount[typeName] = len;\
}

void TestMacroIf()
{
	std::map<std::string, int> strCount;

	INSERT_DIC_MAP("qingya")
	INSERT_DIC_MAP("zijian")
	INSERT_DIC_MAP("ziguyilai")

	PrintMap(strCount);
}