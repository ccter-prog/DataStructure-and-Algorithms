#pragma once

#include "BinNode.h"
#include <memory>
#include <new>
#include <print>
#include <stack>
#include <queue>

template <typename Elem>
class BinTree
{
    public:
        // 特殊成员函数
        BinTree();
        BinTree(const Elem& rx);
    public:
        // 普通成员函数
        void prePrint() const;
        bool isEmpty() const;
        // bool insert(const Elem& rx);
        BinNode<Elem>* find(const Elem& x) const;
        bool insert(const Elem& x, const int lorr, const Elem& value);
        void print() const;
        void inprint() const;
        void levelOrderTraversal() const;
        int count() const;
        BinNode<Elem>* get_root() const;
        BinNode<Elem>* make_node() noexcept;
        void root_reset(BinNode<Elem>* p) noexcept;
    private:
        // 私有成员函数
        void rprePrint(BinNode<Elem>* pr) const;
        BinNode<Elem>* rfind(const Elem& x, BinNode<Elem>* pr) const;
        void rprint(BinNode<Elem>* pr, const int depth) const;
        void rinprint(BinNode<Elem>* pr) const;
        void ipreprint(BinNode<Elem>* pr) const;
        void ipostPrint(BinNode<Elem>* pr) const;
        int countLeaves(BinNode<Elem>* pr) const;
    private:
        std::unique_ptr<BinNode<Elem>> m_root;
        // int m_count;
};

template <typename Elem>
inline BinTree<Elem>::BinTree()  //  : m_count(1)
{}

template <typename Elem>
inline BinTree<Elem>::BinTree(const Elem& rx)  //  : m_count(1)
{
    m_root.reset(new(std::nothrow) BinNode<Elem>);
    if (m_root)
    {
        m_root -> data = rx;
        // m_count++;
    }
}

template <typename Elem>
inline void BinTree<Elem>::prePrint() const
{
    // rprePrint(m_root.get());
    // ipreprint(m_root.get());
    ipostPrint(m_root.get());
    std::println();
}

template <typename Elem>
inline bool BinTree<Elem>::isEmpty() const
{
    return m_root == nullptr;
}

template <typename Elem>
inline BinNode<Elem>* BinTree<Elem>::find(const Elem& x) const
{
    return rfind(x, m_root.get());
}

template <typename Elem>
inline bool BinTree<Elem>::insert(const Elem& x, const int lorr, const Elem& value)
{
    bool ret = false;
    BinNode<Elem>* found = rfind(x, m_root.get());
    if (found)
    {
        switch (lorr)
        {
            case 0:
            {
                if (!found -> left)
                {
                    found -> left.reset(make_node());
                    if (found -> left)
                    {
                        found -> left -> data = value;
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
            case 1:
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
    rprint(m_root.get(), 0);
}

template <typename Elem>
inline void BinTree<Elem>::inprint() const
{
    rinprint(m_root.get());
    std::println();
}

template <typename Elem>
inline void BinTree<Elem>::levelOrderTraversal() const
{
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
    return countLeaves(m_root.get());
}

template <typename Elem>
inline BinNode<Elem>* BinTree<Elem>::get_root() const
{
    return m_root.get();
}

template <typename Elem>
inline void BinTree<Elem>::root_reset(BinNode<Elem>* p) noexcept
{
    m_root.reset(p);
}

template <typename Elem>
inline void BinTree<Elem>::rprePrint(BinNode<Elem>* pr) const
{
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
    if (!pr)
    {
        return 0;
    }
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