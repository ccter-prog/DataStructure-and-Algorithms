/*
 * 二叉树实现，使用 unique_ptr 管理内存以避免手动释放导致的泄漏
 * 提供递归和迭代遍历方式，方便学习和比较不同实现
 */

#pragma once

#include "core/BinNode.h"
#include <memory>
#include <new>
#include <print>
#include <stack>
#include <queue>
#include <utility>

template <typename Elem>
class BinTree
{
    public:
        // 构造函数设计为内联以提高性能，避免函数调用开销
        BinTree();
        BinTree(const Elem& rx);
    public:
        // 遍历方法提供多种实现，递归版本简单但有栈深度限制，迭代版本更安全
        void prePrint() const;
        bool isEmpty() const;
        BinNode<Elem>* find(const Elem& x) const;
        // 插入方法指定父节点和左右位置，便于精确控制树结构
        bool insert(const Elem& x, const int lorr, const Elem& value);
        void print() const;
        void inprint() const;
        // 层序遍历使用队列，符合 BFS 思想
        void levelOrderTraversal() const;
        int count() const;
        BinNode<Elem>* get_root() const;
        // make_node 使用 nothrow 以防内存分配失败时抛异常
        BinNode<Elem>* make_node() noexcept;
        void root_reset(BinNode<Elem>* p) noexcept;
        BinNode<Elem>* get_root_release() noexcept;
        void root_move(std::unique_ptr<BinNode<Elem>>& ptr) noexcept;

    private:
        // 私有方法封装递归逻辑，隐藏实现细节
        void rprePrint(BinNode<Elem>* pr) const;
        BinNode<Elem>* rfind(const Elem& x, BinNode<Elem>* pr) const;
        void rprint(BinNode<Elem>* pr, const int depth) const;
        void rinprint(BinNode<Elem>* pr) const;
        void ipreprint(BinNode<Elem>* pr) const;
        void ipostPrint(BinNode<Elem>* pr) const;
        // 叶子计数使用迭代栈实现，避免递归深度问题
        int countLeaves(BinNode<Elem>* pr) const;

    private:
        // 使用 unique_ptr 自动管理根节点内存，无需手动 delete
        std::unique_ptr<BinNode<Elem>> m_root;
};

template <typename Elem>
inline BinTree<Elem>::BinTree()  //  : m_count(1)
{
    // 默认构造创建空树，延迟初始化以节省资源
}

template <typename Elem>
inline BinTree<Elem>::BinTree(const Elem& rx)  //  : m_count(1)
{
    // 使用 nothrow new 避免构造失败时抛异常，适合学习和测试环境
    m_root.reset(new(std::nothrow) BinNode<Elem>);
    if (m_root)
    {
        m_root -> data = rx;
        // 注释掉计数器，因为当前实现不维护节点数量
    }
}

template <typename Elem>
inline void BinTree<Elem>::prePrint() const
{
    // 当前使用后序遍历演示不同遍历方式，可切换到前序或迭代版本
    // rprePrint(m_root.get());
    // ipreprint(m_root.get());
    ipostPrint(m_root.get());
    std::println();
}

template <typename Elem>
inline bool BinTree<Elem>::isEmpty() const
{
    // 简单检查根指针是否为空，unique_ptr 保证了空安全
    return m_root == nullptr;
}

template <typename Elem>
inline BinNode<Elem>* BinTree<Elem>::find(const Elem& x) const
{
    // 委托给递归查找，保持接口简洁
    return rfind(x, m_root.get());
}

