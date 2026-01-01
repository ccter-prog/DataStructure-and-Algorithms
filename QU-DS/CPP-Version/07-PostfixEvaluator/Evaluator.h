#pragma once

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

class Evaluator
{
    public:
        // 普通函数
        bool cal();
        void getString();
        double StackTOP();
        bool StackTOP(double& value);
        bool StackPOP();
    private:
        std::stack<double> m_dStack;
        std::vector<std::string> m_tokens;
};

inline bool Evaluator::cal()
{
    bool ret = true;
    while (m_dStack.size() != 0)
    {
        m_dStack.pop();
    }
    for (auto& i : m_tokens)
    {
        if (i != "+" && i != "-" && i != "*" && i != "/")
        {
            m_dStack.push(std::stod(i));   
        }
        else
        {
            double temp1;
            double temp2;
            if (m_dStack.size() < 2)
            {
                std::cerr << "错误：操作数不足！\n";
                if (!m_dStack.empty())
                {
                    m_dStack.pop();
                }
                ret = false;
                goto end;
            }
            StackTOP(temp1);
            StackPOP();
            StackTOP(temp2);
            StackPOP();
            char c = i.at(0);
            switch (c)
            {
                case '+':
                {
                    m_dStack.push(temp2 + temp1);
                    break;
                }
                case '-':
                {
                    m_dStack.push(temp2 - temp1);
                    break;
                }
                case '*':
                {
                    m_dStack.push(temp2 * temp1);
                    break;
                }
                case '/':
                {
                    if (std::fabs(temp1) > 1e-10)
                    {
                        m_dStack.push(temp2 / temp1);
                    }
                    else
                    {
                        std::cerr << "右操作数不应为0或太小！\n";
                        ret = false;
                        goto end;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }   
        }
    }
end:
    return ret;
}

inline void Evaluator::getString()
{
    std::string str;
    std::string token;
    m_tokens.clear();
    std::cout << "请输入：";
    std::getline(std::cin, str);
    std::istringstream iss(str);
    while (iss >> token)
    {
        m_tokens.emplace_back(token);
    }
}

inline double Evaluator::StackTOP()
{
    double ret = -1.0;
    if (!m_dStack.empty())
    {
        ret = m_dStack.top();
    }
    return ret;
}

inline bool Evaluator::StackTOP(double& value)
{
    bool ret = false;
    if (!m_dStack.empty())
    {
        value = m_dStack.top();
        ret = true;
    }
    return ret;
}

inline bool Evaluator::StackPOP()
{
    bool ret = false;
    if (!m_dStack.empty())
    {
        m_dStack.pop();
        ret = true;
    }
    return ret;
}
