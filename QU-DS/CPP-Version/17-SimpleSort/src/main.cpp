#include "simple_sort.h"
#include <array>
#include <cstddef>
#include <print>

int main()
{
    std::array<int, 6> array({19, 54, 4, 30, 70, 2});
    insertion_sort(array);
    for (auto i : array)
    {
        std::println("{}", i);
    }
    return 0;
}