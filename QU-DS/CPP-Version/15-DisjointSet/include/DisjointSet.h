#pragma once

#include <cstddef>
#include <map>
#include <memory>
#include <new>
#include <optional>
#include <print>
#include <utility>

template <typename T>
class DisjointSet
{
    public:
        // 特殊函数
        DisjointSet(std::size_t capacity = 0);
        DisjointSet(const DisjointSet& obj);
        DisjointSet(DisjointSet&& obj) noexcept;
    public:
        class Iterator
        {
            public:
                // 友元
                friend class DisjointSet;
            public:
                // 成员函数
                Iterator& operator++();
                T& operator*() const;
                bool operator!=(const Iterator& obj) const;
                bool operator==(const Iterator& obj) const;
            public:
                // 特殊函数
                explicit Iterator(T* data);
            private:
                T* ptr;
        };
    public:
        // 迭代器函数
        Iterator begin() const;
        Iterator end() const;
    public:
        // 运算符重载
        DisjointSet& operator=(const DisjointSet& obj);
        DisjointSet& operator=(DisjointSet&& obj) noexcept;
    public:
        // 成员函数
        bool insert(const T& value);
        void print() const;
        std::optional<std::size_t> find(const T& value);
        bool union_set(const T& value1, const T& value2);
        bool connected(const T& value1, const T& value2);
        bool grow(const std::size_t new_capacity = 0);
        std::size_t get_size() const;
        std::size_t get_capacity() const;
        // private:
        // 私有成员函数
        // void root_update(const std::size_t& root, const std::size_t& index);
        // std::optional<std::size_t> get_index(const T& value);
    private:
        // 私有成员变量
        std::unique_ptr<T[]> m_data;
        std::unique_ptr<std::size_t[]> m_parent;
        std::map<T, std::size_t> m_map;
        std::unique_ptr<std::size_t[]> m_tree_size;
        std::size_t m_capacity;
        std::size_t m_size;
};

template <typename T>
inline DisjointSet<T>::DisjointSet(std::size_t capacity)
    : m_data(new (std::nothrow) T[capacity + 1]),
      m_parent(new (std::nothrow) std::size_t[capacity + 1]),
      m_tree_size(new (std::nothrow) std::size_t[capacity + 1]), m_capacity(0), m_size(0)
{
    if (m_data && m_parent && m_tree_size)
    {
        m_capacity = capacity;
    }
}

template <typename T>
inline DisjointSet<T>::DisjointSet(const DisjointSet<T>& obj)
    : m_data(new (std::nothrow) T[obj.m_capacity + 1]),
      m_parent(new (std::nothrow) std::size_t[obj.m_capacity + 1]), m_map(obj.m_map),
      m_tree_size(new (std::nothrow) std::size_t[obj.m_capacity + 1]), m_capacity(obj.m_capacity),
      m_size(obj.m_size)
{
    if (!m_data || !m_parent || !m_tree_size)
    {
        m_capacity = 0;
        m_size = 0;
        return;
    }
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        m_data[i] = obj.m_data[i];
        m_parent[i] = obj.m_parent[i];
        m_tree_size[i] = obj.m_tree_size[i];
    }
}

template <typename T>
inline DisjointSet<T>::DisjointSet(DisjointSet<T>&& obj) noexcept
    : m_data(std::move(obj.m_data)), m_parent(std::move(obj.m_parent)), m_map(std::move(obj.m_map)),
      m_tree_size(std::move(obj.m_tree_size)), m_capacity(obj.m_capacity), m_size(obj.m_size)
{
    obj.m_capacity = 0;
    obj.m_size = 0;
}

template <typename T>
inline DisjointSet<T>::Iterator::Iterator(T* data) : ptr(data)
{
}

template <typename T>
inline DisjointSet<T>::Iterator& DisjointSet<T>::Iterator::operator++()
{
    ++ptr;
    return *this;
}

template <typename T>
inline T& DisjointSet<T>::Iterator::operator*() const
{
    return *ptr;
}

template <typename T>
inline bool DisjointSet<T>::Iterator::operator!=(const DisjointSet<T>::Iterator& obj) const
{
    return ptr != obj.ptr;
}

template <typename T>
inline bool DisjointSet<T>::Iterator::operator==(const DisjointSet<T>::Iterator& obj) const
{
    return ptr == obj.ptr;
}

template <typename T>
inline DisjointSet<T>::Iterator DisjointSet<T>::begin() const
{
    return Iterator(m_data.get() + 1);
}

template <typename T>
inline DisjointSet<T>::Iterator DisjointSet<T>::end() const
{
    return Iterator(m_data.get() + m_size + 1);
}

template <typename T>
inline DisjointSet<T>& DisjointSet<T>::operator=(const DisjointSet<T>& obj)
{
    if (this == &obj)
    {
        return *this;
    }
    std::unique_ptr<T[]> temp_data(new (std::nothrow) T[obj.m_capacity + 1]);
    std::unique_ptr<std::size_t[]> temp_parent(new (std::nothrow) std::size_t[obj.m_capacity + 1]);
    std::unique_ptr<std::size_t[]> temp_tree_size(new (std::nothrow)
                                                      std::size_t[obj.m_capacity + 1]);
    if (!temp_data || !temp_parent || !temp_tree_size)
    {
        return *this;
    }
    for (std::size_t i = 1; i <= obj.m_size; ++i)
    {
        temp_data[i] = obj.m_data[i];
        temp_parent[i] = obj.m_parent[i];
        temp_tree_size[i] = obj.m_tree_size[i];
    }
    m_map = obj.m_map;
    m_data = std::move(temp_data);
    m_parent = std::move(temp_parent);
    m_tree_size = std::move(temp_tree_size);
    m_capacity = obj.m_capacity;
    m_size = obj.m_size;
    return *this;
}

