#pragma once

#include <array>
#include <cstddef>
#include <print>

namespace shell_sort
{
    template <std::size_t N>
    inline constexpr void shell_sort(std::array<int, N>& arr)
    {
        if constexpr (N <= 1)
        {
            return;
        }
        std::size_t gap = 1;
        while (gap < N / 2)
        {
            gap = gap * 2 + 1;
        }
        while (gap > 0)
        {
            std::size_t i = 0;
            while (i + gap < N)
            {
                int temp_value = arr[i + gap];
                std::size_t j = i + gap;
                while (j >= gap && arr[j - gap] > temp_value)
                {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp_value;
                ++i;
            }
            gap = (gap - 1) / 2;
        }
    }

    template <typename T, std::size_t N>
    inline void print(const std::array<T, N>& arr)
    {
        for (const auto& i : arr)
        {
            std::println("{}", i);
        }
    }
}  // namespace shell_sort