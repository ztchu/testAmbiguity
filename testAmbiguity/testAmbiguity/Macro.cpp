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

#define PRINT(value) printf(#value "= %d\n", value)

#define FUNC(arg) print##arg()\
    {\
        printf(#arg "= %d", arg);\
    }

#define WARN_IF(EXP) \
do{\
std::cout << "Warning:" << #EXP << std::endl; \
}while(0)

#define DECLARE_FUN_NAME_ADD(type) ADD##type
//#define ADD(type) DECLARE_FUN_NAME_ADD(type)

#define DECLARE_ADD(type)\
type DECLARE_FUN_NAME_ADD(type)(type n1, type n2)\
{\
    return n1 + n2;\
}

DECLARE_ADD(int)

void TestMacro()
{
    PRINT(3);
    int ans = DECLARE_FUN_NAME_ADD(int)(1, 3);
    std::cout << "ans = " << ans << std::endl;
    WARN_IF(divider == 0);
}
