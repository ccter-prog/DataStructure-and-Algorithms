#pragma once

#include "InsertionSort.h"
#include <array>
#include <cstddef>
#include <span>
#include <utility>

#define CUTOFF 3


namespace QuickSort
{
    template <std::size_t N>
    inline int
    median_pivot(std::array<int, N>& array, const std::size_t left, const std::size_t right)
    {
        std::size_t mid = (left + right) / 2;
        if (array[left] > array[mid])
        {
            std::swap(array[left], array[mid]);
        }
        if (array[left] > array[right])
        {
            std::swap(array[left], array[right]);
        }
        if (array[mid] > array[right])
        {
            std::swap(array[mid], array[right]);
        }
        std::swap(array[mid], array[right - 1]);
        return array[right - 1];
    }

    template <std::size_t N>
    inline bool try_insertion_sort(std::array<int, N>& array, const std::size_t left, const std::size_t right)
    {
        if (right - left < CUTOFF)
        {
            InsertionSort::insertion_sort(std::span<int, N >(array).subspan(left, right - left + 1));
            return true;
        }
        return false;
    }

    template <std::size_t N>
    void q_sort(std::array<int, N>& array, std::size_t left, std::size_t right)
    {
        if (try_insertion_sort(array, left, right))
        {
            return;
        }
        else
        {
            int pivot = median_pivot(array, left, right);

            /* left + 1 因为median_pivot函数已经把选的3个数中的最小值放在了0号位置
             * 同理 right - 2 因为末尾的那个位置是3个数中最大的，而 right - 1 为pivot的位置
             */

            std::size_t i = left + 1;
            std::size_t j = right - 2;
            while (i < j)
            {
                while (array[i] < pivot)
                {
                    ++i;
                }
                while (array[j] > pivot)
                {
                    --j;
                }
                if (i < j)
                {
                    std::swap(array[i], array[j]);
                    ++i, --j;  // 保证每次循环体执行后i和j至少有一个发生了移动
                }
            }
            std::swap(array[i], array[right - 1]);
            q_sort(array, left, i - 1);
            q_sort(array, i + 1, right);
        }

    }

    template <std::size_t N>
    inline void quick_sort(std::array<int, N>& array)
    {
        if constexpr (N < 2)
        {
            return;
        }
        q_sort(array, 0, N - 1);
    }
}  // namespace QuickSort