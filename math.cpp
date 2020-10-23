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

#define MAX 100

const ld PI = acos(-1.0);

//変数定義
ll count = 0;                            //ある程度の回数処理を回すため
ld max = MAX, min = -1 * MAX;            //区間の橋の設定
ld search_range = 0.5;                   //探索する際の範囲幅
std::vector<std::pair<ld, ld>> interval; //±の変化した区間を記憶
//ここまで

//関数定義
void setting(void);    //設定
void zero_point(void); //零点を含む区間を探す
ld style(ld);          //式の実行
void output(void);     //出力
//ここまで

int main(void)
{
    setting();
    std::cout << "零点の探索をする際の探索幅を決めてください。\n1以上だと解が見つからないこともあるため、1未満の少数1桁を設定することが望ましいです。" << std::endl;
    std::cin >> search_range;
    zero_point();
    output();
    return 0;
}

//設定
void setting(void)
{
    std::cout << std::fixed << std::setprecision(10); //少数は10桁まで表示するように設定
}

void zero_point(void)
{
    ld left = min;
    ld right = left + fabs(search_range);
    std::map<ld, ll> memory;
    while (right < MAX)
    {
        ld a, b;
        a = style(left);
        b = style(right);
        if (a * b <= 0)
        {
            if (memory.count(left))
                break;
            interval.push_back(std::make_pair(left, right));
            if (style(right) < 0.000000001)
                memory[right] = 1;
        }
        left += fabs(search_range);
        right += fabs(search_range);
    }
    return;
}

//式
ld style(ld x)
{
    return pow(x, 2) - 1;
}

void output(void)
{
    for (ll i = 0; i < interval.size(); i++)
    {
        ld center, left, right;
        count = 0;
        left = interval[i].first;
        right = interval[i].second;
        while (fabs(left - right) > 1e-10)
        {
            if (count == 100000)
                break;
            left = interval[i].first;
            right = interval[i].second;
            center = (left + right) / 2.;
            if (style(center) == 0)
                break;
            if (style(left) == 0)
            {
                interval[i].second = interval[i].first;
                break;
            }
            if (style(right) == 0)
            {
                interval[i].first = interval[i].second;
                break;
            }
            if (style(left) * style(center) < 0)
                interval[i].second = center;
            if (style(left) * style(center) > 0)
                interval[i].first = center;
            count++;
        }
        if (fabs(interval[i].first - interval[i].second) > 1e-10)
            std::cout << "零点が区間内に複数個存在しています。\n零点の探索幅を狭くすることで解が見つかる可能性があります。" << std::endl;
        else
            std::cout << " 解" << i + 1 << ":" << ((interval[i].first + interval[i].second) / 2.) << std::endl;
    }
    return;
}
