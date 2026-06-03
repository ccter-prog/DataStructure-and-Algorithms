#pragma once

#include <array>
#include <cstddef>

template <typename T, std::size_t N>
inline void selection_sort(typename std::array<T, N>::iterator begin,
                           typename std::array<T, N>::iterator end)
{
    T min = *begin;
    typename std::array<T, N>::iterator index = begin;
    while (begin != end)
    {
        for (auto i = begin + 1; i != end; ++i)
        {
            if (min > *i)
            {
                min = *i;
                index = i;
            }
        }
        if (index != begin)
        {
            T temp = *begin;
            *begin = min;
            *index = temp;
        }
        ++begin;
    }
}

template <typename T, std::size_t N>
inline void selection_sort(std::array<T, N>& arr)
{
    T min = *(arr.begin());
    typename std::array<T, N>::iterator index = arr.begin();
}