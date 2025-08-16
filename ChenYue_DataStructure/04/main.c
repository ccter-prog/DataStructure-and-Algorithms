#include <stdio.h>

int MaxSubseqSums(int *A, int N)
{
    int MaxSum = 0;
    int ThisSum = 0;
    for (int i = 0; i < N; i++)
    {
        ThisSum += A[i];
        if (ThisSum > MaxSum)
        {
            MaxSum = ThisSum;
        }
        else if (ThisSum < 0)
        {
            ThisSum = 0;
        }
    }
    return MaxSum;
}

int main()
{
    int A[] = {-1, 3, -2, 4, -6, 1, 6, -1};
    int N = sizeof(A) / sizeof(int);
    printf("最大子列和为：%d\n", MaxSubseqSums(A, N));
    return 0;
}