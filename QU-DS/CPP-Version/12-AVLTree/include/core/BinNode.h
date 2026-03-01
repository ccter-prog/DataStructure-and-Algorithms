#pragma once

#include <memory>

template <typename Elem>
struct BinNode
{
    // 构造函数
    BinNode();

    // 数据
    Elem data;
    int height;
    std::unique_ptr<BinNode> left;
    std::unique_ptr<BinNode> right;
};

template <typename Elem>
inline BinNode<Elem>::BinNode() : height(0)
{
    
}