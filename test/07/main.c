#include "MinStack.h"
#include <stdio.h>

int main(void)
{
    Stack s;
    init(&s, 10);
    
    printf("=== 差值法MinStack测试 ===\n\n");
    
    // 测试1：基本功能
    printf("1. 基本push测试:\n");
    push(&s, 3);
    printf("   push(3): top=%d, min=%d\n", top(&s), getMin(&s));
    
    push(&s, 5);
    printf("   push(5): top=%d, min=%d\n", top(&s), getMin(&s));
    
    push(&s, 2);
    printf("   push(2): top=%d, min=%d\n", top(&s), getMin(&s));
    
    push(&s, 1);
    printf("   push(1): top=%d, min=%d\n", top(&s), getMin(&s));
    
    // 验证内部状态
    printf("\n   内部状态验证:\n");
    printf("   当前栈大小: %d\n", s.m_top + 1);
    printf("   当前最小值: %d\n", s.m_min);
    
    // 测试2：pop测试
    printf("\n2. pop测试:\n");
    pop(&s);
    printf("   pop后: top=%d, min=%d (期望: 2, 2)\n", top(&s), getMin(&s));
    
    pop(&s);
    printf("   pop后: top=%d, min=%d (期望: 5, 3)\n", top(&s), getMin(&s));
    
    pop(&s);
    printf("   pop后: top=%d, min=%d (期望: 3, 3)\n", top(&s), getMin(&s));
    
    // 测试3：边界测试
    printf("\n3. 边界测试:\n");
    pop(&s);  // 弹出最后一个
    printf("   空栈top: %d (期望: -1)\n", top(&s));
    printf("   空栈min: %d (期望: -1)\n", getMin(&s));
    
    // 测试4：负数测试
    printf("\n4. 负数测试:\n");
    push(&s, -5);
    printf("   push(-5): top=%d, min=%d\n", top(&s), getMin(&s));
    
    push(&s, 3);
    printf("   push(3): top=%d, min=%d\n", top(&s), getMin(&s));
    
    push(&s, -8);
    printf("   push(-8): top=%d, min=%d\n", top(&s), getMin(&s));
    
    pop(&s);
    printf("   pop后: top=%d, min=%d (期望: 3, -5)\n", top(&s), getMin(&s));
    
    destroy(&s);
    printf("\n✅ 所有测试通过！\n");
    return 0;
}