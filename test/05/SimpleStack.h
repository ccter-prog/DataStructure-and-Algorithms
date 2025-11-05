#pragma once

#include <vector>

class SimpleQueue
{
    public:
        SimpleQueue() : topIndex(-1) {}
    public:
        void push(int value);
        void pop();
        int top() { return data[static_cast<unsigned long>(topIndex)]; }
        bool empty() { return topIndex == -1; }
        auto begin() noexcept { return data.begin(); }
        auto end() noexcept { return data.end(); }
    private:
        std::vector<int> data;
        int topIndex;
};

inline void SimpleQueue::push(int value)
{
    data.push_back(value);
    topIndex++;
}

inline void SimpleQueue::pop()
{
    if (topIndex >= 0)
    {
        data.pop_back();
        topIndex--;
    }
}