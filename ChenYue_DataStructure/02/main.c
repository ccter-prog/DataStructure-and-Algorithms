#include <stdio.h>
#include <time.h>
#include "MyFunction.h"

#define MAXN 10
#define MAXK 1e7

clock_t start, stop;
double duration;

int main()
{
    double a[MAXN];
    for (int i = 0; i < MAXN; i++)
    {
        a[i] = (double)i;
    }
    start = clock();
    for (int i = 0; i < MAXK; i++)
    {
        f1(MAXN - 1, a, 1.1);
    }
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK / MAXK;
    printf("ticks1 = %f\n", (double)(stop - start));
    printf("duration1 = %6.2e\n", duration);

    start = clock();
    for (int i = 0; i < MAXK; i++)
    {
        f2(MAXN - 1, a, 1.1);
    }
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK / MAXK;
    printf("ticks2 = %f\n", (double)(stop - start));
    printf("duration2 = %6.2e\n", duration);
    return 0;
}