#pragma once
#include <vector>
#include <string>

double TranslateStrValToDouble(const Size&  elementSize, const Location& elementLocation, const Size& slideSize,
    const std::string & attrName, const std::string &strVal);

void TestExpression();
