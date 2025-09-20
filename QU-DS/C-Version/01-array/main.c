#include <stdio.h>
#include <stdlib.h>

int func(int *array, int size) 
{
    return array[0];
}

int main()
{
    int array[100] = {11, 22, 33, 44, 55};
    int *p = (int*)malloc(100 * sizeof(int));
    printf("%d\n", func(array, 100));
    free(p);
    return 0;
}