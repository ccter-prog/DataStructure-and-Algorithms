#ifndef BANK_QUEUE_H
#define BANK_QUEUE_H

typedef struct BankQueue
{
    int *m_data;
    int m_capacity;
    int m_front;
    int m_rear;
    int m_size;
} BankQueue;

int init(BankQueue *pq, const int N);
int enQueue(BankQueue *pq, const int ID);
int deQueue(BankQueue *pq);
void destroy(BankQueue *pq);

#endif