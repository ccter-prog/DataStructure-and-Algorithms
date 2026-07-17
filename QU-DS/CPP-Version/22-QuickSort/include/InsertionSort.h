#pragma once

#include <cstddef>
#include <span>

namespace InsertionSort
{
    inline void insertion_sort(std::span<int> array)
    {
        if (array.size() < 2)
        {
            return;
        }
        for (std::size_t i = 1; i < array.size(); ++i)
        {
            if (array[i] < array[i - 1])
            {
                int temp_value = array[i];
                std::size_t j = i;
                for (; j > 0 && array[j - 1] > temp_value; --j)
                {
                    array[j] = array[j - 1];
                }
                array[j] = temp_value;
            }
        }
    }
}  // namespace InsertionSort