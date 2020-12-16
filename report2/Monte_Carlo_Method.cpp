#include <iomanip>      // setprecsion
#include <iostream>     // std::cout, std::endl, std::cin
#include <cstdio>       // printf
#include <cstdlib>      // rand, std::srand
#include <cmath>        // sin, cos, tan

// 変数定義
const long long count = 1000000;            // 座標の個数を指定
const long long size = 10;                  // 正方形の大きさを指定
const long double PI = acos(-1.0);          // 円周率
long long area_true_count = 0;              // 円内に入ってた回数
long double area_PI;                        // 面積から求めた確率
// ここまで

// 関数定義
void setting(void);                         // 設定
void area(long long, long long);            // 面積より
void output(void);                          // 出力
// ここまで

int main(void)
{
    setting();
    for (long long i = 0; i < count; i++)
    {
        // (x, y)を乱数により指定
        long long x = rand() % size;
        long long y = rand() % size;
        area(x, y);
    }
    output();
    return 0;
}

// 設定
void setting(void)
{
    std::srand(time(NULL));                             // 乱数列を時間で変更
    std::cout << std::fixed << std::setprecision(15);   // 少数は10桁まで表示するように設定
}

// 面積から
void area(long long x, long long y)
{
    if ((x - size / 2.) * (x - size / 2.) + (y - size / 2.) * (y - size / 2.) <= size / 2. * size / 2.)
        area_true_count++;
}

// 出力
void output(void)
{
    area_PI = (area_true_count * 1.) / (count * 1.) * 100 / (size / 2.) / (size / 2.);
    std::cout << "模範解" << std::endl << PI << std::endl;
    std::cout << "円の面積から求めた解" << std::endl << area_PI << std::endl << "誤差 = " << fabs(PI - area_PI) << std::endl;
}