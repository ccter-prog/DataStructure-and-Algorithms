#pragma once

#include <array>
#include <cstddef>

namespace BubbleSort
{
    template <typename T, std::size_t N>
    inline void bubble_sort(std::array<T, N>& arr)
    {
        if constexpr (N <= 1)
        {
            return;
        }
        for (std::size_t count = 0; count < N - 1; ++count)
        {
            bool swap_flag = false;
            for (auto j = arr.begin(); j + 1 != arr.end() - count; ++j)
            {
                if (*j > *(j + 1))
                {
                    T temp = *j;
                    *j = *(j + 1);
                    *(j + 1) = temp;
                    swap_flag = true;
                }
            }
            if (!swap_flag)
            {
                return;
            }
        }
    }
}  // namespace BubbleSort