/*
コンパイル&実行コマンド
g++ Gauss_Seidel.cpp -o test;./test
*/

//解けない問題
/*
    例
    7x + 4y + 2z = -6
    16x + 2y + z = 7

    この式は実際には（上-（下×２））をすることでxが求まるため計算できるが、
    ガウスザイデル法では解の数＞式の数のとき解くとは出来ない
*/

#include <algorithm> // next_permutation
#include <iomanip>   //setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <cstdio>    // printf

typedef long long ll;
typedef long double ld;

//変数定義

ll line_number;                                                                 //行列の行数
ll number;                                                                      //解の数
ll count;                                                                       //周回数をカウント
ll ok = 0;                                                                      //入力の確認用
std::vector<std::vector<ld>> input_matrix(100, std::vector<ld>(100, 0));        //方程式の左辺行列のデータ
std::vector<ld> input_ans_matrix(100, 0);                                       //方程式の右辺行列のデータ
std::vector<ld> answer(100, 0);                                                 //方程式の解
std::vector<std::vector<ld>> change_input_matrix(100, std::vector<ld>(100, 0)); //変形後の行列の行データ
std::vector<ld> change_input_ans_matrix(100, 0);                                //変形後の解のデータ
std::vector<std::vector<ld>> check_input_matrix(100, std::vector<ld>(100, 0));  //check用行列の行データ
std::vector<ld> check_input_ans_matrix(100, 0);                                 //check用連立方程式の解
std::vector<ll> all_check(1, 0);
ll error = 0; //対角上に０があるときエラー

//ここまで

void setting(void); //設定
void input(void);   //入力部
void x_equal(void); //x=の形に直す
ld loop(void);      //処理部
void output(void);  //出力部
void view(void);    //途中確認用
void view_ans(void);    //途中確認用
bool last_check();  //解が誤差で死んでないか最終確認

int main()
{
    setting();
    input();

    //解に対し式が足りない場合に終了
    if (error == 1)
        return 0;
    
    //x1~xnまでの式の作成　もし行数に対応するxが見つからない場合は全探索をする
    for (ll i = 1; i < line_number; i++)
        all_check.push_back(i);
    
    do
    {
        error = 0;
        x_equal();
        if (error == 0)
            break;
    } while (next_permutation(all_check.begin(), all_check.end()));
    
    //全探索をしたうえでも各xについて式が作成できなかった際に終了
    if (error != 0)
    {
        std::cout << error;
        std::cout << "一部のxについての式が作成できなかったため強制終了します。" << std::endl;
        return 0;
    }

    //確認済み

    ll stop = 0;

    count = 0;
    do
    {
        error = 1;
        ld Error = loop(); //誤差を保存
        if(count < 100)
        view_ans();
        if(count == 100)
        {
            std::cout << "出力が多くなりすぎる可能性があります。終了まで出力を止めたい場合は0を入力してください。" << std::endl;
            std::cin >> stop;
        }
        if(stop != 0)
            view_ans();
        if (Error < 0.0000000000001 && Error > -0.0000000000001)
            error = 0;
        count++; //回数が多くなりすぎたら強制終了
    } while (error != 0 && count < 100000);
    
    if(count >= 100000)
    {
    std::cout << "答えが発散しました。" << std::endl;
    return 0;
    }
    output();

    return 0;
}

//設定
void setting(void)
{
    std::cout << std::fixed << std::setprecision(10); //少数を10桁まで表示するように設定
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
            printf("%lld行目の方程式を入れてください。\n", i + 1);
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
                  << "=============================================================================================" << std::endl;
        for (ll i = 0; i < line_number; i++)
        {
            for (ll j = 0; j < line_number; j++)
            {
                std::cout << tmp_input_matrix[i][j] << " ";
            }
            std::cout << " = " << tmp_input_ans_matrix[i] << std::endl;
        }
        std::cout << "=============================================================================================" << std::endl;
        std::cin >> ok;
        //あっていれば一時保存用からグローバル関数へ移行&&適当な初期値を入力
        if (ok == 1)
        {
            std::cout << "適当な解を入力してください" << std::endl;
            for (ll i = 0; i < line_number; i++)
            {
                std::cin >> answer[i];
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

//処理部1
void x_equal(void)
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
    for (ll i = 0; i < line_number; i++)
    {
        if (tmp_input_matrix[i][i] == 0)
        {
            error = 1;
            return;
        }
        for (ll j = 0; j < line_number; j++)
        {
            change_input_matrix[i][j] = tmp_input_matrix[i][j] / tmp_input_matrix[i][i] * -1;
        }
        change_input_ans_matrix[i] = tmp_input_ans_matrix[i] / tmp_input_matrix[i][i];
    }
}

//処理部2
ld loop(void)
{
    ld ERROR = 0;
    for (ll i = 0; i < line_number; i++)
    {
        ld tmp = answer[i];
        answer[i] = 0;
        for (ll j = 0; j < line_number; j++)
        {
            if (i == j)
                continue;
            answer[i] += change_input_matrix[i][j] * answer[j];
        }
        answer[i] += change_input_ans_matrix[i];
        ld diff = tmp - answer[i];
        //誤差が出た際に+と-で相殺しないようにするため
        /*
        誤差が1と-1のときこの処理をしないと誤差がないことになる
        */
        if(diff < 0) diff * -1;
        ERROR += diff;
    }
    return ERROR;
}

//出力部
void output(void)
{
    bool flag = last_check();
    if (flag)
    {
        for (ll i = 0; i < line_number; i++)
        {
            std::cout << "x" << i + 1 << " = " << answer[i] << std::endl;
        }
    }
    else
        std::cout << "解なし" << std::endl;
}

//確認用
void view(void)
{
    for (ll i = 0; i < line_number; i++)
    {
        for (ll j = 0; j < line_number; j++)
        {
            std::cout << input_matrix[i][j] << "  ";
        }
        std::cout << " = " << input_ans_matrix[i] << std::endl;
    }
    std::cout << "=============================================================================================" << std::endl;
    for (ll i = 0; i < line_number; i++)
    {
        std::cout << answer[i] << "  ";
    }
    std::cout << std::endl;
}

//確認用
void view_ans()
{
    printf("count[%05lld]:", count + 1);
    for (ll i = 0; i < line_number; i++)
    {
        std::cout << answer[i] << "  ";
    }
    std::cout << std::endl;
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
            if (answer[j] >= 1000000000 || answer[j] <= -10000000000)
                sum += 100000000;
            sum += check_input_matrix[i][j] * answer[j];
        }
        //差が大きい場合は解が間違っている
        if (sum - input_ans_matrix[i] > 0.0000001 && sum - input_ans_matrix[i] < -0.0000001)
            return false;
    }
    return true;
}