//今回テストに使用した式はGauss_Jordan_test.txtに置かれている
#include <algorithm> // next_permutation
#include <iomanip>   //setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <fstream>   //fopen, fclose
#include <cstdio>    // printf

typedef long long ll;
typedef long double ld;

//変数定義

ll line_number;                                                                //行列の行数
ll number;                                                                     //解の数
ll ok = 0;                                                                     //入力の確認用
std::vector<std::vector<ld>> input_matrix(100, std::vector<ld>(100, 0));       //行列の行データ
std::vector<ld> input_ans_matrix(100, 0);                                      //連立方程式の解
std::vector<std::vector<ld>> check_input_matrix(100, std::vector<ld>(100, 0)); //check用行列の行データ
std::vector<ld> check_input_ans_matrix(100, 0);                                //check用連立方程式の解
std::vector<ll> all_check(1, 0);
ll error = 0; //対角上に０があるときエラー

//ここまで

void setting(void); //設定
void input(void);   //入力部
void L_Down(void);  //処理部_1
void R_Up(void);    //処理部_2
void One(void);     //処理_3
void output(void);  //出力部
void check(void);   //途中確認用
bool last_check();  //解が誤差で死んでないか最終確認

int main()
{
    setting();
    input();
    if (error == 1)
        return 0;
    for (ll i = 1; i < line_number; i++)
        all_check.push_back(i);
    do
    {
        error = 0;
        L_Down();
        if (error == 0)
            break;
    } while (next_permutation(all_check.begin(), all_check.end()));
    check();
    if (error != 0)
    {
        std::cout << error;
        std::cout << "実行時にエラーが起きたため強制終了します。" << std::endl;
        return 0;
    }
    R_Up();
    check();
    One();
    output();
    return 0;
}

//設定
void setting(void)
{
    std::cout << std::fixed << std::setprecision(20); //少数は5桁まで表示するように設定
}

//入力部
void input(void)
{
    do
    {
        std::cout << "行数の行数を入力してください。" << std::endl;
        std::cin >> line_number;
        std::cout << "求めたい解の個数を入力してください。" << std::endl;
        std::cin >> number;
        if (line_number < number)
        {
            std::cout << "求めたい文字に対して与えられる式が少ないので計算できません。" << std::endl;
            error = 1;
            return;
        }
        std::vector<std::vector<ld>> tmp_input_matrix(line_number, std::vector<ld>(line_number)); //一時保存用行列の行データ
        std::vector<ld> tmp_input_ans_matrix(line_number);                                        //一時保存用連立方程式の解
        for (ll i = 0; i < line_number; i++)
        {
            printf("%lld行目の値と解を入れてください。\n", i + 1);
            for (ll j = 0; j < line_number; j++)
            {
                ld value;
                std::cin >> value;
                tmp_input_matrix[i][j] = value;
            }
            ld value;
            std::cin >> value;
            tmp_input_ans_matrix[i] = value;
        }
        std::cout << "これは確認です。入力があっていれば1を、間違っていれば0を入力してください。\n"
                  << "--------------------------------------------------------------" << std::endl;
        for (ll i = 0; i < line_number; i++)
        {
            for (ll j = 0; j < line_number; j++)
            {
                std::cout << tmp_input_matrix[i][j] << " ";
            }
            std::cout << " = " << tmp_input_ans_matrix[i] << std::endl;
        }
        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cin >> ok;
        //あっていれば一時保存用からグローバル関数へ移行
        if (ok == 1)
        {
            for (ll i = 0; i < line_number; i++)
            {
                for (ll j = 0; j < line_number; j++)
                {
                    input_matrix[i][j] = tmp_input_matrix[i][j];
                    check_input_matrix[i][j] = tmp_input_matrix[i][j];
                }
                input_ans_matrix[i] = tmp_input_ans_matrix[i];
                check_input_ans_matrix[i] = tmp_input_ans_matrix[i];
            }
        }
    } while (ok == 0);
}

