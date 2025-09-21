#include <stdio.h>

int main(void)
{
    int a[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    int sum[11] = {0};
    int carry = 0;
    for (int i = 0; i < 10; i++)
    {
        int s = a[i] + b[i] + carry;
        carry = s / 10;
        sum[i] = s % 10;
    }
    if (carry > 0)
    {
        sum[10] = carry;
        printf("%d", sum[10]);
    }
    for (int i = 9; i >= 0; i--)
    {
        printf("%d", sum[i]);
    }
    putchar('\n');
    return 0;
}