template <typename Elem>
inline bool BinTree<Elem>::insert(const Elem& x, const int lorr, const Elem& value)
{
    // 先查找父节点，避免直接操作指针导致的错误
    bool ret = false;
    BinNode<Elem>* found = rfind(x, m_root.get());
    if (found)
    {
        // 使用 switch 明确左右插入逻辑，提高代码可读性
        switch (lorr)
        {
            case 0:  // 左插入
            {
                if (!found -> left)
                {
                    // 使用 make_node 统一节点创建逻辑
                    found -> left.reset(make_node());
                    if (found -> left)
                    {
                        found -> left -> data = value;
                    }
                    else
                    {
                        // 内存分配失败时跳转到结束，避免复杂错误处理
                        goto end;
                    }
                }
                else
                {
                    goto end;
                }
                break;
            }
            case 1:  // 右插入
            {
                if (!found -> right)
                {
                    found -> right.reset(make_node());
                    if (found -> right)
                    {
                        found -> right -> data = value;
                    }
                    else
                    {
                        goto end;
                    }
                }
                else
                {
                    goto end;
                }
                break;
            }
            default:
            {
                goto end;
            }
        }
        ret = true;
    }
end:
    return ret;
}

// template <typename Elem>
// inline bool BinTree<Elem>::insert(const Elem& rx)
// {
//     bool ret = false;
//     if (isEmpty())
//     {
//         m_root.reset(new(std::nothrow) BinNode<Elem>);
//         if (!isEmpty())
//         {
//             m_root -> data = rx;
//             m_count++;
//             ret = true;
//         }
//     }
//     else
//     {
//         BinNode<Elem>* temp = m_root.get();
//         while (!ret)
//         {
//             if (!temp -> left)
//             {
//                 temp -> left.reset(make_node());
//                 temp -> left -> data = rx;
//                 m_count++;
//                 ret = true;
//             }
//             else if (!temp -> right)
//             {
//                 temp -> right.reset(make_node());
//                 temp -> right -> data = rx;
//                 m_count++;
//                 ret = true;
//             }
//             else
//             {
//                 int control = m_count % 2;
//                 if (control == 0)
//                 {
//                     temp = temp -> right.get();
//                 }
//                 else
//                 {
//                     temp = temp -> left.get();
//                 }
//             }
//         }
//     }
//     return ret;
// }

template <typename Elem>
inline void BinTree<Elem>::print() const
{
    // 递归打印树结构，带深度缩进便于可视化
    rprint(m_root.get(), 0);
}

template <typename Elem>
inline void BinTree<Elem>::inprint() const
{
    // 中序遍历输出，便于验证 BST 性质
    rinprint(m_root.get());
    std::println();
}

template <typename Elem>
inline void BinTree<Elem>::levelOrderTraversal() const
{
    // 使用队列实现 BFS，符合层序遍历的自然顺序
    if (!m_root)
    {
        return;
    }
    std::queue<BinNode<Elem>*> q;
    q.push(m_root.get());
    while (!q.empty())
    {
        BinNode<Elem>* temp = q.front();
        q.pop();
        std::print("{} ", temp -> data);
        if (temp -> left)
        {
            q.push(temp -> left.get());
        }
        if (temp -> right)
        {
            q.push(temp -> right.get());
        }
    }
    std::println();
}

template <typename Elem>
inline int BinTree<Elem>::count() const
{
    // 统计叶子节点数量，反映树的"宽度"
    return countLeaves(m_root.get());
}

template <typename Elem>
inline BinNode<Elem>* BinTree<Elem>::get_root() const
{
    // 提供只读访问根节点，便于外部检查
    return m_root.get();
}

template <typename Elem>
inline void BinTree<Elem>::root_reset(BinNode<Elem>* p) noexcept
{
    // 重置根节点，自动处理旧节点的清理
    m_root.reset(p);
}

template <typename Elem>
inline BinNode<Elem>* BinTree<Elem>::get_root_release() noexcept
{
    // 释放所有权，返回裸指针供外部管理
    return m_root.release();
}

template <typename Elem>
inline void BinTree<Elem>::root_move(std::unique_ptr<BinNode<Elem>>& ptr) noexcept
{
    // 移动语义转移所有权，避免拷贝开销
    m_root = std::move(ptr);
}

