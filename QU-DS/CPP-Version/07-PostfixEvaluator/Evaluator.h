#pragma once

template <typename T, typename B>
auto cal(T a, B b, char ob)
{
    // T ret;
    switch (ob)
    {
        case '+':
        {
            // ret = a + b;
            return a + b;
            // break;
        }
        case '-':
        {
            // ret = a - b;
            return a - b;
            // break;
        }
        case '*':
        {
            // ret = a * b;
            // break;
            return a * b;
        }
        case '/':
        {
            // ret = a / b;
            // break;
            return a / b;
        }
    }
    // return ret;
}