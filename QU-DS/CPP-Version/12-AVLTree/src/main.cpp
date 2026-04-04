#include "trees/BinTree.h"
#include "trees/BSTree.h"
#include "trees/AVLTree.h"

int main()
{
    BinTree<int> bt;
    BSTree<int> bst(bt);
    AVLTree<int> avl(bst);
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    bt.print();
    return 0;
}