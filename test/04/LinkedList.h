#pragma once

#include "Node.h"
#include <memory>
#include <iostream>
#include <utility>

template <typename T>
class LinkedList
{
    public:
        // 特殊成员函数
        LinkedList() : head(nullptr), tail(nullptr) {}
    public:
        // 添加迭代器
        class iterator
        {
            public:
                // 特殊成员函数
                iterator(Node<T>* ptr = nullptr) : current(ptr) {}
            public:
                friend LinkedList<T>;
            public:
                // 运算符重载
                T& operator*() { return current -> data; }
                iterator& operator++() { current = current -> next.get(); return *this; }
                iterator operator++(int);
                bool operator==(const iterator& other) const { return current == other.current; }
                bool operator!=(const iterator& other) const { return current != other.current; }
            private:
                Node<T>* current;
        };
    public:
        // 迭代器函数
        iterator begin() { return iterator(head.get()); }
        iterator end() { return iterator(nullptr); }
        iterator begin() const { return iterator(head.get()); }
        iterator end() const { return iterator(nullptr); }
        // 普通成员函数   
        // 修改操作函数
        void add(T num);
        void push_front(const T& value);
        void pop_front();
        iterator insert_after(iterator pos, const T& value);
        iterator erase_after(iterator pos);
        void remove(const T& value);
        void clear() { head.reset(); tail = nullptr; }
        void swap(LinkedList& other) noexcept;
        void unique();
        void splice_after(iterator pos, LinkedList<T>& other);
        void sort();
        template <typename Compare>
        void sort(Compare comp);
        // 元素访问函数
        void print() const;
        T& front() { return head -> data; }
        Node<T>* search(T num);
        // 容量相关函数
        bool empty() { return head.get() == nullptr; }
    private:
        std::unique_ptr<Node<T>> head;
        Node<T>* tail;
};

template <typename T>
inline void LinkedList<T>::add(T num)
{
    std::unique_ptr<Node<T>> p = std::make_unique<Node<T>>(num);
    if (head)
    {
        tail -> next = std::move(p);
        tail = tail -> next.get();
    }
    else
    {
        head = std::move(p);
        tail = head.get();
    }
}

template <typename T>
inline void LinkedList<T>::push_front(const T& value)
{
    std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>(value);
    if (head)
    {
        new_node -> next = std::move(head);
    }
    head = std::move(new_node);
    if (!tail)
    {
        tail = head.get();
    }
}

template <typename T>
inline void LinkedList<T>::pop_front()
{
    if (!head)
    {
        return;
    }
    if (head.get() == tail)
    {
        tail = nullptr;
    }
    head = std::move(head -> next);
}

template <typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::insert_after(typename LinkedList<T>::iterator pos, const T& value)
{
    if (pos == end())
    {
        return pos;
    }
    Node<T>* current_node = pos.current;
    std::unique_ptr<Node<T>> new_node = std::make_unique<Node<T>>(value);
    new_node -> next = std::move(current_node -> next);
    current_node -> next = std::move(new_node);
    if (tail == current_node)
    {
        tail = current_node -> next.get();
    }
    return iterator(current_node -> next.get());
}

template <typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::erase_after(typename LinkedList<T>::iterator pos)
{
    if (pos == end())
    {
        return pos;
    }
    Node<T>* current_node = pos.current;
    Node<T>* old_node = current_node -> next.get();

    if (old_node && old_node -> next)
    {
        current_node -> next = std::move(old_node -> next);
    }
    else if (old_node)
    {
        current_node -> next.reset();
        tail = current_node;
    }
    return iterator(current_node -> next.get());
}

template <typename T>
inline void LinkedList<T>::remove(const T& value)
{
    if (!head)
    {
        return;
    }
    Node<T>* temp = nullptr;
    for (Node<T>* list = head.get(); list != nullptr; temp = list, list = list -> next.get())
    {
        if (temp && list -> data == value)
        {
            if (list -> next)
            {
                temp -> next = std::move(list -> next);
                list = temp;
            }
            else
            {
                temp -> next.reset();
                tail = temp;
            }
        }
        else if (list -> data == value)
        {
            if (head -> next)
            {
                head = std::move(head -> next);
                list = head.get();
            }
            else
            {
                head.reset();
                tail = nullptr;
                break;
            }
        }
    }
}

template <typename T>
inline void LinkedList<T>::swap(LinkedList<T>& other) noexcept
{
    head.swap(other.head);
    Node<T>* temp = tail;
    tail = other.tail;
    other.tail = temp;
}

template <typename T>
inline void LinkedList<T>::unique()
{
    Node<T>* p = head.get();
    while (p != nullptr && p -> next)
    {
        if (p -> data == p -> next -> data)
        {
            p -> next = std::move(p -> next -> next);
        }
        else
        {
            p = p -> next.get();
        }
    }
}

template <typename T>
inline void LinkedList<T>::splice_after(typename LinkedList<T>::iterator pos, LinkedList<T>& other)
{
    Node<T>* current_node = pos.current;
    std::unique_ptr<Node<T>> temp;
    temp.swap(current_node -> next);
    current_node -> next = std::move(other.head);
    other.tail -> next = std::move(temp);
}

template <typename T>
inline void LinkedList<T>::sort()
{
    if (!head)
    {
        return;
    }
    for (Node<T>* p = head.get(), *j = nullptr; p; j = p, p = p -> next.get())
    {
        for (Node<T>* q = p -> next.get(), *i = nullptr; q; i = q, q = q -> next.get())
        {
            if (p == head.get() && p -> data > q -> data)  // 为第一轮循环头节点交换做准备
            {
                Node<T>* temp = head.release();
                head = q == p -> next.get() ? std::move(temp -> next) : std::move(i -> next);
                temp -> next = std::move(q -> next);
                head -> next = temp;
            }
            else if (p -> data > q -> data)  // 不检查j指针的原因是当第一个条件分支进不去时就意味着第一层循环过去了
            {
                Node<T>* temp = j -> next.release();
                j -> next = std::move(p -> next);
                p -> next -> next = temp;

            }
        }
    }
}

template <typename T>
inline void LinkedList<T>::print() const
{
    for (auto& i : *this)
    {
        std::cout << i << '\n';
    }
}

template <typename T>
inline Node<T>* LinkedList<T>::search(T num)
{
    Node<T>* list = head.get();
    for (; list != nullptr && list -> data != num; list = list -> next.get());
    return list;  // 如果找到了会返回那段地址，如果没找到会返回nullptr
}

template <typename T>
inline typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(int)
{
    iterator temp = *this;
    ++(*this);
    return temp;
}