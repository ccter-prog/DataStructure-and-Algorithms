#include <stdio.h>

static int findX(int *array, int length, int x)
{
    int ret = -1;
    int i = 0;
    for (; i < length && array[i] != x; i++);
    if (array[i] == x)
    {
        ret = i;
    }
    return ret;
}

static unsigned int getX(int *array, int length, int *px, int index)
{
    unsigned int flag = 1;
    if (!(index >= length))
    {
        *px = array[index];
        flag = 0;
    }
    return flag;
}

static int findMax(int *array, int length)
{
    int max = array[0];
    for (int i = 1; i < length; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int main(void)
{
    int array[10] = {-111, -22, 3333, -44, -55, -6, -7, -8, -9, -10};
    int size = sizeof(array) / sizeof(int);
    printf("%d\n", findX(array, size, 22));

    int a = 0;
    unsigned int flag = getX(array, size, &a, 2);
    printf("a = %d, flag = %u\n", a, flag);

    printf("max = %d\n", findMax(array, size));
    printf("Hello World\n");
    return 0;
}