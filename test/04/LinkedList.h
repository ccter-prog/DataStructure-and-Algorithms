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