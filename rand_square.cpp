#include <algorithm> // next_permutation
#include <iomanip>   //setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <string>    // std::string
#include <map>       //map
#include <utility>   // pair, make_pair
#include <fstream>   //fopen, fclose
#include <cstdio>    // printf
#include <cstdlib>
#include <cmath> // sin, cos, tan

#define round 10 //周回数

int main(void)
{
    long long default_value = 0;
    std::cout << "初期値を入力してください。" << std::endl;
    std::cin >> default_value;
    long long digits = log10(default_value) + 1;
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
        default_value = 0;
        //数値反転
        for (long long j = 0; j < digits; j++)
        {
            default_value *= 10;
            default_value += (int)(tmp % 10);
            tmp /= 10;
        }
        std::cout << default_value << std::endl;
        std::cin >> tmp;
    }
    return 0;
}
