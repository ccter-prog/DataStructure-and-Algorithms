#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>

typedef int Elem;

struct heap
{
    Elem *data;
    size_t capacity;
    size_t size;
};

struct heap heap_init(const size_t capacity);
void heap_destroy(struct heap *obj);
void heap_print(const struct heap *obj);
bool heap_insert(struct heap *obj, const Elem value);

#endif