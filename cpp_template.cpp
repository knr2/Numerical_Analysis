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

typedef long long ll;
typedef long double ld;

const ld PI = acos(-1.0);

//変数定義
//ここまで

//関数定義
void setting(void);    //設定
//ここまで

int main(void)
{
    setting();
    return 0;
}

//設定
void setting(void)
{
    std::cout << std::fixed << std::setprecision(10); //少数は10桁まで表示するように設定
}