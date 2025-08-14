#include <stdio.h>

/* 任务：计算一个数组中所有可能的连续子数组的和的总和（不需要和 0 比较，直接累加所有子数组的和）。 */
int sum_of_all_subarray_sums(int *A, int N)
{
    int sum = 0;
    if (N > 0)
    {
        for (int i = 0; i < N; i++)
        {
            int count = (i + 1) * (N - i);
            sum += A[i] * count;
        }
    }
    return sum;
}

int main()
{
    int A[] = {1, 2};
    int N = sizeof(A) / sizeof(int);
    printf("所有可能的连续子数组的和的总和为：%d\n", sum_of_all_subarray_sums(A, N));
    return 0;
}