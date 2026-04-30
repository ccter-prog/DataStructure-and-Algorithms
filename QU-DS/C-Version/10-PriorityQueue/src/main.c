#include "../include/heap.h"
#include "../include/expected.h"
#include <stdio.h>

int main(void)
{
    struct heap h = heap_init(10);
    heap_insert(&h, 20);
    heap_insert(&h, 10);
    heap_insert(&h, 5);
    heap_insert(&h, 15);
    heap_insert(&h, 30);
    heap_print(&h);
    struct expected temp = heap_remove(&h);
    if (temp.has_value)
    {
        printf("%d\n", temp.value);
    }
    heap_print(&h);
    heap_destroy(&h);
    return 0;
}