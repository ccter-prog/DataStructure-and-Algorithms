#pragma once

#include "Slot.h"
#include <cstddef>
#include <memory>
#include <new>


template <typename T>
class HashTable
{
    public:
        HashTable(std::size_t capacity);
    private:
        std::unique_ptr<Slot<T>[]> m_slot;
        std::size_t m_size;
        std::size_t m_remains;
};

template <typename T>
inline HashTable<T>::HashTable(std::size_t size)
{
}