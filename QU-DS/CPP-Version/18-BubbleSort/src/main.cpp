#include "BubbleSort.h"
#include <array>
#include <print>

int main()
{
    std::array<int, 8> arr({10, 9, 8, 7, 6, 5, 4, 3});
    BubbleSort::bubble_sort(arr);
    for (const auto& i : arr)
    {
        std::println("{}", i);
    }
    return 0;
}