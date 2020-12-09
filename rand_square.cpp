#include <iostream>     // std::cout, std::endl, std::cin
#include <fstream>      // fopen, fprintf, fclose
#include <cmath>        // log10

#define round 10        //周回数

int main(void)
{
    long long default_value = 0;
    std::cout << "初期値を入力してください。" << std::endl;
    std::cin >> default_value;
    long long digits = log10(default_value) + 1;
    
    // 書き込みファイルの指定
    FILE *fp1;
    if ((fp1 = fopen("rand.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can not find rand.txt\n");
        exit(1);
    }

    for (long long i = 0; i < round; i++)
    {
        default_value = default_value * default_value;
        
        //取り出すn桁の一番後ろに移動
        for (long long j = 0; j < digits / 2; j++)
        {
            default_value /= 10;
        }
        
        //n桁を後ろから取り出す
        long long tmp = 0;
        for (long long j = 0; j < digits; j++)
        {
            tmp *= 10;
            tmp += (int)(default_value % 10);
            default_value /= 10;
        }

        //数値反転
        default_value = 0;
        for (long long j = 0; j < digits; j++)
        {
            default_value *= 10;
            default_value += (int)(tmp % 10);
            tmp /= 10;
        }

        std::cout << default_value << std::endl;
        fprintf(fp1, "%lld\n", default_value);
    }
    fclose(fp1);
    return 0;
}
