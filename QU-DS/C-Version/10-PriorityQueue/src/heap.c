#include "../include/heap.h"
#include "../include/expected.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static bool heap_grow(struct heap *obj);
static void heap_percolate_up(struct heap *obj, size_t index);
static void heap_percolate_down(struct heap *obj, size_t index);

struct heap heap_init(const size_t capacity)
{
    struct heap obj;
    // 分配 capacity+1 个空间：多出的一个位置(data[0])用于存放哨兵
    obj.data = (Elem *)malloc(sizeof(Elem) * (capacity + 1));  // 内存分配成功则data为堆内存开始，否则data被malloc返回的空指针赋值为空指针
    obj.capacity = obj.data ? capacity : 0;  // 如果data不为NULL，设置capacity为传入值，否则为0
    obj.size = 0;  // 初始化size为0，表示数组元素为空  
    // 初始化哨兵为最小值，确保上浮操作在到达根节点时能自然终止，无需额外边界检查
    obj.data[0] = INT_MIN;
    return obj;
}

void heap_destroy(struct heap *obj)
{
    free(obj->data);
    // 释放后置空，防止悬空指针
    obj->data = NULL;
    obj->capacity = 0;
    obj->size = 0;
}

void heap_print(const struct heap *obj)
{
    // 从索引1开始打印，跳过索引0的哨兵
    for (size_t i = 1; i <= obj->size; ++i)
    {
        printf("%d ", obj->data[i]);
    }
    
    putchar('\n');
}

bool heap_insert(struct heap *obj, const Elem value)
{
    if (!obj->data)
    {
        return false;
    }
    // 检查是否需要扩容
    if (obj->size == obj->capacity)
    {
        if (!heap_grow(obj))
        {
            return false;
        }
    }
    // 将新元素放入末尾，并执行上浮操作以维护最小堆性质
    obj->data[++obj->size] = value;
    heap_percolate_up(obj, obj->size);
    return true;
}

struct expected heap_remove(struct heap *obj)
{
    struct expected result;
    if (!obj->size)
    {
        result.error = "堆为空, remove失败";
        result.has_value = EXPECTED_ERROR;
        return result;
    }
    result.value = obj->data[1];
    result.has_value = EXPECTED_OK;
    obj->data[1] = obj->data[obj->size--];
    heap_percolate_down(obj, 1);
    return result;
}

static bool heap_grow(struct heap *obj)
{
    // 计算新的分配大小：容量翻倍 + 1个哨兵位
    size_t new_alloc_size = obj->capacity * 2 + 1;
    Elem *temp;
    // 处理初始容量为0或data为空的特殊情况，需额外多分配一个位置以存储第一个有效元素
    if ((obj->data && obj->capacity == 0) || !obj->data)
    {
        new_alloc_size += 1;
        temp = (Elem *)realloc(obj->data, sizeof(Elem) * (new_alloc_size));
        // 如果是首次分配内存，手动初始化哨兵
        if (!obj->data)
        {
            temp[0] = INT_MIN;
        }
    }
    else
    {
        temp = (Elem *)realloc(obj->data, sizeof(Elem) * new_alloc_size);
    }
    if (!temp)
    {
        return false;
    }
    obj->data = temp;
    // 更新逻辑容量（总分配数减去1个哨兵位）
    obj->capacity = new_alloc_size - 1;
    return true;
}

static void heap_percolate_up(struct heap *obj, size_t index)
{
    Elem temp = obj->data[index];
    size_t i = index;
    // 利用哨兵机制：当父节点(data[i/2])不大于待插入值(temp)时停止
    // 由于data[0]是INT_MIN，循环会在到达根节点后自动终止，无需额外边界检查
    for (; obj->data[i] < obj->data[i / 2]; i /= 2)
    {
        obj->data[i] = obj->data[i / 2]; // 父节点下移
    }
    obj->data[i] = temp; // 将元素放入最终找到的正确位置
}

static void heap_percolate_down(struct heap *obj, size_t index)
{
    Elem temp = obj->data[index];
    size_t i = index;
    size_t child;
    for (; i * 2 <= obj->size; i = child)
    {
        child = i * 2;
        if (child != obj->size && obj->data[child] > obj->data[child + 1])
        {
            ++child;
        }
        if (obj->data[i] > obj->data[child])
        {
            obj->data[i] = obj->data[child];
        }
        else
        {
            break;
        }
    }
    obj->data[i] = temp;
}