//処理部
void L_Down(void)
{
    std::vector<std::vector<ld>> tmp_input_matrix(line_number, std::vector<ld>(line_number)); //一時保存用行列の行データ
    std::vector<ld> tmp_input_ans_matrix(line_number);                                        //一時保存用連立方程式の解
    for (ll i = 0; i < line_number; i++)
    {
        for (ll j = 0; j < line_number; j++)
        {
            tmp_input_matrix[i][j] = input_matrix[all_check[i]][j];
        }
        tmp_input_ans_matrix[i] = input_ans_matrix[all_check[i]];
    }
    //iが列を,jが行を表す
    for (ll i = 0; i < line_number - 1; i++)
    {
        if (tmp_input_matrix[i][i] == 0)
        {
            error++;
        }
        for (ll j = i + 1; j < line_number; j++)
        {
            if (tmp_input_matrix[j][i] != 0)
            {
                ld tmp = tmp_input_matrix[j][i] / tmp_input_matrix[i][i];
                for (ll k = 0; k < line_number; k++)
                {
                    tmp_input_matrix[j][k] -= tmp_input_matrix[i][k] * tmp;
                }
                tmp_input_ans_matrix[j] -= tmp_input_ans_matrix[i] * tmp;
            }
        }
    }
    if (error == 0)
    {
        for (ll i = 0; i < line_number; i++)
        {
            for (ll j = 0; j < line_number; j++)
            {
                input_matrix[i][j] = tmp_input_matrix[i][j];
            }
            input_ans_matrix[i] = tmp_input_ans_matrix[i];
        }
    }
}

//処理部
void R_Up(void)
{
    //行数 - 1列目を０にする
    //iが列を,jが行を表す
    for (ll i = line_number - 1; i >= 0; i--)
    {
        for (ll j = i - 1; j >= 0; j--)
        {
            if (input_matrix[j][i] != 0)
            {
                ld tmp = input_matrix[j][i] / input_matrix[i][i];
                for (ll k = 0; k < line_number; k++)
                {
                    input_matrix[j][k] -= input_matrix[i][k] * tmp;
                }
                input_ans_matrix[j] -= input_ans_matrix[i] * tmp;
            }
        }
    }
}

//処理部
void One(void)
{
    for (ll i = 0; i < line_number; i++)
        input_ans_matrix[i] /= input_matrix[i][i];
}

//出力部
void output(void)
{
    bool flag = last_check();
    if (flag)
    {
        for (ll i = 0; i < line_number; i++)
        {
            std::cout << char((ll)('a') + i) << " = " << input_ans_matrix[line_number - i - 1] << " ";
        }
    }
    else
        std::cout << "解なし" << std::endl;
}

//確認用
void check(void)
{
    for (ll i = 0; i < line_number; i++)
    {
        for (ll j = 0; j < line_number; j++)
        {
            std::cout << input_matrix[i][j] << "  ";
        }
        std::cout << " = " << input_ans_matrix[i] << std::endl;
    }
}

//最終確認用
bool last_check(void)
{
    ll flag = 0;
    for (ll i = 0; i < line_number; i++)
    {
        ld sum = 0;
        for (ll j = 0; j < line_number; j++)
        {
            //あまりにも数値が大きいまたは、小さい場合は誤差により死んでいる可能性が高いためはじかれるようにする
            if (input_ans_matrix[j] >= 1000000000 || input_ans_matrix[j] <= -10000000000)
                sum += 100000000;
            sum += check_input_matrix[i][j] * input_ans_matrix[j];
            std::cout << sum << std::endl;
        }
        //誤差が0.005より大きいときははじく(0にしないのは分数の計算時は必ずごく少数の誤差が出るため)
        if (sum - check_input_ans_matrix[i] < 0.005)
            flag++;
    }
    if (flag >= number)
        return true;
    return false;
}