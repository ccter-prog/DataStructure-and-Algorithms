#include "CircularQueue.h"
#include <stdio.h>

int main(void)
{
    Queue q;
    init(&q, 6);
    for (int i = 1; i <= 6; i++)
    {
        enQueue(&q, i);
        printf("Front = %d\n", q.m_data[q.m_front]);
        deQueue(&q);
    }
    destroy(&q);
    return 0;
}