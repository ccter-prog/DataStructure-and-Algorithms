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
    if (obj.data)
    {
        // 如果data不为NULL，设置capacity为传入值，否则为0
        obj.capacity = capacity;
        // 初始化哨兵为最小值，确保上浮操作在到达根节点时能自然终止，无需额外边界检查
        obj.data[0] = INT_MIN;
    }
    else
    {
        obj.capacity = 0;
    }
    obj.size = 0;  // 初始化size为0，表示数组元素为空  
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
    // 保存堆顶元素（最小值）作为返回值
    result.value = obj->data[1];
    result.has_value = EXPECTED_OK;
    // 将最后一个元素移至堆顶以填补空缺，并减少堆大小
    // 随后执行下沉操作，从根节点开始恢复最小堆性质
    obj->data[1] = obj->data[obj->size--];
    heap_percolate_down(obj, 1);
    return result;
}

struct heap heap_build(const Elem *array, const size_t size)
{
    struct heap obj = heap_init(size);
    if (!obj.data)
    {
        return obj;
    }
    // 将输入数组元素复制到堆的数据区（从索引1开始，保留索引0给哨兵）
    for (size_t i = 0; i < size; ++i)
    {
        obj.data[i + 1] = array[i];
    }
    obj.size = size;
    // 使用 Floyd 建堆算法：从最后一个非叶子节点开始，自底向上依次执行下沉操作
    // 这种方法的平均时间复杂度为 O(n)，优于逐个插入的 O(n log n)
    for (size_t i = obj.size / 2; i > 0; --i)
    {
        heap_percolate_down(&obj, i);
    }
    return obj;
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
    // 只要当前节点存在子节点，就继续下沉调整
    for (; i * 2 <= obj->size; i = child)
    {
        child = i * 2;
        // 如果存在右子节点，且右子节点的值小于左子节点，则选择右子节点
        // 确保始终与两个子节点中较小的一个进行比较和交换，以维持最小堆性质
        if (child != obj->size && obj->data[child] > obj->data[child + 1])
        {
            ++child;
        }
        // 如果父节点大于选出的最小子节点，则将子节点上移
        if (obj->data[i] > obj->data[child])
        {
            obj->data[i] = obj->data[child];
        }
        else
        {
            // 父节点已不大于子节点，满足堆性质，停止下沉
            break;
        }
    }
    // 将暂存的原始值放入最终确定的位置
    obj->data[i] = temp;
}