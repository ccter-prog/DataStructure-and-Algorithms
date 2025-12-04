#include "MinStack.h"
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

// 单栈版本
int init(Stack *ps, const int capacity)
{
    ps -> m_data = (int *)malloc(sizeof(int) * (size_t)capacity);
    ps -> m_top = -1;
    ps -> m_capacity = capacity;
    ps -> m_min = INT_MAX;
    return ps -> m_data ? 1 : 0;
}

// 双栈版本
// int init(Stack *ps, const int capacity)
// {
//     ps -> m_data = (int *)malloc(sizeof(int) * (size_t)capacity);
//     ps -> m_top = -1;
//     ps -> m_capacity = capacity;
//     return ps -> m_data ? 1 : 0;
// }

// 单栈版本
int push(Stack *ps, const int x)
{
    int ret = 0;
    if (ps -> m_data && ps -> m_top == -1)
    {
        ps -> m_top++;
        ps -> m_data[ps -> m_top] = 0;
        ps -> m_min = x;
        ret = 1;
    }
    else if (ps -> m_data && ps -> m_top < ps -> m_capacity)
    {
        ps -> m_top++;
        ps -> m_data[ps -> m_top] = x - ps -> m_min;
        if (x < ps -> m_min)
        {
            ps -> m_min = x;
        }
        ret = 1;
    }
    return ret;
}

// 双栈版本
// int push(Stack *ps, const int x)
// {
//     int ret = 0;
//     if (ps -> m_data && ps -> m_top < ps -> m_capacity)
//     {
//         ps -> m_top++;
//         ps -> m_data[ps -> m_top] = x;
//         ret = 1;
//     }
//     return ret;
// }

// 单栈版本
void pop(Stack *ps)
{
    if (ps -> m_top >= 0 && ps -> m_data[ps -> m_top] < 0)
    {
        ps -> m_min -= ps -> m_data[ps -> m_top];
        ps -> m_top--;
    }
    else if (ps -> m_top >= 0)
    {
        ps -> m_top--;
    }
    else
    {
        ps -> m_min = INT_MAX;
    }
}

// 双栈版本
// void pop(Stack *ps)
// {
//     if (ps -> m_top >= 0)
//     {
//         ps -> m_top--;
//     }
// }

// 单栈版本
int top(Stack *ps)
{
    int ret = -1;
    if (ps -> m_top >= 0)
    {
        int diff = ps -> m_data[ps -> m_top];
        if (diff < 0)
        {
            ret = ps -> m_min;
        }
        else
        {
            ret = ps -> m_min + diff;
        }
    }
    return ret;
}

// 双栈版本
// int top(Stack *ps)
// {
//     return ps -> m_top >= 0 ? ps -> m_data[ps -> m_top] : -1;
// }

// 单栈版本
int getMin(Stack *ps)
{
    return ps -> m_top < 0 ? -1 : ps -> m_min;
}

// 双栈版本
// int getMin(Stack *ps)
// {
//     int min = INT_MAX;
//     if (ps -> m_top >= 0)
//     {
//         Stack temp;
//         if (init(&temp, ps -> m_capacity))
//         {
//             while (ps -> m_top != -1)
//             {
//                 int x = top(ps);
//                 pop(ps);
//                 push(&temp, x);
//                 if (x < min)
//                 {
//                     min = x;
//                 }
//             }
//             while (temp.m_top != -1)
//             {
//                 int x = top(&temp);
//                 pop(&temp);
//                 push(ps, x);
//             }
//         }
//     }
//     return min;
// }

void destroy(Stack *ps)
{
    free(ps -> m_data);
    ps -> m_data = NULL;
    ps -> m_capacity = 0;
    ps -> m_top = -1;
}