#include "trees/BinTree.h"
#include "trees/BSTree.h"
#include "trees/AVLTree.h"

int main()
{
    BinTree<int> bt;
    BSTree<int> bst(bt);
    bst.insert(10);
    bst.insert(20);
    bst.insert(5);
    bst.remove(10);
    bt.print();
    return 0;
}