#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

typedef struct CircularQueue
{
    int *m_data;
    int m_capacity;
    int m_front;
    int m_rear;
    int m_size;
} Queue;

int init(Queue *pq, const int capacity);
int enQueue(Queue *pq, const int x);
int deQueue(Queue *pq);
int Front(Queue *pq, int *px);
int isEmpty(Queue *pq);
int isFull(Queue *pq);
void destroy(Queue *pq);

#endif