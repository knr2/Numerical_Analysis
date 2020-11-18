#include <algorithm> // next_permutation
#include <iomanip>   // setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <string>    // std::string
#include <map>       // map
#include <utility>   // pair, make_pair
#include <fstream>   // fopen, fclose
#include <cstdio>    // printf
#include <cstdlib>   // exit
#include <cmath>     // sin, cos, tan

// 変数定義

    FILE *writing_file; // 書き込みファイル

    long long integration_space; // 積分空間を何等分するか
    long long round_number = 15; // 何回微分区間(Δx)を設定しなおすか

    long double y; // y座標を記憶

    // それぞれの問題における区間端と一回の移動距離

    long double section_min_one = 0;
    long double section_max_one = 3;
    long double moving_distance_one;

    long double section_min_two = 1;
    long double section_max_two = 2;
    long double moving_distance_two;

    // ここまで

    // 関数定義

    void setting(void); // 設定
    void input(void);   // 入力

    // x座標を受け取りy座標を返す
    long double problem_one(long double); // 問題1
    long double problem_two(long double); // 問題2

    // 計算をする
    void trapezoid_method(void); // 台形法
    void simpson_method(void); // シンプソン法

// ここまで

int main(void)
{
    setting();

    for (long long i = 0; i < round_number;i++)
    {
        input();
        trapezoid_method();
        simpson_method();
    }
    return 0;
}

// 設定
void setting(void)
{
    // 少数は10桁まで表示するように設定
    std::cout << std::fixed << std::setprecision(10);

    // 解を書き込むファイルの指定
    if ((writing_file = fopen("answer.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can not find answer.txt\n");
        exit(1);
    }
    fprintf(writing_file, "∫(x⁴ - 2x³ + x² - 3x + 1)dx\t|\t∫(1 / x)dx\n\n");
    fprintf(writing_file, "\n解\n6.6000000000\t\t\t\t|\t0.6931471806\n\n");
}

// 入力
void input(void)
{
    std::cout << "積分空間を何等分するかを入力してください." << std::endl;
    std::cin >> integration_space;
    
    // 移動距離を設定
    moving_distance_one = (section_max_one - section_min_one) / integration_space;
    moving_distance_two = (section_max_two - section_min_two) / integration_space;
}

// 問題1
long double problem_one(long double x)
{
    return (pow(x, 4) - 2 * pow(x, 3) + pow(x, 2) - 3 * x + 1);
}

// 問題2
long double problem_two(long double x)
{
    return (1 / x);
}

void trapezoid_method(void)
{
    
    y = 0;
    for(long long i = 0;i <= integration_space;i++)
    {
        long double tmp = section_min_one + i * moving_distance_one;
        if(i == 0||i == integration_space)
            y += problem_one(tmp);
        else
            y += 2 * problem_one(tmp);
    }
    y *= moving_distance_one / 2.;
    fprintf(writing_file, "--------------------------------------------\n\t%lld分割した際の台形法の解\n--------------------------------------------\n", integration_space);
    fprintf(writing_file, "%.10Lf\t\t\t\t|\t", y);
    
    y = 0;
    for (long long i = 0; i <= integration_space; i++)
    {
        long double tmp = section_min_two + i * moving_distance_two;
        if (i == 0 || i == integration_space)
            y += problem_two(tmp);
        else
            y += 2 * problem_two(tmp);
    }
    y *= moving_distance_two / 2.;
    fprintf(writing_file, "%.10Lf\n\n", y);
}

void simpson_method(void)
{
    y = 0;
    for(long long i = 0;i <= integration_space * 2;i++)
    {
        long double tmp = section_min_one + i * moving_distance_one / 2.;
        if(i == 0||i == integration_space)
            y += problem_one(tmp);
        else if(i % 2 == 1)
            y += 2 * problem_one(tmp);
        else if(i % 2 == 0)
            y += 4 * problem_one(tmp);
        }
    y *= moving_distance_one / 6.;
    
    fprintf(writing_file, "--------------------------------------------\n\t%lld分割した際のシンプソン法の解\n--------------------------------------------\n", integration_space);
    fprintf(writing_file, "%.10Lf\t\t\t\t|\t", y);

    y = 0;
    for (long long i = 0; i <= integration_space * 2; i++)
    {
        long double tmp = section_min_two + i * moving_distance_two / 2.;
        if (i == 0 || i == integration_space)
            y += problem_one(tmp);
        else if (i % 2 == 0)
            y += 2 * problem_two(tmp);
        else if (i % 2 == 1)
            y += 4 * problem_two(tmp);
    }
    y *= moving_distance_two / 6.;

    fprintf(writing_file, "%.10Lf\n\n\n", y);
}