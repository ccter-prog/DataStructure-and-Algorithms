#include "BinTree.h"

int main()
{
    BinTree<int> bt(11);
    bt.insert(11, 0, 22);
    bt.insert(11, 1, 33);
    bt.insert(22, 0, 44);
    bt.insert(33, 0, 55);
    bt.print();
    return 0;
}