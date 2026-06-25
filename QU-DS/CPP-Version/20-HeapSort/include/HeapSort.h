#pragma once

#include <array>
#include <cstddef>

namespace HeapSort
{
    template <std::size_t N>
    inline void
    percolate_down(std::array<int, N>& arr, const std::size_t index, const std::size_t size)
    {
        int temp_value = arr[index];
        std::size_t i = index;
        while (i * 2 + 1 < size)
        {
            std::size_t child = i * 2 + 1;
            if (child + 1 < size && arr[child] < arr[child + 1])
            {
                ++child;
            }
            if (temp_value < arr[child])
            {
                arr[i] = arr[child];
                i = child;
            }
            else
            {
                break;
            }
        }
        arr[i] = temp_value;
    }

    template <std::size_t N>
    inline void heap_sort(std::array<int, N>& arr)
    {
        if constexpr (N <= 1)
        {
            return;
        }
        for (std::size_t i = N / 2; i > 0; --i)
        {
            percolate_down(arr, i - 1, N);
        }
        for (std::size_t i = N - 1; i > 0; --i)
        {
            int temp_value = arr[0];
            arr[0] = arr[i];
            arr[i] = temp_value;
            percolate_down(arr, 0, i);
        }
    }
}  // namespace HeapSort