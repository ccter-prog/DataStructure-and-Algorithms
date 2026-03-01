#include "trees/BinTree.h"
#include "trees/BSTree.h"

int main()
{
    BinTree<int> bt;
    BSTree<int> bst(bt);
    bst.insert(1);
    bst.insert(2);
    bst.insert(0);
    bt.print();
    return 0;
}