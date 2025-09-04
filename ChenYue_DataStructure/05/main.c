#include <stdio.h>
#include "LNode.h"

int main()
{
    struct LNode L;
    List PtrL = NULL;
    PtrL = MakeEmpty();
    for (int i = 1; i <= 10; i++)
    {
        insert(PtrL, i);
    }
    int num = Find(10, PtrL);
    printf("num=%d\n", num);
    del(PtrL);
    return 0;
}