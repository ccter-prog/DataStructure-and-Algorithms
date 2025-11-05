#include <iostream>
#include "SimpleStack.h"

int main()
{
    SimpleQueue arr;
    arr.push(1);
    arr.push(2);
    arr.push(3);
    for (auto i : arr)
    {
        std::cout << i << ' ';
    }
    std::cout.put('\n');
    return 0;
}