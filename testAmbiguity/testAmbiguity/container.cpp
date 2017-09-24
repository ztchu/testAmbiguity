#include <map>
#include <iostream>



#include "container.h"

void TestMapContaioner()
{
    std::map<int, int> mat{ {1, 2} };

    auto iter = mat.begin();
    
    std::cout << mat[1] << std::endl;
    std::cout << mat[2] << std::endl;
}

void TestPair()
{
    std::pair<int, int> pa{ 1, 2 };
    pa.first;
}

