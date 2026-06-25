#include "HeapSort.h"
#include <array>
#include <print>

int main()
{
    std::array<int, 5> arr({3532, 35, 45, 345, 3});
    for (const auto& i : arr)
    {
        std::println("{}", i);
    }
    HeapSort::heap_sort(arr);
    for (const auto& i : arr)
    {
        std::println("{}", i);
    }
    return 0;
}