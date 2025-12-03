#pragma once

typedef struct SeqStack
{
    int *m_data;
    int m_capacity;
    int m_top;
} Stack;

void init(Stack *ps, const int capacity);
int push(Stack *ps, const int x);
int isFull(const Stack *ps);
int isEmpty(const Stack *ps);
int pop(Stack *ps, int *px);
int top(const Stack *ps, int *px);
void destroy(Stack *ps);