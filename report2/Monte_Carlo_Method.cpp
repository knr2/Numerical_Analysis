#include <iomanip>      // setprecsion
#include <iostream>     // std::cout, std::endl, std::cin
#include <vector>     // std::cout, std::endl, std::cin
#include <cstdio>       // printf
#include <cstdlib>      // rand, std::srand
#include <cmath>        // sin, cos, tan

// 変数定義
long long count = 1;            // 座標の個数を指定
int size = 2;                  // 正方形の大きさを指定
const long double PI = acos(-1.0);          // 円周率
long long area_true_count = 0;              // 円内に入ってた回数
long double area_PI;                        // 面積から求めた確率
// ここまで

// 関数定義
void setting(void);                         // 設定
void area(long long, long long);            // 面積より
void output(void);                          // 出力
// ここまで

std::vector<int> plot ={2,4,8,10,12,20,50,100};

int main(void)
{
    setting();
    FILE *fp1;
    if ((fp1 = fopen("answer.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can not find Sentence.txt\n");
        exit(1);
    }
    for(int k = 0;k < plot.size();k++)
    {
        size = plot[k];
        fprintf(fp1, "\nN = %d\n", size);
        count = 1;
        for(int j = 0;j < 24;j++)
        {
            count *= 2;
            area_true_count = 0;
            for (long long i = 0; i < count; i++)
            {
                // (x, y)を乱数により指定
                long long x = rand() % size;
                long long y = rand() % size;
                area(x, y);
            }
            
            // 出力したいとき
            // output();

            // ファイルへ書き込む場合
            area_PI = (area_true_count * 1.) / (count * 1.) * 4;
            if(j % 2 == 0)
            {
                fprintf(fp1, "2の%d乗\t%.10Lf\t\t", j + 1, area_PI);
                std::cout << area_PI << std::endl;
            }
            else
            {
                fprintf(fp1, "2の%d乗\t%.10Lf\n", j + 1, area_PI);
                std::cout << area_PI << std::endl;
            }
        }
    }
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
    area_PI = (area_true_count * 1.) / (count * 1.) * 4;
    std::cout << "模範解" << std::endl << PI << std::endl;
    std::cout << "円の面積から求めた解" << std::endl << area_PI << std::endl << "誤差 = " << fabs(PI - area_PI) << std::endl;
}
