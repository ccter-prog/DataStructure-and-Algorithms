#pragma once

#include <memory>

template <typename T>
class Node
{
    public:
        Node() : data{}, next(nullptr) {}
        explicit Node(T num) : data(num), next(nullptr) {}
    public:
        T data;
        std::unique_ptr<Node> next;
};