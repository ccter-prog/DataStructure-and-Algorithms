#include "LinkedList.h"
#include <iostream>
#include <cassert>

int main()
{
    LinkedList<int> list;
    
    // 测试空链表
    std::cout << "Testing empty list:\n";
    list.print();
    assert(list.search(5) == nullptr);
    
    // 测试添加元素
    std::cout << "\nTesting add:\n";
    for (int i = 1; i <= 10; ++i)
    {
        list.add(i);
    }
    list.print();
    
    // 测试搜索
    std::cout << "\nTesting search:\n";
    assert(list.search(5) != nullptr);
    assert(list.search(15) == nullptr);
    std::cout << "Search test passed\n";
    
    // 测试删除中间节点
    std::cout << "\nTesting delete middle node (5):\n";
    list.del(5);
    list.print();
    assert(list.search(5) == nullptr);
    
    // 测试删除头节点
    std::cout << "\nTesting delete head node (1):\n";
    list.del(1);
    list.print();
    assert(list.search(1) == nullptr);
    
    // 测试删除尾节点
    std::cout << "\nTesting delete tail node (10):\n";
    list.del(10);
    list.print();
    assert(list.search(10) == nullptr);
    
    // 测试删除不存在的节点
    std::cout << "\nTesting delete non-existent node (99):\n";
    list.del(99);
    list.print(); // 应该没有变化
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}