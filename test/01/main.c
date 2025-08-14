#include <stdio.h>

/* 任务：给定一个整数数组，找出连续子数组（至少包含一个元素）的最大乘积，返回这个乘积。 */
int max_product_subarray(int *A, int N)
{
    int global_max = A[0];
    if (N > 0)
    {
        for (int i = 0; i < N; i++)
        {
            int current_sum = 1;
            for (int j = i; j < N; j++)
            {
                current_sum *= A[j];
                if (current_sum > global_max)
                {
                    global_max = current_sum;
                }
            }
        }
    }
    return global_max;
}

int main()
{
    int A[] = {-3};
    int N = sizeof(A) / sizeof(int);
    printf("最大乘积为：%d\n", max_product_subarray(A, N));
    return 0;
}