#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define x_range 1000

long double convert(long double);
long double func(long double);
long double func_d(long double);

int main(void)
{
    
    //iには求めた解の個数を入力。
    for (long long i = 0; i < 3; i++)
    {
        //仮の解を代入
        long double tmp_number_of_solution = -100;
        if(i == 0)
        tmp_number_of_solution = -3;
        else if(i == 1)
            tmp_number_of_solution = -1;
        else if(i == 2)
            tmp_number_of_solution = 3000;
        long double before; //処理前のxの値を記憶
        long long count = 0;
        do
        {
            before = tmp_number_of_solution;
            tmp_number_of_solution = convert(tmp_number_of_solution);
            printf("%LF\n", before);
        } while (fabs(before - tmp_number_of_solution) > 1e-10 && count <= 100000);
        printf("%Lf\n\n", tmp_number_of_solution);
    }
    return 0;
}

long double convert(long double x)
{
    return ((-func(x) / func_d(x)) + x);
}

long double func(long double x)
{
    //test 1
    //return x * x - 1.;
    //test 2
    //return x * x * x + 5. * x * x - 8. * x;
    //test 3
    return sin(x);
}

long double func_d(long double x)
{
    //test 1
    //return x * 2;
    //test 2
    //return 3 * x * x + 10. * x - 8.;
    //test 3
    return cos(x);
}