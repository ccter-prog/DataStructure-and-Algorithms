#include "BinTree.h"
#include "BSTree.h"
#include <print>

int main()
{
    BinTree<int> bstContainer;
    BSTree<int> bst(bstContainer);
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.remove(50);
    bstContainer.print();
    return 0;
}