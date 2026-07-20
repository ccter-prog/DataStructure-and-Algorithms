#include "RadixSort.h"
#include <array>
#include <print>

int main()
{
    std::array<int, 11> array({23, 45, 12, 56, 1, 6, 90, 998, 223, 111, 123});
    RadixSort::radix_sort(array);
    for (const auto& i : array)
    {
        std::print("{} ", i);
    }
    std::println();
    return 0;
}