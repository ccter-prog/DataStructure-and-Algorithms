#include "LinkedList.h"
#include <iostream>
#include <string>

void test_sort_basic() {
    std::cout << "=== 基础排序测试 ===" << '\n';
    
    LinkedList<int> list;
    
    // 测试1：乱序
    list.add(3);
    list.add(1);
    list.add(4);
    list.add(2);
    
    std::cout << "排序前: ";
    list.print();
    
    list.sort();
    
    std::cout << "排序后: ";
    list.print();  // 应该输出: 1 2 3 4
}

void test_sort_edge_cases() {
    std::cout << "\n=== 边界情况测试 ===" << '\n';
    
    // 测试2：空链表
    LinkedList<int> empty_list;
    empty_list.sort();
    std::cout << "空链表排序后: ";
    empty_list.print();  // 应该无输出
    
    // 测试3：单元素链表
    LinkedList<int> single_list;
    single_list.add(42);
    single_list.sort();
    std::cout << "单元素排序后: ";
    single_list.print();  // 应该输出: 42
    
    // 测试4：已排序链表
    LinkedList<int> sorted_list;
    sorted_list.add(1);
    sorted_list.add(2);
    sorted_list.add(3);
    sorted_list.sort();
    std::cout << "已排序链表排序后: ";
    sorted_list.print();  // 应该输出: 1 2 3
}

void test_sort_comprehensive() {
    std::cout << "\n=== 综合测试 ===" << '\n';
    
    LinkedList<int> list;
    
    // 测试5：重复元素
    list.add(3);
    list.add(1);
    list.add(3);
    list.add(2);
    list.add(1);
    
    std::cout << "重复元素排序前: ";
    list.print();
    
    list.sort();
    
    std::cout << "重复元素排序后: ";
    list.print();  // 应该输出: 1 1 2 3 3
    
    // 测试6：逆序
    LinkedList<int> reverse_list;
    reverse_list.add(5);
    reverse_list.add(4);
    reverse_list.add(3);
    reverse_list.add(2);
    reverse_list.add(1);
    
    std::cout << "逆序链表排序前: ";
    reverse_list.print();
    
    reverse_list.sort();
    
    std::cout << "逆序链表排序后: ";
    reverse_list.print();  // 应该输出: 1 2 3 4 5
}

void test_sort_string() {
    std::cout << "\n=== 字符串排序测试 ===" << '\n';
    
    LinkedList<std::string> str_list;
    str_list.add("banana");
    str_list.add("apple");
    str_list.add("cherry");
    
    std::cout << "字符串排序前: ";
    str_list.print();
    
    str_list.sort();
    
    std::cout << "字符串排序后: ";
    str_list.print();  // 应该按字典序: apple banana cherry
}

int main() {
    test_sort_basic();
    test_sort_edge_cases(); 
    test_sort_comprehensive();
    test_sort_string();
    
    std::cout << "\n=== 所有测试完成 ===" << '\n';
    return 0;
}