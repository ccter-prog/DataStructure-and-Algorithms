#include <stddef.h>
#include <stdio.h>

int binary_search(int* array, int value, size_t low, size_t high);

int main(void)
{
    int array[100];
    for (int i = 0; i < 100; ++i)
    {
        array[i] = i * 10;
    }
    size_t high = sizeof(array) / sizeof(array[0]) - 1;
    int index = binary_search(array, 100, 0, high);
    printf("%d\n", index);
    return 0;
}

int binary_search(int* array, int value, size_t low, size_t high)
{
    while (low <= high)
    {
        size_t mid = (low + high) / 2;
        if (value < array[mid])
        {
            high = mid - 1;
        }
        else if (value > array[mid])
        {
            low = mid + 1;
        }
        else
        {
            return (int)mid;
        }
    }
    return -1;
}