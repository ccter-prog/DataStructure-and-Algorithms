#pragma once

#include <memory>

template <typename Elem>
struct BinNode
{
    Elem data;
    std::unique_ptr<BinNode> left;
    std::unique_ptr<BinNode> right;
};