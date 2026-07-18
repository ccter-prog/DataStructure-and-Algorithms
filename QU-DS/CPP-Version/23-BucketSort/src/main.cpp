#include "BucketSort.h"
#include <array>
#include <print>

int main()
{
    std::array<int, 10> array({1, 3, 5, 9, 7, 4, 2, 6, 8});
    BucketSort::bucket_sort(array);
    for (const auto& i : array)
    {
        std::print("{} ", i);
    }
    std::println();
    return 0;
}