#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define x_range 1000

long double convert(long double);
long double func(long double);
long double func_d(long double);

int main(void)
{
    long long number = 0;
    long double answer[1000];
    for (long long j = 0; j < 1000; j++)
    {
        answer[j] = 100000000;
    }
    //全ての解を見つけるため、-1000~1000までの範囲で接点を探索する。
    for(long long i = -x_range;i < x_range;i++)
    {
        long double tmp_number_of_solution = i;
        long double before; //処理前のxの値を記憶
        long long count = 0;
        do
        {
            before = tmp_number_of_solution;

            tmp_number_of_solution = convert(tmp_number_of_solution);
        } while (fabs(before - tmp_number_of_solution) > 1e-10&&count <= 100000);
        if (fabs(before - tmp_number_of_solution) < 1e-10)
        {
            for(long long j = 0;j < number + 1;j++)
            {
                //同じ答えが複数回でる可能性があるので、今まで記憶したものと比較し差が小さいものははじく
                if (fabs(tmp_number_of_solution - answer[j]) < 1e-10)
                    break;
                //まだ記憶していなければ新しく記憶
                else if(answer[j] == 100000000)
                {
                    //-0.0000000000を0.0000000000と表記するように
                    if (tmp_number_of_solution >= -0.00000000004 && tmp_number_of_solution <= 0.00000000004)
                        tmp_number_of_solution = fabs(tmp_number_of_solution);
                    answer[j] = tmp_number_of_solution;
                    number++;
                    break;
                }
                else continue;
            }
        }
    }
    for(long long i = 0;i < number;i++)
    {
        for(long long j = i + 1;j < number;j++)
        {
            //昇順にソートしたいとき
            /*
            if (answer[i] < answer[j])
            {
                long double tmp = answer[i];
                answer[i] = answer[j];
                answer[j] = tmp;
            }
            */
            //降順にソートしたいとき
            if(answer[i] > answer[j])
            {
                long double tmp = answer[i];
                answer[i] = answer[j];
                answer[j] = tmp;
            }
        }
    }
    for(long long i = 0;i < number;i++)
    {
        printf("solution %lld : %.10Lf\n", i + 1, answer[i]);
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
    return x * x - 1.;
    //test 2
    //return x * x * x + 5. * x * x - 8. * x;
    //test 3
    //return sin(x);
}

long double func_d(long double x)
{
    //test 1
    return x * 2;
    //test 2
    //return 3 * x * x + 10. * x - 8.;
    //test 3
    //return cos(x);
}