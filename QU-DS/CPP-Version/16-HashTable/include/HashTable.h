#pragma once

#include "Slot.h"
#include <cstddef>
#include <memory>
#include <new>

template <typename T>
class HashTable
{
    public:
        // 特殊函数
        HashTable(std::size_t size);
    private:
        // static成员函数
        static consteval bool is_prime(const std::size_t n);
        static consteval std::size_t find_next_prime(std::size_t n);
    private:
        std::unique_ptr<Slot<T>[]> m_slot;
        std::size_t m_size;
        std::size_t m_remains;
};

template <typename T>
inline HashTable<T>::HashTable(std::size_t size) : m_size(0), m_remains(0)
{
    std::size_t prime = find_next_prime(size);
    m_slot.reset(new (std::nothrow) Slot<T>[prime]);
    if (m_slot)
    {
        m_size = prime;
        m_remains = prime;
    }
}

template <typename T>
inline consteval bool HashTable<T>::is_prime(const std::size_t n)
{
    if (n <= 1)
    {
        return false;
    }
    for (std::size_t i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

template <typename T>
inline consteval std::size_t HashTable<T>::find_next_prime(std::size_t n)
{
    while (!is_prime(n))
    {
        ++n;
    }
    return n;
}