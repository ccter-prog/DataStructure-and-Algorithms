#include <stdio.h>
#include "printN.h"

void printN(int num)
{
    for (int i = 1; i <= num; i++)
    {
        printf("%d\n", i);
    }
    printf("==========循环实现==========\n");
}

void printN2(int num)
{
    if (num > 1)
    {
        printN2(num - 1);
    }
    printf("%d\n", num);
}