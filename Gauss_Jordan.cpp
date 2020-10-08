//答えに対し式が足りないと計算不可（動作確認済み）
//今回テストに使用した式はGauss_Jordan_test.txtに置かれている
#include <algorithm> // next_permutation
#include <iomanip>   //setprecsion
#include <iostream>  // cout, endl, cin
#include <vector>    // vector
#include <fstream>     //fopen, fclose
#include <cstdio>  // printf

using namespace std;

typedef long long ll;
typedef long double ld;

//変数定義

ll line_number;                                        //行列の行数
ll number;                                        //解の数
ll ok = 0;                                             //入力の確認用
vector<vector<ld>> input_matrix(100, vector<ld>(100, 0)); //行列の行データ
vector<ld> input_ans_matrix(100, 0);                      //連立方程式の解
vector<vector<ld>> check_input_matrix(100, vector<ld>(100, 0)); //check用行列の行データ
vector<ld> check_input_ans_matrix(100, 0);                      //check用連立方程式の解
vector<ll> all_check(1, 0);
ll error = 0; //対角上に０があるときエラー


//ここまで

void setting(void); //設定
void input(void); //入力部
void L_Down(void); //処理部_1
void R_Up(void); //処理部_2
void One(void); //処理_3
void output(void); //出力部
void check(void); //途中確認用
bool last_check(); //解が誤差で死んでないか最終確認

int main()
{
    setting();
    input();
    if(error == 1) return 0;
    for(ll i = 1;i < line_number;i++) all_check.push_back(i);
    do
    {
        error = 0;
        L_Down();
        if(error == 0) break;
    }while(next_permutation(all_check.begin(), all_check.end()));
    check();
    if (error != 0)
    {
        cout << error;
        cout << "実行時にエラーが起きたため強制終了します。" << endl;
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
    cout << fixed << setprecision(5); //少数は5桁まで表示するように設定
}

//入力部
void input(void)
{
    do
    {
        cout << "行数の行数を入力してください。" << endl;
        cin >> line_number;
        cout << "求めたい解の個数を入力してください。" << endl;
        cin >> number;
        if(line_number < number)
        {
            cout << "求めたい文字に対して与えられる式が少ないので計算できません。" << endl;
            error = 1;
            return;
        }
        vector<vector<ld>> tmp_input_matrix(line_number, vector<ld>(line_number)); //一時保存用行列の行データ
        vector<ld> tmp_input_ans_matrix(line_number);                              //一時保存用連立方程式の解
        for (ll i = 0; i < line_number; i++)
        {
            printf("%lld行目の値と解を入れてください。\n", i + 1);
            for (ll j = 0; j < line_number; j++)
            {
                ld value;
                cin >> value;
                tmp_input_matrix[i][j] = value;
            }
            ld value;
            cin >> value;
            tmp_input_ans_matrix[i] = value;
        }
        cout << "これは確認です。入力があっていれば1を、間違っていれば0を入力してください。\n"
             << "--------------------------------------------------------------" << endl;
        for (ll i = 0; i < line_number; i++)
        {
            for (ll j = 0; j < line_number; j++)
            {
                cout << tmp_input_matrix[i][j] << " ";
            }
            cout << " = " << tmp_input_ans_matrix[i] << endl;
        }
        cout << "--------------------------------------------------------------" << endl;
        cin >> ok;
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
    vector<vector<ld>> tmp_input_matrix(line_number, vector<ld>(line_number)); //一時保存用行列の行データ
    vector<ld> tmp_input_ans_matrix(line_number);                              //一時保存用連立方程式の解
    for (ll i = 0; i < line_number; i++)
    {
        for (ll j = 0; j < line_number; j++)
        {
            tmp_input_matrix[i][j] = input_matrix[all_check[i]][j];
        }
        tmp_input_ans_matrix[i] = input_ans_matrix[all_check[i]];
    }
    //行数 - 1列目を０にする
    //iが列を,jが行を表す
    for(ll i = 0;i < line_number - 1;i++)
    {
        if(tmp_input_matrix[i][i] == 0)
        {
            error++;
            //後日対角化のためにシャッフル機能を追加したい
        }
        for(ll j = i + 1;j < line_number;j++)
        {
            if(tmp_input_matrix[j][i] != 0)
            {
                ld tmp = tmp_input_matrix[j][i] / tmp_input_matrix[i][i];
                for(ll k = 0;k < line_number;k++)
                {
                    tmp_input_matrix[j][k] -= tmp_input_matrix[i][k] * tmp;
                }
                tmp_input_ans_matrix[j] -= tmp_input_ans_matrix[i] * tmp;
            }
        }
    }
    if(error == 0)
    {
        for(ll i = 0;i <line_number;i++)
        {
            for(ll j = 0;j < line_number;j++)
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
    for(ll i = 0;i < line_number;i++) input_ans_matrix[i] /= input_matrix[i][i];
}

//出力部
void output(void)
{
    bool flag = last_check();
    if(flag)
    {
        for (ll i = 0; i < line_number; i++)
        {
            cout << "x" << i + 1 << " = " << input_ans_matrix[i] << endl;
        }
    }
    else cout << "解なし" << endl;
}

//確認用
void check(void)
{
    for(ll i = 0;i < line_number;i++)
    {
        for(ll j = 0;j < line_number;j++)
        {
            cout << input_matrix[i][j] << "  ";
        }
        cout << " = " << input_ans_matrix[i] << endl;
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
            if (input_ans_matrix[j] >= 1000000000 || input_ans_matrix[j] <= -10000000000)
                sum += 100000000;
                sum += check_input_matrix[i][j] * input_ans_matrix[j];
            cout << sum << endl;
        }
        //誤差が0.005より大きいときははじく(0にしないのは分数の計算時は必ずごく少数の誤差が出るため)
        if(sum - check_input_ans_matrix[i] < 0.005) flag++;
    }
    if(flag >= number) return true;
    return false;
}