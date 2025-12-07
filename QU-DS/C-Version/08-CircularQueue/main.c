#include "CircularQueue.h"
#include <stdio.h>

int main(void)
{
    Queue q;
    
    // 1. 测试初始化
    if (!init(&q, 6))
    {
        printf("初始化失败！\n");
        return -1;
    }
    printf("队列初始化成功，容量：%d\n\n", q.m_capacity);
    
    // 2. 测试入队6个元素（应该成功，因为容量=6）
    printf("入队1-6：\n");
    for (int i = 1; i <= 6; i++)
    {
        if (enQueue(&q, i))
        {
            printf("  入队 %d 成功，当前大小：%d\n", i, q.m_size);
        }
        else
        {
            printf("  入队 %d 失败（队列已满）\n", i);
        }
    }
    
    // 3. 测试队列已满时再入队
    printf("\n尝试入队 7（应该失败）：\n");
    if (!enQueue(&q, 7))
    {
        printf("  正确：队列已满，无法入队7\n");
    }
    
    // 4. 测试出队
    printf("\n出队3个元素：\n");
    for (int i = 0; i < 3; i++)
    {
        if (deQueue(&q))
        {
            printf("  出队成功，当前大小：%d\n", q.m_size);
        }
    }
    
    // 5. 测试循环特性
    printf("\n再入队3个元素（测试循环）：\n");
    for (int i = 7; i <= 9; i++)
    {
        if (enQueue(&q, i))
        {
            printf("  入队 %d 成功，当前大小：%d\n", i, q.m_size);
        }
    }
    
    // 6. 查看队列状态
    printf("\n最终队列状态：\n");
    printf("  容量：%d\n", q.m_capacity);
    printf("  大小：%d\n", q.m_size);
    printf("  front索引：%d\n", q.m_front);
    printf("  rear索引：%d\n", q.m_rear);
    
    // 7. 清空队列
    printf("\n清空队列：\n");
    while (q.m_size > 0)
    {
        deQueue(&q);
    }
    printf("  队列已清空，大小：%d\n", q.m_size);
    
    // 8. 测试空队列出队
    printf("\n尝试从空队列出队（应该失败）：\n");
    if (!deQueue(&q))
    {
        printf("  正确：队列为空，无法出队\n");
    }
    
    destroy(&q);
    printf("\n队列已销毁\n");
    return 0;
}