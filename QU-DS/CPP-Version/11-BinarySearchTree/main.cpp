#include "BinTree.h"
#include "BSTree.h"
#include <print>

int main()
{
    BinTree<int> bstContainer;
    BSTree<int> bst(bstContainer);
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(8);
    bst.insert(15);
    bst.insert(15);
    bst.insert(2);
    bst.insert(6);
    bstContainer.print();
    std::println("-------------------------");
    bst.remove(10);
    bstContainer.print();
    return 0;
}