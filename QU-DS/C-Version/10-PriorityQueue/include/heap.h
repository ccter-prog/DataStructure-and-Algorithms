#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>

struct expected;

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
struct expected heap_remove(struct heap *obj);

#endif