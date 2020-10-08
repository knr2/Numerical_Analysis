/*
実行時
gcc test.c -lm;./a.out
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    long long a;
    double b;
    scanf("%lld %lf", &a, &b);
    printf("%lld %lf\n", a, sqrt(b));
    return 0;
}