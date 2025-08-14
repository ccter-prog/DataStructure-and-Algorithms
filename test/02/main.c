#include <stdio.h>

/* 任务：给定一个整数数组和一个目标值 target，找出和等于 target 的最长连续子数组，返回它的长度；如果没有，返回 0 */
int longest_subarray_with_sum(int *A, int N, int target)
{
    int size = 0;
    if (N > 0)
    {
        for (int i = 0; i < N; i++)
        {
            int current_sum = 0;
            int count = 0;
            for (int j = i; j < N; j++)
            {
                current_sum += A[j];
                count++;
                if (current_sum == target && count > size)
                {
                    size = count;
                }
            }
        }
    }
    return size;
}

int main()
{
    int A[] = {2, -1, 2};
    int N = sizeof(A) / sizeof(int);
    int target = -11;
    printf("最长的连续子数组长度为：%d\n", longest_subarray_with_sum(A, N, target));
    return 0;
}