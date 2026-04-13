#pragma once

#include "BSTree.h"
#include "BinTree.h"
#include <algorithm>
#include <expected>
#include <stack>
#include <utility>
#include <optional>

template <typename Elem>
class AVLTree
{
    public:
        // 特殊函数
        explicit AVLTree(BSTree<Elem>& bst);      
    public:
        // 普通成员函数
        std::expected<BinNode<Elem>*, const char*> insert(const Elem& value) noexcept;
        bool remove(const Elem& x) noexcept;
    private:
        // 私有成员函数
        int height(BinNode<Elem>* r) const noexcept;
        void LLrotate(BinNode<Elem>* parent) noexcept;
        void RRrotate(BinNode<Elem>* parent) noexcept;
        void LRrotate(BinNode<Elem>* parent) noexcept;
        void RLrotate(BinNode<Elem>* parent) noexcept;
        void updateHeight(BinNode<Elem>* node) noexcept;
        std::optional<std::stack<BinNode<Elem>*>> get_findx_parent(const Elem& x) noexcept;
    private:
        // 组合
        BSTree<Elem>& m_bst;
};

template <typename Elem>
inline AVLTree<Elem>::AVLTree(BSTree<Elem>& bst) : m_bst(bst)
{

}

template <typename Elem>
inline std::expected<BinNode<Elem>*, const char*> AVLTree<Elem>::insert(const Elem& value) noexcept
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
        path.size() > 0 ? parent = path.top() : nullptr;
        updateHeight(node);
        if (height(node -> left.get()) - height(node -> right.get()) >= 2)
        {
            if (value < node -> left -> data)
            {
                LLrotate(parent);
            }
            else
            {
                LRrotate(parent);
            }
        }
        else if (height(node -> right.get()) - height(node -> left.get()) >= 2)
        {
            if (value > node -> right -> data)
            {
                RRrotate(parent);
            }
            else
            {
                RLrotate(parent);
            }
        }
    }
    return result;
}

template <typename Elem>
inline bool AVLTree<Elem>::remove(const Elem& x) noexcept
{
    std::optional<std::stack<BinNode<Elem>*>> op(get_findx_parent(x));
    if (!op)
    {
        return false;
    }
    std::stack<BinNode<Elem>*> st(op.value());
    BinNode<Elem>* parent = st.size() > 0 ? st.top() : nullptr;
    BinNode<Elem>* node = nullptr;
    BinTree<Elem>& bt = m_bst.get_bt();
    if (!parent)
    {
        node = bt.get_root();
    }
    else
    {
        node = parent -> data > x ? parent -> right.get() : parent -> left.get();
    }
    if (node -> left && node -> right)
    {
        BinNode<Elem>* MaxLeftParent = node;
        BinNode<Elem>* MaxLeft = node -> left.get();
        while (MaxLeft -> right)
        {
            st.push(MaxLeftParent);
            MaxLeftParent = MaxLeft;
            MaxLeft = MaxLeft -> right.get();
        }
        node -> data = MaxLeft -> data;
        if (MaxLeftParent == node)
        {
            node -> left = std::move(MaxLeft -> left);
        }
        else
        {
            MaxLeftParent -> right = std::move(MaxLeft -> right);
        }
        goto end;
    }
    if (st.size() == 0)
    {
        BinNode<Elem>* root = bt.get_root();
        if (root -> left)
        {
            bt.root_move(root -> left);
        }
        else if (root -> right)
        {
            bt.root_move(root -> right);
        }
        else
        {
            bt.root_reset(nullptr);
        }
    }
end:
    while (!st.empty())
    {
        BinNode<Elem>* temp = st.top();
        updateHeight(temp);
        st.pop();
    }
    return true;
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
    BinNode<Elem>* tmp_root = parent ? parent -> left.release() : bt.get_root_release();
    BinNode<Elem>* new_root = tmp_root -> left.release();
    tmp_root -> left = std::move(new_root -> right);
    new_root -> right.reset(tmp_root);
    parent ? parent -> left.reset(new_root) : bt.root_reset(new_root);
    updateHeight(tmp_root);
    updateHeight(new_root);
}

template <typename Elem>
inline void AVLTree<Elem>::RRrotate(BinNode<Elem>* parent) noexcept
{
    BinTree<Elem>& bt = m_bst.get_bt();
    BinNode<Elem>* tmp_root = parent ? parent -> right.release() : bt.get_root_release();
    BinNode<Elem>* new_root = tmp_root -> right.release();
    tmp_root -> right = std::move(new_root -> left);
    new_root -> left.reset(tmp_root);
    parent ? parent -> right.reset(new_root) : bt.root_reset(new_root);
    updateHeight(tmp_root);
    updateHeight(new_root);
}

template <typename Elem>
inline void AVLTree<Elem>::LRrotate(BinNode<Elem>* parent) noexcept
{
    BinTree<Elem>& bt = m_bst.get_bt();
    BinNode<Elem>* tmp_root = parent ? parent -> left.release() : bt.get_root_release();
    BinNode<Elem>* tmp_lr = tmp_root -> left -> right.release();
    tmp_root -> left -> right = std::move(tmp_lr -> left);
    BinNode<Elem>* tmp_l = tmp_root -> left.release();
    tmp_root -> left = std::move(tmp_lr -> right);
    tmp_lr -> right.reset(tmp_root);
    tmp_lr -> left.reset(tmp_l);
    parent ? parent -> left.reset(tmp_lr) : bt.root_reset(tmp_lr);
    updateHeight(tmp_l);
    updateHeight(tmp_root);
    updateHeight(tmp_lr);
}

template <typename Elem>
inline void AVLTree<Elem>::RLrotate(BinNode<Elem>* parent) noexcept
{
    BinTree<Elem>& bt = m_bst.get_bt();
    BinNode<Elem>* tmp_root = parent ? parent -> right.release() : bt.get_root_release();
    BinNode<Elem>* tmp_rl = tmp_root -> right -> left.release();
    tmp_root -> right -> left = std::move(tmp_rl -> right);
    BinNode<Elem>* tmp_r = tmp_root -> right.release();
    tmp_root -> right = std::move(tmp_rl -> left);
    tmp_rl -> left.reset(tmp_root);
    tmp_rl -> right.reset(tmp_r);
    parent ? parent -> right.reset(tmp_rl) : bt.root_reset(tmp_rl);
    updateHeight(tmp_r);
    updateHeight(tmp_root);
    updateHeight(tmp_rl);
}

template <typename Elem>
inline void AVLTree<Elem>::updateHeight(BinNode<Elem>* node) noexcept
{
    node -> height = std::max(height(node -> left.get()), height(node -> right.get())) + 1;
}

template <typename Elem>
inline std::optional<std::stack<BinNode<Elem>*>> AVLTree<Elem>::get_findx_parent(const Elem& x) noexcept
{
    BinTree<Elem>& bt = m_bst.get_bt();
    BinNode<Elem>* current = bt.get_root();
    if (current && current -> data == x)
    {
        return std::stack<BinNode<Elem>*>();
    }
    std::stack<BinNode<Elem>*> st;
    BinNode<Elem>* parent = nullptr;
    while (current)
    {
        parent = current;
        st.push(parent);
        if (x > current -> data)
        {
            current = current -> right.get();
        }
        else if (x < current -> data)
        {
            current = current -> left.get();            
        }
        else
        {
            return st;
        }
    }
    return std::nullopt;
}