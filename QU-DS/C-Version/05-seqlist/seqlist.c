#include "seqlist.h"
#include <stdio.h>

void init(SList *p)
{
    p -> length = 0;
}

void printList(const SList *p)
{
    for (int i = 0; i < p -> length; i++)
    {
        printf("%d ", p -> data[i]);
    }
    putchar('\n');
}

int insert(SList *p, const int k, const int x)
{
    int ret = 0;
    if (k >= 0 && k <= p -> length && p -> length != MAX)
    {
        for (int i = p -> length - 1; i >= k; i--)
        {
            p -> data[i + 1] = p -> data[i];
        }
        p -> data[k] = x;
        p -> length++;
        ret = 1;
    }
    return ret;
}

int erase(SList *p, const int k, int *px)
{
    int ret = 0;
    if (k >= 0 && k < p -> length)
    {
        *px = p -> data[k];
        for (int i = k; i < p -> length - 1; i++)
        {
            p -> data[i] = p -> data[i + 1];
        }
        p -> length--;
        ret = 1;
    }
    return ret;
}