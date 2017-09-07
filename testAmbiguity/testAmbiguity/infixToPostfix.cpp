#include <string>
#include <stack>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

#include "commonTools.h"
#include "infixToPostfix.h"


std::string DeleteSpaceFromStr(const std::string &strVal)
{
    std::string ans;
    for (auto i = 0; i < strVal.length(); ++i)
    {
        if (strVal[i] != ' ')
        {
            ans.push_back(strVal[i]);
        }
    }
    return ans;
}

std::stack<std::string> TranslateInfixToPostfix(const Size&  elementSize, const Location& elementLocation, const Size& slideSize, const std::string &str)
{
    std::stack<std::string> operatorStk;
    std::stack<std::string> mediaAnsStk;

    std::string strVal = DeleteSpaceFromStr(str);

    std::map<std::string, double> symbolMapVal{ { "#ppt_x", elementLocation.x / slideSize.Width },{ "#ppt_y", elementLocation.y / slideSize.Height },
    { "#ppt_w", elementSize.Width / slideSize.Width },{ "#ppt_h", elementSize.Height / slideSize.Height },
    { "ppt_x", elementLocation.x / slideSize.Width },{ "ppt_y", elementLocation.y / slideSize.Height },
    { "ppt_w", elementSize.Width / slideSize.Width },{ "ppt_h", elementSize.Height / slideSize.Height } };
    std::map<char, std::pair<int, std::string>> operatorPriority{ { ',',{ 0, "," } },{ '+',{ 1, "+" } },{ '-',{ 1, "-" } },{ '*',{ 2, "*" } },{ '/',{ 2, "/" } },{ 'm',{ 3, "" }}};

    for (int i = 0; i < strVal.length();)
    {
        int pos = i;
        while (pos < strVal.length() && strVal[pos] != '(' && strVal[pos] != ')')
        {
            if (strVal[pos] == '-')
            {
                if (pos == 0 || operatorPriority.find(strVal[pos - 1]) != operatorPriority.end() || strVal[pos - 1] == '(')
                {
                    ++pos;
                    continue;
                }               
            }
            if (operatorPriority.find(strVal[pos]) == operatorPriority.end())
            {
                ++pos;//break;
            }
            else
            {
                break;
            }
        }
        std::string subStr = strVal.substr(i, pos - i);   //取运算数
        if (!subStr.empty())
        {
            std::string noSymbol = subStr.substr(1, subStr.length() - 1);
            if (symbolMapVal.find(subStr) != symbolMapVal.end())
            {
                mediaAnsStk.push(std::to_string(symbolMapVal[subStr]));
            }
            else if (symbolMapVal.find(noSymbol) != symbolMapVal.end())
            {
                mediaAnsStk.push(std::to_string(0 - symbolMapVal[noSymbol]));
            }
            else
            {
                mediaAnsStk.push(subStr);
            }
        }
        if (pos == strVal.length())
        {
            break;
        }
        if (strVal[pos] == '(')
        {
            operatorStk.push("(");
        }
        else if (strVal[pos] == ')' || strVal[pos] == ',')
        {
            while (!operatorStk.empty() && operatorStk.top() != "(")
            {
                mediaAnsStk.push(operatorStk.top());
                operatorStk.pop();
            }
            if (strVal[pos] != ',')
                operatorStk.pop();//弹出左括号
        }
        else if (strVal[pos] == 'm')
        {
            std::string func = strVal.substr(pos, 3);
            operatorStk.push(func);
            i = pos + 3;
            continue;
        }
        else   //+-*/
        {
            bool flag = true;
            while (flag)
            {
                flag = false;
                if (operatorStk.empty())
                {
                    operatorStk.push(operatorPriority[strVal[pos]].second);
                }
                else
                {
                    if (operatorStk.top() == "(")
                    {
                        operatorStk.push(operatorPriority[strVal[pos]].second);
                        break;
                    }
                    if (operatorPriority[strVal[pos]].first > operatorPriority[operatorStk.top()[0]].first)
                    {
                        operatorStk.push(operatorPriority[strVal[pos]].second);
                        break;
                    }
                    else
                    {
                        mediaAnsStk.push(operatorStk.top());
                        operatorStk.pop();
                        flag = true;
                    }
                }
            }
        } 
        i = pos + 1;
    }
    while (!operatorStk.empty())
    {
        mediaAnsStk.push(operatorStk.top());
        operatorStk.pop();
    }
    while (!mediaAnsStk.empty())
    {
        std::cout << mediaAnsStk.top() << " ";
        operatorStk.push(mediaAnsStk.top());
        mediaAnsStk.pop();
    }
    return operatorStk;
}

double TranslateStrValToDouble(const Size&  elementSize, const Location& elementLocation, const Size& slideSize,
    const std::string & attrName, const std::string &strVal)
{
    std::stack<std::string> stkPostfix = TranslateInfixToPostfix(elementSize, elementLocation, slideSize, strVal);

    std::stack<double> stkMedian;
    while (!stkPostfix.empty())
    {
        if (stkPostfix.top() == "+" || stkPostfix.top() == "-" || stkPostfix.top() == "*" || stkPostfix.top() == "/" || 
            stkPostfix.top() == "max" || stkPostfix.top() == "min")
        {
            double rightArg = stkMedian.top();
            stkMedian.pop();
            double leftArg = stkMedian.top();
            stkMedian.pop();

            if (stkPostfix.top() == "+")
            {
                stkMedian.push(leftArg + rightArg);
            }
            else if (stkPostfix.top() == "-")
            {
                stkMedian.push(leftArg - rightArg);
            }
            else if (stkPostfix.top() == "*")
            {
                stkMedian.push(leftArg * rightArg);
            }
            else if (stkPostfix.top() == "/")
            {
                stkMedian.push(leftArg / rightArg);
            }
            else if (stkPostfix.top() == "max")
            {
                stkMedian.push(std::max(leftArg, rightArg));
            }
            else if (stkPostfix.top() == "min")
            {
                stkMedian.push(std::min(leftArg, rightArg));
            }
            stkPostfix.pop();
        }
        else
        {
            stkMedian.push(std::stod(stkPostfix.top()));
            stkPostfix.pop();
        }
    }
    if (attrName == "ppt_x" || attrName == "ppt_w")
    {
        return stkMedian.top() * slideSize.Width;
    }
    else if (attrName == "ppt_y" || attrName == "ppt_h")
    {
        return stkMedian.top() * slideSize.Height;
    }
}

void TestExpression()
{
    Size elementSize = { 0.5, 0.5 };
    Location elementLocation = { 0.6, 0.6 };
    Size slideSize = { 1, 1 };
    std::string attrName = "ppt_x";
    //std::string strVal = "-6/2-1+5+max(3,2)";
    //std::string strVal = "max(0.3*0.4, .3)";
    //std::string strVal = "(6*min(max(#ppt_w*#ppt_h,.3),1)-7.4)/-.7*#ppt_w";
    //std::string strVal = "#ppt_y + #ppt_h*1.125000";
    std::string strVal = "-ppt_w";
    double ans = TranslateStrValToDouble(elementSize, elementLocation, slideSize, attrName, strVal);
    std::cout << ans << std::endl;
}


