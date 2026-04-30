#include "../include/heap.h"

int main(void)
{
    struct heap h = heap_init(10);
    heap_insert(&h, 20);
    heap_insert(&h, 10);
    heap_insert(&h, 5);
    heap_insert(&h, 15);
    heap_print(&h);
    return 0;
}