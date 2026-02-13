#include "BinTree.h"
#include "BSTree.h"
#include <print>

int main()
{
    BinTree<int> bstContainer;
    BSTree<int> bst(bstContainer);
    std::println("创建空的二叉搜索树");
    std::println("\n1.插入节点测试:");
    auto result1 = bst.insert(50);
    if (result1)
    {
        std::println("成功插入: 50");
    }
    auto result2 = bst.insert(30);
    if (result2)
    {
        std::println("成功插入: 30");  
    }
    auto result3 = bst.insert(70);
    if (result3)
    {
        std::println("成功插入: 70");
    }
    for (int i = 20; i <= 80; i += 20)
    {
        bst.insert(i);
    }
    bst.insert(35);
    std::println("插入完成: 20, 40, 60, 80, 35");

    std::println("2.BST树形结构:");
    bstContainer.print();
    
    std::println("3.查找功能测试:");
    BinNode<int>* minNode = bst.findmin();
    if (minNode)
    {
        std::println("最小值: {}", minNode -> data);
    }
    BinNode<int>* maxNode = bst.findmax();
    if (maxNode)
    {
        std::println("最大值: {}", maxNode -> data);
    }
    std::println("\n查找特定值:");
    int searchValues[] = {40, 35, 90, 20};
    for (int val : searchValues)
    {
        BinNode<int>* found = bst.findx(val);
        if (found)
        {
            std::println("找到节点 {}", val);
        }
        else
        {
            std::println("未找到节点 {}", val);
        }
    }

    std::println("\n4.遍历测试:");
    std::print("中序遍历(应该是有序的):");
    bstContainer.inprint();
    std::print("前序遍历:");
    bstContainer.prePrint();
    std::print("层序遍历:");
    bstContainer.levelOrderTraversal();

    std::println("\n5.测试插入重复值:");
    auto dupResult = bst.insert(50);
    if (!dupResult)
    {
        std::println("正确拒绝重复值 50: {}", dupResult.error());
    }
    
    std::println("\n6.统计信息:");
    std::println("叶子节点数: {}", bstContainer.count());

    std::println("\n7.测试极端情况:");
    BinTree<int> emptyContainer;
    BSTree<int> emptyBST(emptyContainer);
    std::println("空BST的最小值:");
    BinNode<int>* emptyMin = emptyBST.findmin();
    if (!emptyMin)
    {
        std::println("nullptr(正确)");
    }
    std::println("空BST的最大值:");
    BinNode<int>* emptyMax = emptyBST.findmax();
    if (!emptyMax)
    {
        std::println("nullptr(正确)");
    }
    std::println("在空BST中查找50:");
    BinNode<int>* emptyFind = emptyBST.findx(50);
    if (!emptyFind)
    {
        std::println("未找到(正确)");
    }
    return 0;
}