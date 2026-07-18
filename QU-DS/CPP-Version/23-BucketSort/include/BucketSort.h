#pragma once

#include <array>
#include <vector>

/* 根据老师指定的场景，元素值的大小不会超过N */

namespace BucketSort
{
    // 声明
    template <std::size_t N>
    void bucket_sort(std::array<int, N>& array);

    // 定义
    template <std::size_t N>
    void bucket_sort(std::array<int, N>& array)
    {
        std::array<std::vector<int>, N + 1> temp_array;
        for (auto& i : array)
        {
            temp_array[i].push_back(i);
        }
        std::size_t list = 0;
        for (std::size_t i = 0; i <= N; ++i)
        {
            while (!temp_array[i].empty())
            {
                array[list++] = temp_array[i].back();
                temp_array[i].pop_back();
            }
        }
    }
}  // namespace BucketSort