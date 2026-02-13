#pragma once

#include "BinTree.h"
#include "BinNode.h"
#include <expected>
#include <utility>

template <typename Elem>
class BSTree
{
    public:
        BSTree(BinTree<Elem>& bt);
    public:
        // 普通函数
        BinNode<Elem>* findmax();
        BinNode<Elem>* findmin();
        BinNode<Elem>* findx(const Elem& x);
        std::expected<BinNode<Elem>*, const char*> insert(const Elem& value);
        
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