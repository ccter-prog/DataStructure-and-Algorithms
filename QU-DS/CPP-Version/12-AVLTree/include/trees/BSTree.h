/*
 * 二分搜索树实现，基于组合的 BinTree 提供 BST 操作
 * 使用组合而不是继承以保持接口清晰，避免多重继承复杂性
 */

#pragma once

#include "BinTree.h"
#include "core/BinNode.h"
#include <expected>
#include <utility>
#include <memory>

template <typename Elem>
class BSTree
{
    public:
        // 显式构造函数避免隐式转换，确保用户明确传递 BinTree 引用
        explicit BSTree(BinTree<Elem>& bt);
    public:
        // 普通成员函数
        // findmax/findmin 使用循环而非递归，避免栈溢出且更高效
        BinNode<Elem>* findmax();
        BinNode<Elem>* findmin();
        BinNode<Elem>* findx(const Elem& x);
        // insert 返回 expected 以优雅处理插入失败（如重复元素或内存不足）
        std::expected<BinNode<Elem>*, const char*> insert(const Elem& value);
        // remove 使用 noexcept 保证不抛异常，适合关键路径
        bool remove(const Elem& x) noexcept;
        // 返回引用便于外部访问底层 BinTree，但保持 const 安全
        BinTree<Elem>& get_bt() const noexcept;
    private:
        // 私有成员函数
        // 辅助函数获取父节点，便于删除操作
        BinNode<Elem>* get_findx_parent(const Elem& x);
    private:
        // 使用引用组合 BinTree，避免拷贝开销和所有权问题
        BinTree<Elem>& m_bt;
};

template <typename Elem>
inline BSTree<Elem>::BSTree(BinTree<Elem>& bt) : m_bt(bt)
{
    // 构造函数仅初始化引用，不进行额外操作保持轻量
}

template <typename Elem>
inline BinNode<Elem>* BSTree<Elem>::findmax()
{
    // 从根开始向右遍历找到最大值，BST 性质保证最右为最大
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
    // 从根开始向左遍历找到最小值，BST 性质保证最左为最小
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
    // 迭代查找避免递归栈开销，适合查找操作频繁的场景
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
    // 先创建节点再查找位置，避免在查找过程中分配内存失败
    std::unique_ptr<BinNode<Elem>> temp(m_bt.make_node());
    if (!temp)
    {
        return std::unexpected("内存分配失败");
    }
    temp -> data = value;
    BinNode<Elem>* p = m_bt.get_root();
    if (!p)
    {
        // 空树直接设为根
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
    // 根据比较结果插入到父节点的左或右
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
inline bool BSTree<Elem>::remove(const Elem& x) noexcept
{
    // 先查找节点是否存在
    BinNode<Elem>* p = findx(x);
    if (!p)
    {
        return false;
    }
    // 处理有两子的节点，用左子树最大值替换
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
        // 删除左子树的最大节点（叶子或只有左子）
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
    // 处理根节点删除
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
    // 处理非根节点，找到父节点后调整指针
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
        // 叶子节点直接置空
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
inline BinTree<Elem>& BSTree<Elem>::get_bt() const noexcept
{
    // 返回底层 BinTree 引用，便于访问基础树操作
    return m_bt;
}

template <typename Elem>
inline BinNode<Elem>* BSTree<Elem>::get_findx_parent(const Elem& x)
{
    // 辅助函数查找父节点，用于删除操作时调整指针
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