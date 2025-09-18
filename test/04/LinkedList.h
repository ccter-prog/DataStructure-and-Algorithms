#pragma once

#include "Node.h"
#include <memory>
#include <iostream>
#include <utility>

template <typename T>
class LinkedList
{
    public:
        LinkedList() : head(nullptr), tail(nullptr) {}
        void add(T num);
        void print() const;
        Node<T>* search(T num);
        void del(T num);
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
        Node<T>* temp_tail(p.get());
        tail -> next = std::move(p);
        tail = temp_tail;
    }
    else
    {
        head = std::move(p);
        tail = head.get();
    }
}

template <typename T>
inline void LinkedList<T>::print() const
{
    Node<T>* list(head.get());
    for (; list != nullptr; list = list -> next.get())
    {
        std::cout << list -> data << '\n';
    }
}

template <typename T>
inline Node<T>* LinkedList<T>::search(T num)
{
    Node<T>* list(head.get());
    for (; list != nullptr && list -> data != num; list = list -> next.get());
    return list;  // 如果找到了会返回那段地址，如果没找到会返回nullptr
}

template <typename T>
inline void LinkedList<T>::del(T num)
{
    if (!head)
    {
        return;
    }
    Node<T>* list(head.get());
    Node<T>* temp(nullptr);
    for (; list != nullptr && list -> data != num; temp = list, list = list -> next.get());
    if (list)  // 循环结束后如果list为真则会进入进行删除操作，否则说明没有找到
    {
        if (temp)
        {
            Node<T>* next_node(list -> next.get());
            temp -> next = std::move(list -> next);
            if (!next_node)
            {
                tail = temp;
            }
        }
        else
        {
            head = std::move(head -> next);
            if (!head)
            {
                tail = nullptr;
            }
        }
    }
}