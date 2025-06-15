#include <math.h>
#include "MyFunction.h"

double f1(int n, double *a, double x)
{
    double p = a[0];
    for (int i = 1; i <= n; i++)
    {
        p += (a[i] * pow(x, i));
    }
    return p;
}

double f2(int n, double *a, double x)
{
    double p = a[n];
    for (int i = n; i > 0; i--)
    {
        p = a[i - 1] + x * p;
    }
    return p;
}