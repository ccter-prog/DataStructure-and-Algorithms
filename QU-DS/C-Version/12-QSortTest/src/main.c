#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void print_array(const int* arr, const size_t size);
int cmp(const void* a, const void* b);

int main(void)
{
    int array[11] = {11, 222, 3, 44, 55, 666, -100, 0, 999, -123, 1};
    size_t array_size = sizeof(array) / sizeof(int);
    qsort(array, array_size, sizeof(int), cmp);
    print_array(array, array_size);
	return 0;
}

void print_array(const int* arr, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int cmp(const void* a, const void* b)
{
    return *((int*)a) - *((int*)b);
}