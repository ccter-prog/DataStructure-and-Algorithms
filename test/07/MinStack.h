#pragma once

typedef struct MinStack
{
    int *m_data;
    int m_top;
    int m_capacity;
    int m_min;
} Stack;

int init(Stack *ps, const int capacity);
int push(Stack *ps, const int x);
void pop(Stack *ps);
int top(Stack *ps);
int getMin(Stack *ps);
void destroy(Stack *ps);