#include "../include/heap.h"
#include "../include/expected.h"
// #include <stdio.h>

int main(void)
{
    // Elem array[6] = {10, 50, 60, 5, 30, 20};
    // struct heap h = heap_build(array, sizeof(array) / sizeof(array[0]));
    // heap_print(&h);

    struct heap h = heap_init(50);
    heap_insert(&h, 5);
    heap_insert(&h, 10);
    heap_insert(&h, 20);
    heap_delete(&h, 10);
    heap_print(&h);
    heap_destroy(&h);
    return 0;
}