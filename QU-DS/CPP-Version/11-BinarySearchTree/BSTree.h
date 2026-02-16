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
        BinNode<Elem>* current = p -> left.get();
        BinNode<Elem>* q = nullptr;
        while (current -> right)
        {
            q = current;
            current = current -> right.get();
        }
        p -> data = current -> data;
        if (q && current -> left)
        {
            q -> left = std::move(current -> left);
        }
        if (q)
        {
            q -> right.reset();
        }
        else if (!q)
        {
            p -> left = std::move(current -> left);
        }
        return true;
    }
    BinNode<Elem>* current = m_bt.get_root();
    if (current -> data == x)
    {
        if (current -> left)
        {
            m_bt.root_reset(current -> left.release());
        }
        else if (current -> right)
        {
            m_bt.root_reset(current -> right.release());
        }
        return true;
    }
    BinNode<Elem>* q = get_findx_parent(x);  // 由于get_findx_parent的两个返回空指针的情况已被上下文检查完，所以不做检查
    if (!current -> left && !current -> right)
    {
        if (current -> data > q -> data)
        {
            q -> right.reset();
        }
        else
        {
            q -> left.reset();
        }
    }
    else if (current -> left)
    {
        q -> left = std::move(current -> left);
    }
    else
    {
        q -> right = std::move(current -> right);
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