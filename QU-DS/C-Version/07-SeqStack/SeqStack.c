#include "SeqStack.h"
#include <stdlib.h>
#include <stddef.h>

void init(Stack *ps, const int capacity)
{
    ps -> m_capacity = capacity;
    ps -> m_data = (int *)malloc(sizeof(int) * (size_t)capacity);
    ps -> m_top = -1;
}

int push(Stack *ps, const int x)
{
    int ret = 0;
    if (!isFull(ps))
    {
        ps -> m_top++;
        ps -> m_data[ps -> m_top] = x;
        ret = 1;
    }
    return ret;
}

int isFull(const Stack *ps)
{
    return ps -> m_top < ps -> m_capacity ? 0 : 1;
}

int isEmpty(const Stack *ps)
{
    return ps -> m_top == -1;
}

int pop(Stack *ps, int *px)
{
    int ret = 0;
    if (!isEmpty(ps))
    {
        *px = ps -> m_data[ps -> m_top];
        ps -> m_top--;
        ret = 1;
    }
    return ret;
}

int top(const Stack *ps, int *px)
{
    int ret = 0;
    if (!isEmpty(ps))
    {
        *px = ps -> m_data[ps -> m_top];
        ret = 1;
    }
    return ret;
}

void destroy(Stack *ps)
{
    free(ps -> m_data);
    ps -> m_data = NULL;
    ps -> m_capacity = 0;
    ps -> m_top = -1;
}