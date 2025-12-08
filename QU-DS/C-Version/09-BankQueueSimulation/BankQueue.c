#include "BankQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int init(BankQueue *pq, const int N)
{
    pq -> m_data = (int *)malloc(sizeof(int) * (size_t)N);
    if (pq -> m_data)
    {
        pq -> m_capacity = N;
        pq -> m_front = 0;
        pq -> m_rear = 0;
    }
    else
    {
        pq -> m_capacity = 0;
        pq -> m_front = -1;
        pq -> m_rear = -1;
    }
    pq -> m_size = 0;
    return pq -> m_data != NULL;
}

int enQueue(BankQueue *pq, const int ID)
{
    int ret = 0;
    if (pq -> m_data && pq -> m_size < pq -> m_capacity)
    {
        pq -> m_data[pq -> m_rear] = ID;
        pq -> m_rear = (pq -> m_rear + 1) % pq -> m_capacity;
        pq -> m_size++;
        ret = 1;
        printf("<%d> joined. Total:<%d>\n", ID, pq -> m_size);
    }
    else if (pq -> m_size == pq -> m_capacity)
    {
        printf("<%d> rejected.\n", ID);
    }
    return ret;
}

int deQueue(BankQueue *pq)
{
    int ret = 0;
    if (pq -> m_size > 0)
    {
        printf("<%d> called. Total:<%d>\n", pq -> m_data[pq -> m_front], pq -> m_size);
        pq -> m_front = (pq -> m_front + 1) % pq -> m_capacity;
        pq -> m_size--;
        ret = 1;
    }
    else
    {
        printf("No one!\n");
    }
    return ret;
}

void destroy(BankQueue *pq)
{
    free(pq -> m_data);
    pq -> m_data = NULL;
    pq -> m_capacity = 0;
    pq -> m_front = -1;
    pq -> m_rear = -1;
    pq -> m_size = 0;
}