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
struct heap heap_build(const Elem *array, const size_t size);
bool heap_decrease_key(struct heap *obj, const Elem old_value, const Elem new_value);
bool heap_increase_key(struct heap *obj, const Elem old_value, const Elem new_value);
struct expected heap_delete(struct heap *obj, const Elem value);

#endif