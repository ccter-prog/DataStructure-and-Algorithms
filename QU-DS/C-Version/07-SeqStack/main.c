#include "SeqStack.h"
#include <stdio.h>

int main(void)
{
    Stack st;
    init(&st, 5);
    push(&st, 5);
    push(&st, 11);
    push(&st, 22);
    push(&st, 33);
    push(&st, 44);
    push(&st, 55);
    push(&st, 66);
    int x;
    pop(&st, &x);
    printf("x = %d\n", x);
    top(&st, &x);
    printf("x = %d\n", x);
    destroy(&st);
    return 0;
}