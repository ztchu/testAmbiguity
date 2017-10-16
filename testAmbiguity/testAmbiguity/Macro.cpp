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

/*
#define Type std::string
void TestMacroDefine()
{
    int a = 3;
    if (a == 1)
    {
#define TYPE std::string;
    }
    else if (a == 2)
    {
#define TYPE std::
    }
    
}*/

#define Debug(var, ...) std::cout << var << ## __VA_ARGS__ << std::endl;

void TestDebug()
{
    Debug("zijian", "qingya");
    //Debug("qingya");
}

#define XNAME(n) x##n

void TestReplace()
{
    int XNAME(3);
    XNAME(3) = 4;
    std::cout << XNAME(3) << std::endl;
}


