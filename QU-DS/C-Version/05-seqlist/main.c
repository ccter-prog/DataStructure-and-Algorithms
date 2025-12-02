#include "seqlist.h"

int main(void)
{
    SList a;
    init(&a);
    insert(&a, 0, 11);
    insert(&a, 0, 22);
    insert(&a, 1, 33);
    printList(&a);
    int x;
    erase(&a, 1, &x);
    printList(&a);
    return 0;
}