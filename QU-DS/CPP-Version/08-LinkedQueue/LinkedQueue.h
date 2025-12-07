#pragma once

#include "Node.h"
#include <memory>
#include <new>

template <typename T>
class LinkedQueue
{
    public:
        // 特殊成员函数
        LinkedQueue();
    public:
        // 普通成员函数
        bool isEmpty() const;
        bool enQueue(const T& rx);
        bool deQueue();
        bool Front(T& rx) const;
        int getSize() const;
        void clear();
    private:
        std::unique_ptr<Node<T>> m_front;
        Node<T>* m_rear;
        int m_size;
};

template <typename T>
inline LinkedQueue<T>::LinkedQueue() : m_rear(nullptr), m_size(0)
{}

template <typename T>
inline bool LinkedQueue<T>::isEmpty() const
{
    return m_front == nullptr;
}

template <typename T>
inline bool LinkedQueue<T>::enQueue(const T& rx)
{
    bool ret = false;
    std::unique_ptr<Node<T>> newNode(new(std::nothrow) Node<T>);
    if (newNode)
    {
        newNode -> data = rx;
        m_size++;
        ret = true;
        if (m_front)
        {
            m_rear -> next = std::move(newNode);
            m_rear = m_rear -> next.get();
        }
        else
        {
            m_front = std::move(newNode);
            m_rear = m_front.get();
        }
    }
    return ret;
}

template <typename T>
inline bool LinkedQueue<T>::deQueue()
{
    bool ret = false;
    if (m_front && m_front -> next)
    {
        m_front = std::move(m_front -> next);
        m_size--;
        ret = true;
    }
    else if (m_front)
    {
        m_front.reset();
        m_rear = nullptr;
        m_size--;
        ret = true;
    }
    return ret;
}

template <typename T>
inline bool LinkedQueue<T>::Front(T& rx) const
{
    bool ret = false;
    if (!isEmpty())
    {
        rx = m_front -> data;
        ret = true;
    }
    return ret;
}

template <typename T>
inline int LinkedQueue<T>::getSize() const
{
    return m_size;
}

template <typename T>
inline void LinkedQueue<T>::clear()
{
    m_front.reset();
    m_rear = nullptr;
    m_size = 0;
}