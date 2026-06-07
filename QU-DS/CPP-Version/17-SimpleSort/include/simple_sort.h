#pragma once

#include <array>
#include <cstddef>

template <typename T, std::size_t N>
inline void selection_sort(typename std::array<T, N>::iterator begin,
                           typename std::array<T, N>::iterator end)
{
    if (begin == end)
    {
        return;
    }
    while (begin != end - 1)
    {
        T min = *begin;
        typename std::array<T, N>::iterator index = begin;
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
    for (auto i = arr.begin(); i != arr.end() - 1; ++i)
    {
        T min = *i;
        typename std::array<T, N>::iterator index = i;
        for (auto k = i + 1; k != arr.end(); ++k)
        {
            if (min > *k)
            {
                min = *k;
                index = k;
            }
        }
        if (index != i)
        {
            T temp = *i;
            *i = min;
            *index = temp;
        }
    }
}

template <typename T, std::size_t N>
inline void insertion_sort(std::array<T, N>& arr)
{
    if constexpr (N <= 1)
    {
        return;
    }
    for (auto i = arr.begin() + 1; i != arr.end(); ++i)
    {
        if (*i < *(i - 1))
        {
            auto j = i;
            T temp = *j;
            for (; j != arr.begin(); --j)
            {
                if (temp < *(j - 1))
                {
                    *j = *(j - 1);
                    continue;
                }
                break;
            }
            *j = temp;
        }
    }
}