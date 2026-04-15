/*
 * 二叉树节点结构，使用 unique_ptr 管理子节点避免手动内存管理
 * height 字段为 AVL 树平衡因子预留，初始化为 0 表示叶子高度
 */

#pragma once

#include <memory>

template <typename Elem>
struct BinNode
{
    // 默认构造函数初始化 height 为 0，便于 AVL 树高度计算
    BinNode();

    // 数据成员
    Elem data;
    // height 用于 AVL 树平衡，-1 表示空节点，0 表示叶子
    int height;
    // 使用 unique_ptr 自动管理子节点内存，防止内存泄漏
    std::unique_ptr<BinNode> left;
    std::unique_ptr<BinNode> right;
};

template <typename Elem>
inline BinNode<Elem>::BinNode() : height(0)
{

}