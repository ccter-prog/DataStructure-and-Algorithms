#include "RadixSort.h"
#include <array>
#include <print>

int main()
{
    std::array<int, 11> arr1 = {5, 3, 8, 1, 9, 2, 7, 4, 6, 10, 11};
    RadixSort::radix_sort(arr1);
    std::println("Test1: ");
    for (const auto& i : arr1)
    {
        std::print("{} ", i);
    }
    std::println("\nExpected: 1 2 3 4 5 6 7 8 9 10 11\n");

    std::array<int, 11> arr2 = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 1};
    RadixSort::radix_sort(arr2);
    std::println("Test2: ");
    for (const auto& i : arr2)
    {
        std::print("{} ", i);
    }
    std::println("\nExpected: 1 10 20 30 40 50 60 70 80 90 100\n");

    std::array<int, 11> arr3 = {100, 200, 300, 400, 500, 600, 700, 800, 900, 10, 20};
    RadixSort::radix_sort(arr3);
    std::println("Test 3: ");
    for (const auto& i : arr3)
    {
        std::print("{} ", i);
    }
    std::println("\nExpected: 10 20 100 200 300 400 500 600 700 800 900");
    return 0;
}