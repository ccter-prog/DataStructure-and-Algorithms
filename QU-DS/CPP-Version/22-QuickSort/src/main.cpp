#include "QuickSort.h"
#include <print>
#include <array>

int main()
{
    std::array<int, 5> arr({77, 44, 22, 78, 90});
    QuickSort::quick_sort(arr);
    for (const auto& i : arr)
    {
        std::println("{}", i);
    }
	return 0;
}