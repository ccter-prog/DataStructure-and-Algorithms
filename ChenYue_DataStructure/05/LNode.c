#include <stdlib.h>
#include "LNode.h"

List MakeEmpty()
{
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    PtrL -> Last = -1;
    return PtrL;
}

int Find(const int X, List PtrL)
{
    int i = 0;
    int ret = 0;
    while (i <= PtrL -> Last && PtrL -> Data[i] != X)
    {
        i++;
    }
    if (i > PtrL -> Last)
    {
        ret = -1;
    }
    else
    {
        ret = i;
    }
    return ret;
}

int insert(List PtrL, int num)
{
    int ret = 0;
    if (PtrL -> Last < 10)
    {
        if (PtrL -> Last == -1)
        {
            PtrL -> Data[0] = num;
            PtrL -> Last = 0;
        }
        else
        {
            PtrL -> Last++;
            PtrL -> Data[PtrL -> Last] = num;
        }
    }
    else
    {
        ret = 1;
    }
    return ret;
}

void del(List PtrL)
{
    if (PtrL)
    {
        free(PtrL);
        PtrL = NULL;
    }
}