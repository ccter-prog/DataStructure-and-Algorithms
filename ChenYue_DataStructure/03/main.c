#include <stdio.h>

int MaxSubseqSum1(int *A, int N)
{
    int global_max = 0;
    if (!(N <= 0))
    {
        int current_max = 0;
        for (int i = 0; i < N; i++)
        {
            current_max = (A[i] > current_max + A[i]) ? A[i] : current_max + A[i];
            if (current_max > global_max)
            {
                global_max = current_max;
            }
        }
    }
    return global_max;
}

// int test(int *A, int N)
// {
//     int global_max = 0;
//     if (N > 0)
//     {
//         for (int i = 0; i < N; i++)
//         {
//             int current_sum = 0;
//             for (int j = i; j < N; j++)
//             {
//                 current_sum += A[j];
//                 int current_result = (current_sum > 0) ? current_sum : 0;
//                 if (current_result > global_max)
//                 {
//                     global_max = current_result;
//                 }
//             }
//         }
//     }
//     return global_max;
// }

int main()
{
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int N = sizeof(A) / sizeof(int);
    printf("最大子序列和为：%d\n", MaxSubseqSum1(A, N));
    return 0;
}