template <typename Elem>
inline void BinTree<Elem>::rprePrint(BinNode<Elem>* pr) const
{
    // 递归前序遍历，简单直观但有栈溢出风险
    if (pr)
    {
        std::print("{} ", pr -> data);
        rprePrint(pr -> left.get());
        rprePrint(pr -> right.get());
    }
}

template <typename Elem>
inline BinNode<Elem>* BinTree<Elem>::make_node() noexcept
{
    return new(std::nothrow) BinNode<Elem>;
}

template <typename Elem>
inline BinNode<Elem>* BinTree<Elem>::rfind(const Elem& x, BinNode<Elem>* pr) const
{
    // 递归查找，优先左子树再右子树，符合一般搜索习惯
    if (pr)
    {
        if (pr -> data != x)
        {
            BinNode<Elem>* found = rfind(x, pr -> left.get());
            pr = found ? found : rfind(x, pr -> right.get());
        }
    }
    return pr;
}

template <typename Elem>
inline void BinTree<Elem>::rprint(BinNode<Elem>* pr, const int depth) const
{
    // 递归打印带缩进，便于观察树形结构
    for (int i = 0; i < depth; i++)
    {
        std::print("  ");
    }
    if (pr)
    {
        std::println("{}", pr -> data);
        rprint(pr -> left.get(), depth + 1);
        rprint(pr -> right.get(), depth + 1);
    }
    else
    {
        std::println("[/]");
    }
}

template <typename Elem>
inline void BinTree<Elem>::rinprint(BinNode<Elem>* pr) const
{
    // 递归中序遍历，输出顺序反映节点值排序
    if (!pr)
    {
        return;
    }
    rinprint(pr -> left.get());
    std::print("{} ", pr -> data);
    rinprint(pr -> right.get());
}

template <typename Elem>
inline void BinTree<Elem>::ipreprint(BinNode<Elem>* pr) const
{
    // 迭代前序遍历，使用栈模拟递归避免栈溢出
    if (!pr)
    {
        return;
    }
    std::stack<BinNode<Elem>*> st;
    while (pr)
    {
        st.push(pr);
        pr = pr -> left.get();
        while (!pr && !st.empty())
        {
            pr = st.top();
            st.pop();
            std::print("{} ", pr -> data);
            pr = pr -> right.get();
        }
    }
}

template <typename Elem>
inline void BinTree<Elem>::ipostPrint(BinNode<Elem>* pr) const
{
    // 迭代后序遍历，使用栈和标记避免重复访问
    if (!pr)
    {
        return;
    }
    std::stack<BinNode<Elem>*> st;
    BinNode<Elem>* last_visited = nullptr;
    while (pr || !st.empty())
    {
        if (pr)
        {
            st.push(pr);
            pr = pr -> left.get();
        }
        else
        {
            BinNode<Elem>* temp = st.top();
            if (temp -> right && temp -> right.get() != last_visited)
            {
                pr = temp -> right.get();
            }
            else
            {
                std::print("{} ", temp -> data);
                last_visited = temp;
                st.pop();
                pr = nullptr;
            }
        }
    }
}

template <typename Elem>
inline int BinTree<Elem>::countLeaves(BinNode<Elem>* pr) const
{
    // 迭代统计叶子，使用栈避免递归深度限制
    if (!pr)
    {
        return 0;
    }
    // 注释掉递归版本，因为迭代更安全
    // if (!pr -> left && !pr -> right)
    // {
    //     return 1;
    // }
    // return countLeaves(pr -> left.get()) + countLeaves(pr -> right.get());

    int result = 0;
    std::stack<BinNode<Elem>*> bt;
    bt.push(pr);
    while (!bt.empty())
    {
        BinNode<Elem>* current = bt.top();
        bt.pop();
        if (!current -> left && !current -> right)
        {
            result++;
            continue;
        }
        if (current -> right)
        {
            bt.push(current -> right.get());
        }
        if (current -> left)
        {
            bt.push(current -> left.get());
        }
    }
    return result;
}