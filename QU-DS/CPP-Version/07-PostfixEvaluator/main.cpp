#include "Evaluator.h"
#include <iostream>
#include <format>

int main()
{
    Evaluator eval;
    eval.getString();
    eval.cal();
    std::cout << std::format("{}\n", eval.StackTOP());
    return 0;
}