#include "BinTree.h"
#include "BSTree.h"
#include <print>

int main()
{
    BinTree<int> bt(10);
    bt.insert(10, 1, 11);
    BSTree<int> br(bt);
    BinNode<int>* p = br.findmax();
    std::println("p = {}", p -> data);
    return 0;
}