template <typename T>
inline DisjointSet<T>& DisjointSet<T>::operator=(DisjointSet<T>&& obj) noexcept
{
    if (this == &obj)
    {
        return *this;
    }
    m_data = std::move(obj.m_data);
    m_parent = std::move(obj.m_parent);
    m_map = std::move(obj.m_map);
    m_tree_size = std::move(obj.m_tree_size);
    m_capacity = obj.m_capacity;
    m_size = obj.m_size;
    obj.m_capacity = 0;
    obj.m_size = 0;
    return *this;
}

template <typename T>
inline bool DisjointSet<T>::insert(const T& value)
{
    if (m_size == m_capacity)
    {
        if (!grow())
        {
            return false;
        }
    }
    ++m_size;
    m_data[m_size] = value;
    m_parent[m_size] = 0;
    m_tree_size[m_size] = 1;
    m_map[value] = m_size;
    return true;
}

template <typename T>
inline void DisjointSet<T>::print() const
{
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        std::print("{}\t", i);
    }
    std::println();
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        std::print("{}\t", m_parent[i]);
    }
    std::println();
    for (const auto& i : *this)
    {
        std::print("{}\t", i);
    }
    std::println();
}

template <typename T>
inline std::optional<std::size_t> DisjointSet<T>::find(const T& value)
{
    if (m_map.find(value) == m_map.end())
    {
        return std::nullopt;
    }
    std::size_t i = m_map[value];
    if (m_parent[i] == 0)
    {
        return i;
    }
    std::size_t tmp = i;
    while (m_parent[i] > 0)
    {
        i = m_parent[i];
    }
    while (m_parent[tmp] > 0)
    {
        std::size_t tmp2 = tmp;
        tmp = m_parent[tmp];
        m_parent[tmp2] = i;
    }
    return i;
}

template <typename T>
inline bool DisjointSet<T>::union_set(const T& value1, const T& value2)
{
    std::optional<std::size_t> find_value1(find(value1));
    std::optional<std::size_t> find_value2(find(value2));
    if (!find_value1.has_value() || !find_value2.has_value())
    {
        return false;
    }
    if (*find_value1 == *find_value2)
    {
        return true;
    }
    if (m_tree_size[*find_value1] < m_tree_size[*find_value2])
    {
        m_parent[*find_value1] = *find_value2;
        m_tree_size[*find_value2] = m_tree_size[*find_value2] + m_tree_size[*find_value1];
    }
    else
    {
        m_parent[*find_value2] = *find_value1;
        m_tree_size[*find_value1] = m_tree_size[*find_value1] + m_tree_size[*find_value2];
    }
    return true;
}

template <typename T>
inline bool DisjointSet<T>::connected(const T& value1, const T& value2)
{
    std::optional<std::size_t> a(find(value1));
    std::optional<std::size_t> b(find(value2));
    if (!a.has_value() || !b.has_value())
    {
        return false;
    }
    return *a == *b;
}

template <typename T>
inline bool DisjointSet<T>::grow(const std::size_t new_capacity)
{
    std::size_t new_alloc;
    if (new_capacity > m_capacity)
    {
        new_alloc = new_capacity;
    }
    else if (new_capacity < m_capacity)
    {
        return false;
    }
    else
    {
        new_alloc = m_capacity == 0 ? (m_capacity + 1) * 2 : m_capacity * 2;
    }
    std::unique_ptr<T[]> temp_data(new (std::nothrow) T[new_alloc]);
    std::unique_ptr<std::size_t[]> temp_parent(new (std::nothrow) std::size_t[new_alloc]);
    std::unique_ptr<std::size_t[]> temp_tree_size(new (std::nothrow) std::size_t[new_alloc]);
    if (!temp_data || !temp_parent || !temp_tree_size)
    {
        return false;
    }
    for (std::size_t i = 1; i <= m_size; ++i)
    {
        temp_data[i] = m_data[i];
        temp_parent[i] = m_parent[i];
        temp_tree_size[i] = m_tree_size[i];
    }
    m_data = std::move(temp_data);
    m_parent = std::move(temp_parent);
    m_tree_size = std::move(temp_tree_size);
    m_capacity = new_alloc;
    return true;
}

template <typename T>
inline std::size_t DisjointSet<T>::get_size() const
{
    return m_size;
}

template <typename T>
inline std::size_t DisjointSet<T>::get_capacity() const
{
    return m_capacity;
}

// template <typename T>
// inline void DisjointSet<T>::root_update(const std::size_t& root, const std::size_t& index)
// {
//     std::size_t i = index;
//     while (m_parent[i] > 0)
//     {
//         std::size_t temp = i;
//         i = m_parent[i];
//         m_parent[temp] = root;
//         m_tree_size[temp] = m_tree_size[temp] + m_tree_size[root];
//     }
//     m_tree_size[root] = m_tree_size[root] + m_tree_size[i];
//     m_tree_size[i] = m_tree_size[root];
//     m_parent[i] = root;
// }

// template <typename T>
// inline std::optional<std::size_t> DisjointSet<T>::get_index(const T& value)
// {
//     if (m_map.find(value) == m_map.end())
//     {
//         return std::nullopt;
//     }
//     return m_map[value];
// }