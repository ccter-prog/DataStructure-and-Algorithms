#pragma once

#include <vector>
#include <cstddef>
#include <optional>

class SimpleQueue
{
    public:
        SimpleQueue() : frontIndex(0) {}
    public:
        void push(int value);
        void pop();
        void shrink();
        bool empty() { return frontIndex >= data.size(); }
        std::size_t size() { return data.size() - frontIndex; }
        std::optional<int> front();
    private:
        std::vector<int> data;
        std::size_t frontIndex;
};

inline void SimpleQueue::push(int value)
{
    data.push_back(value);
}

inline void SimpleQueue::pop()
{
    if (frontIndex < data.size())
    {
        frontIndex++;
    }
}

inline void SimpleQueue::shrink()
{
    if (frontIndex > data.size() / 2)
    {
        data.erase(data.begin(), data.begin() + static_cast<long>(frontIndex));
        frontIndex = 0;
    }
}

inline std::optional<int> SimpleQueue::front()
{
    if (frontIndex >= data.size())
    {
        return std::nullopt;
    }
    return data[frontIndex];
}