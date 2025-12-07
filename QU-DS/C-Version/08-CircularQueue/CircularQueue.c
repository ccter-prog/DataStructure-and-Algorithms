#include "CircularQueue.h"
#include <stdlib.h>
#include <stddef.h>

int init(Queue *pq, const int capacity)
{
    int ret = 0;
    pq -> m_data = (int *)malloc(sizeof(int) * (size_t)capacity);
    ret = pq -> m_data ? 1 : 0;
    pq -> m_capacity = capacity;
    pq -> m_front = 0;
    pq -> m_rear = 0;
    pq -> m_size = 0;
    return ret;
}

int enQueue(Queue *pq, const int x)
{
    int ret = 0;
    if (pq -> m_data && pq -> m_size < pq -> m_capacity)
    {
        pq -> m_data[pq -> m_rear] = x;
        pq -> m_rear = (pq -> m_rear + 1) % pq -> m_capacity;
        pq -> m_size++;
        ret = 1;
    }
    return ret;
}

int deQueue(Queue *pq)
{
    int ret = 0;
    if (pq -> m_size)
    {
        pq -> m_front = (pq -> m_front + 1) % pq -> m_capacity;
        pq -> m_size--;
        ret = 1;
    }
    return ret;
}

int Front(Queue *pq, int *px)
{
    int ret = 0;
    if (pq -> m_size > 0)
    {
        *px = pq -> m_data[pq -> m_front];
        ret = 1;
    }
    return ret;
}

int isEmpty(Queue *pq)
{
    return pq -> m_size == 0;
}

int isFull(Queue *pq)
{
    return pq -> m_size == pq -> m_capacity;
}

void destroy(Queue *pq)
{
    free(pq -> m_data);
    pq -> m_data = NULL;
    pq -> m_capacity = 0;
    pq -> m_front = -1;
    pq -> m_rear = -1;
    pq -> m_size = 0;
}