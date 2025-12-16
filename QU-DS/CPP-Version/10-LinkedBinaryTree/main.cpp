#include "BinTree.h"

int main()
{
    BinTree<int> bt(11);
    bt.insert(11, 0, 22);
    bt.insert(11, 1, 33);
    bt.insert(33, 0, 44);
    bt.prePrint();
    // bt.inprint();
    return 0;
}