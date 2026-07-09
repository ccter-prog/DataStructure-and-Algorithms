#pragma once

#include <array>
#include <cstddef>

namespace MergeSort
{
    template <std::size_t N>
    inline void merge(std::array<int, N>& array,
                      std::array<int, N>& temp_array,
                      std::size_t left_begin,
                      std::size_t right_begin,
                      std::size_t right_end)
    {
        std::size_t left_end = right_begin - 1;
        std::size_t temp_array_index = left_begin;
        std::size_t temp_left_begin = left_begin;
        std::size_t temp_right_end = right_end;
        while (left_begin <= left_end && right_begin <= right_end)
        {
            if (array[left_begin] <= array[right_begin])
            {
                temp_array[temp_array_index++] = array[left_begin++];
            }
            else
            {
                temp_array[temp_array_index++] = array[right_begin++];
            }
        }
        while (left_begin <= left_end)
        {
            temp_array[temp_array_index++] = array[left_begin++];
        }
        while (right_begin <= right_end)
        {
            temp_array[temp_array_index++] = array[right_begin++];
        }
        while (temp_left_begin <= temp_right_end)
        {
            array[temp_left_begin] = temp_array[temp_left_begin];
            ++temp_left_begin;
        }
    }

    template <std::size_t N>
    inline void merge_sort(std::array<int, N>& array)
    {
        if constexpr (N < 2)
        {
            return;
        }
        std::array<int, N> temp_array(array);
        for (std::size_t width = 1; width < N; width <<= 1)
        {
            for (std::size_t left = 0; left < N - width; left += (width << 1))
            {
                std::size_t mid = left + width;
                std::size_t right_end = left + (width << 1) - 1;
                if (right_end >= N)
                {
                    right_end = N - 1;
                }
                merge(array, temp_array, left, mid, right_end);
            }
        }
    }
}  // namespace MergeSort