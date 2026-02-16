#pragma once

#include "BinTree.h"
#include "BinNode.h"
#include <expected>
#include <utility>
#include <memory>

template <typename Elem>
class BSTree
{
    public:
        BSTree(BinTree<Elem>& bt);
    public:
        // 普通成员函数
        BinNode<Elem>* findmax();
        BinNode<Elem>* findmin();
        BinNode<Elem>* findx(const Elem& x);
        std::expected<BinNode<Elem>*, const char*> insert(const Elem& value);
        bool remove(const Elem& x);
    private:
        // 私有成员函数
        BinNode<Elem>* get_findx_parent(const Elem& x);
    private:
        // 组合
        BinTree<Elem>& m_bt;
};

template <typename Elem>
inline BSTree<Elem>::BSTree(BinTree<Elem>& bt) : m_bt(bt)
{

}

template <typename Elem>
inline BinNode<Elem>* BSTree<Elem>::findmax()
{
    BinNode<Elem>* p = m_bt.get_root();
    if (!p)
    {
        return nullptr;
    }
    while (p -> right)
    {
        p = p -> right.get();
    }
    return p;
}

template <typename Elem>
inline BinNode<Elem>* BSTree<Elem>::findmin()
{
    BinNode<Elem>* p = m_bt.get_root();
    if (!p)
    {
        return nullptr;
    }
    while (p -> left)
    {
        p = p -> left.get();
    }
    return p;
}

template <typename Elem>
inline BinNode<Elem>* BSTree<Elem>::findx(const Elem& x)
{
    if (!m_bt.get_root())
    {
        return nullptr;
    }
    BinNode<Elem>* p = m_bt.get_root();
    while (p)
    {
        if (x > p -> data)
        {
            p = p -> right.get();
        }
        else if (x < p -> data)
        {
            p = p -> left.get();
        }
        else
        {
            return p;
        }
    }
    return nullptr;
}

template <typename Elem>
inline std::expected<BinNode<Elem>*, const char*> BSTree<Elem>::insert(const Elem& value)
{
    std::unique_ptr<BinNode<Elem>> temp(m_bt.make_node());
    if (!temp)
    {
        return std::unexpected("内存分配失败");
    }
    temp -> data = value;
    BinNode<Elem>* p = m_bt.get_root();
    if (!p)
    {
        m_bt.root_reset(temp.release());
        return m_bt.get_root();
    }
    BinNode<Elem>* parent = nullptr;
    while (p)
    {
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
    if (value > parent -> data)
    {
        parent -> right = std::move(temp);
        return parent -> right.get();
    }
    else
    {
        parent -> left = std::move(temp);
        return parent -> left.get();
    }
}

template <typename Elem>
inline bool BSTree<Elem>::remove(const Elem& x)
{
    BinNode<Elem>* p = findx(x);
    if (!p)
    {
        return false;
    }
    if (p -> left && p -> right)
    {
        BinNode<Elem>* maxLeftParent = p;
        BinNode<Elem>* maxLeft = p -> left.get();
        while (maxLeft -> right)
        {
            maxLeftParent = maxLeft;
            maxLeft = maxLeft -> right.get();
        }
        p -> data = maxLeft -> data;
        if (maxLeftParent == p)
        {
            p -> left = std::move(maxLeft -> left);
        }
        else
        {
            maxLeftParent -> right = std::move(maxLeft -> left);
        }
        return true;
    }
    if (p == m_bt.get_root())
    {
        if (p -> left)
        {
            m_bt.root_reset(p -> left.release());
        }
        else if (p -> right)
        {
            m_bt.root_reset(p -> right.release());
        }
        else
        {
            m_bt.root_reset(nullptr);
        }
    }
    BinNode<Elem>* parent = get_findx_parent(x);
    if (p -> left)
    {
        if (parent -> left.get() == p)
        {
            parent -> left = std::move(p -> left);
        }
        else
        {
            parent -> right = std::move(p -> left);
        }
    }
    else if (p -> right)
    {
        if (parent -> left.get() == p)
        {
            parent -> left = std::move(p -> right);
        }
        else
        {
            parent -> right = std::move(p -> right);
        }
    }
    else
    {
        if (parent -> left.get() == p)
        {
            parent -> left.reset();
        }
        else
        {
            parent -> right.reset();
        }
    }
    return true;
}

template <typename Elem>
inline BinNode<Elem>* BSTree<Elem>::get_findx_parent(const Elem& x)
{
    BinNode<Elem>* current = m_bt.get_root();
    BinNode<Elem>* parent = nullptr;
    while (current)
    {
        if (x == current -> data)
        {
            return parent;
        }
        parent = current;
        if (x < current -> data)
        {
            current = current -> left.get();
        }
        else
        {
            current = current -> right.get();
        }
    }
    return nullptr;
}