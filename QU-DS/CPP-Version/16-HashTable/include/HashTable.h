#pragma once

#include "Slot.h"
#include <cstddef>
#include <memory>
#include <new>
#include <optional>
#include <print>
#include <utility>

template <typename T>
class HashTable
{
    public:
        // 特殊函数
        HashTable(std::size_t size);
    public:
        bool full() const;
        bool insert(const T& value);
        void print() const;
        void remove(const T& value);
        std::optional<std::size_t> find(const T& value) const;
    private:
        // 私有成员函数
        bool grow();
        void find_slot(std::size_t& index) const;
        void find_slot(const Slot<T>* ptr, std::size_t& index, const std::size_t size) const;
    private:
        // static成员函数
        static constexpr bool is_prime(const std::size_t n);
        static constexpr std::size_t find_next_prime(std::size_t n);
        static constexpr std::size_t hash(const T& value, const std::size_t size);
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
inline bool HashTable<T>::full() const
{
    return m_remains == 0;
}

template <typename T>
inline bool HashTable<T>::insert(const T& value)
{
    if (full())
    {
        if (!grow())
        {
            return false;
        }
    }
    std::size_t index = hash(value, m_size);
    find_slot(index);
    m_slot[index].value = value;
    m_slot[index].status = GridStatus::Active;
    --m_remains;
    return true;
}

template <typename T>
inline void HashTable<T>::print() const
{
    for (std::size_t i = 0; i < m_size; ++i)
    {
        std::println("{}", m_slot[i]);
    }
}

template <typename T>
inline void HashTable<T>::remove(const T& value)
{
    std::optional<std::size_t> op(find(value));
    if (!op.has_value())
    {
        return;
    }
    m_slot[*op].status = GridStatus::Delete;
    ++m_remains;
}

template <typename T>
inline std::optional<std::size_t> HashTable<T>::find(const T& value) const
{
    std::size_t index = hash(value, m_size);
    for (std::size_t i = 0; i < m_size; ++i, index = (index + 1) % m_size)
    {
        if (m_slot[index].status == GridStatus::Empty)
        {
            return std::nullopt;
        }
        else if (m_slot[index].value == value && m_slot[index].status != GridStatus::Delete)
        {
            return index;
        }
    }
    return std::nullopt;
}

template <typename T>
inline bool HashTable<T>::grow()
{
    std::size_t new_alloc_size = find_next_prime(m_size * 2);
    std::unique_ptr<Slot<T>[]> temp(new (std::nothrow) Slot<T>[new_alloc_size]);
    if (!temp)
    {
        return false;
    }
    std::size_t count = 0;
    for (std::size_t i = 0; i < m_size; ++i)
    {
        // if (m_slot[i].status == GridStatus::Delete)
        // {
        //     continue;
        // }
        std::size_t index = hash(m_slot[i].value, new_alloc_size);
        find_slot(temp.get(), index, new_alloc_size);
        temp[index] = m_slot[i];
        ++count;
    }
    m_slot = std::move(temp);
    m_size = new_alloc_size;
    m_remains = new_alloc_size - count;
    return true;
}

template <typename T>
inline void HashTable<T>::find_slot(std::size_t& index) const
{
    while (m_slot[index].status == GridStatus::Active)
    {
        index = (index + 1) % m_size;
    }
}

template <typename T>
inline void
HashTable<T>::find_slot(const Slot<T>* ptr, std::size_t& index, const std::size_t size) const
{
    while (ptr[index].status == GridStatus::Active)
    {
        index = (index + 1) % size;
    }
}


template <typename T>
inline constexpr bool HashTable<T>::is_prime(const std::size_t n)
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
inline constexpr std::size_t HashTable<T>::find_next_prime(std::size_t n)
{
    while (!is_prime(n))
    {
        ++n;
    }
    return n;
}

template <typename T>
inline constexpr std::size_t HashTable<T>::hash(const T& value, const std::size_t size)
{
    return static_cast<std::size_t>(value) % size;
}