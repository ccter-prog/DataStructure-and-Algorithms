/*
 * AVL 树测试主函数
 * 测试插入和删除操作，验证自平衡性质
 */

#include "trees/BinTree.h"
#include "trees/BSTree.h"
#include "trees/AVLTree.h"
#include <print>
#include <vector>

int main()
{
    // 创建底层二叉树和 BST
    BinTree<int> bt;
    BSTree<int> bst(bt);
    AVLTree<int> avl(bst);

    // 测试插入操作
    std::vector<int> insert_values = {10, 5, 15, 3, 7, 12, 18, 1, 9};
    std::println("插入值: {}", insert_values);
    for (int val : insert_values)
    {
        auto result = avl.insert(val);
        if (result)
        {
            std::println("插入 {} 成功", val);
        }
        else
        {
            std::println("插入 {} 失败: {}", val, result.error());
        }
    }

    // 打印插入后树结构
    std::println("\n插入后树结构:");
    bt.print();
    std::println("中序遍历:");
    bt.inprint();

    // 测试删除操作，分步调试
    std::vector<int> remove_values = {3, 15, 10};
    std::println("\n开始删除测试:");
    for (int val : remove_values)
    {
        std::println("准备删除 {}", val);
        std::println("删除前树结构:");
        bt.print();
        std::println("删除前中序:");
        bt.inprint();

        bool success = avl.remove(val);
        if (success)
        {
            std::println("删除 {} 成功", val);
        }
        else
        {
            std::println("删除 {} 失败", val);
        }

        std::println("删除后树结构:");
        bt.print();
        std::println("删除后中序:");
        bt.inprint();
        std::println("---");
    }

    return 0;
}