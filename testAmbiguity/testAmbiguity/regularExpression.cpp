#include "regularExpression.h"
#include <string>
#include <regex>
#include <iostream>

void TestFileName()
{
    std::regex pattern(R"(([^<>/\\\\|:""\*\?]+)\.pptx$)");
    //std::regex pattern(R"(([^\\/]+)\.pptx$)");
    std::string filePath("E:\\Total_project\\PPTX_resolution\\test\\CycloneOffice\\Code\\TestResources\\chuzhongtao\\数学公式\\formula.pptx");
    //std::string filePath("//formula.pptx");
    std::smatch result;
    bool ret = std::regex_search(filePath, result, pattern);
    if (ret && !result.empty())
    {
        std::cout << result[0] << std::endl;
    }

}