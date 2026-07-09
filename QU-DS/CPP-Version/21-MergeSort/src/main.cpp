#include "MergeSort.h"
#include <array>
#include <print>

int main()
{
    std::array<int, 10> array({10, 5, 8, 2, 4, 6, 3});
    for (const auto& i : array)
    {
        std::print("{} ", i);
    }
    std::println();
    MergeSort::merge_sort(array);
    for (const auto& i : array)
    {
        std::print("{} ", i);
    }
    std::println();
    return 0;
}