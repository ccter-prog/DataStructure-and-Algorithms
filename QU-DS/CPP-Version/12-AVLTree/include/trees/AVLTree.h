#pragma once

#include "BSTree.h"
#include "BinTree.h"
#include <algorithm>
#include <expected>
#include <stack>

template <typename Elem>
class AVLTree
{
    public:
        // 特殊函数
        explicit AVLTree(BSTree<Elem>& bst);
    public:
        // 普通成员函数
        std::expected<BinNode<Elem>*, const char*> insert(const Elem& value);
    private:
        // 私有成员函数
        int height(BinNode<Elem>* r) const noexcept;
        void LLrotate(BinNode<Elem>* parent) noexcept;
        void RRrotate(BinNode<Elem>* parent) noexcept;
        void LRrotate(BinNode<Elem>* node, BinNode<Elem>* parent) noexcept;
        void RLrotate(BinNode<Elem>* node, BinNode<Elem>* parent) noexcept;
    private:
        // 组合
        BSTree<Elem>& m_bst;
};

template <typename Elem>
inline AVLTree<Elem>::AVLTree(BSTree<Elem>& bst) : m_bst(bst)
{

}

template <typename Elem>
inline std::expected<BinNode<Elem>*, const char*> AVLTree<Elem>::insert(const Elem& value)
{
    BinTree<Elem>& bt = m_bst.get_bt();
    std::unique_ptr<BinNode<Elem>> temp(bt.make_node());
    if (!temp)
    {
        return std::unexpected("内存分配失败");
    }
    temp -> data = value;
    BinNode<Elem>* p = bt.get_root();
    if (!p)
    {
        bt.root_reset(temp.release());
        return bt.get_root();
    }
    std::stack<BinNode<Elem>*> path;
    BinNode<Elem>* parent = nullptr;
    while (p)
    {
        path.push(p);
        parent = p;
        if (value > p -> data)
        {
            p = p -> right.get();
        }
        else if (value < p -> data)
        {
            p = p -> left.get();
        }
        else
        {
            return std::unexpected("不能有相同的节点元素");
        }
    }
    BinNode<Elem>* result = nullptr;
    if (value > parent -> data)
    {
        parent -> right = std::move(temp);
        result = parent -> right.get();
    }
    else
    {
        parent -> left = std::move(temp);
        result = parent -> left.get();
    }
    while (!path.empty())
    {
        BinNode<Elem>* node = path.top();
        path.pop();
        node -> height = std::max(height(node -> left.get()), height(node -> right.get())) + 1;
        if (height(node -> left.get()) - height(node -> right.get()) == 2)
        {
            if (value < node -> left -> data)
            {
                LLrotate(node);
            }
            else
            {
                LRrotate(node);
            }
        }
        else if (height(node -> right.get()) - height(node -> left.get()) == 2)
        {
            if (value > node -> right -> data)
            {
                RRrotate(node);
            }
            else
            {
                RLrotate(node);
            }
        }
    }
    return result;
}

template <typename Elem>
inline int AVLTree<Elem>::height(BinNode<Elem>* r) const noexcept
{
    return !r ? -1 : r -> height;
}

template <typename Elem>
inline void AVLTree<Elem>::LLrotate(BinNode<Elem>* parent) noexcept
{

    BinTree<Elem>& bt = m_bst.get_bt();
    if (!parent)
    {
        BinNode<Elem>* tmp_root = bt.get_root_release();
        bt.root_reset(tmp_root -> left.release());
        BinNode<Elem>* new_root = bt.get_root();
        new_root -> right.reset(tmp_root);
        return;
    }
    BinNode<Elem>* tmp_node = parent -> left.release();  // 获取node的所有权
    parent -> left.reset(tmp_node -> left.release());
    BinNode<Elem>* tmp_parent_lr = nullptr;
    if (parent -> left -> right)
    {
        tmp_parent_lr = parent -> left -> right.release();
    }
    parent -> left -> right.reset(tmp_node);
    if (tmp_parent_lr)
    {
        parent -> left -> right -> left.reset(tmp_parent_lr);
    }
}

template <typename Elem>
inline void AVLTree<Elem>::RRrotate(BinNode<Elem>* parent) noexcept
{
    BinTree<Elem>& bt = m_bst.get_bt();
    if (!parent)
    {
        BinNode<Elem>* tmp_root = bt.get_root_release();
        bt.root_reset(tmp_root -> right.release());
        BinNode<Elem>* new_root = bt.get_root();
        new_root -> left.reset(tmp_root);
        return;
    }
    BinNode<Elem>* tmp_node = parent -> right.release();  // 获得node所有权
    parent -> right.reset(tmp_node -> right.release());
    BinNode<Elem>* tmp_parent_rl = nullptr;
    if (parent -> right -> left)
    {
        tmp_parent_rl = parent -> right -> left.release();
    }
    parent -> right -> left.reset(tmp_node);
    if (tmp_parent_rl)
    {
        parent -> right -> left -> right.reset(tmp_parent_rl);
    }
}