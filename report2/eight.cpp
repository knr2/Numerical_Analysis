#include <algorithm> // next_permutation
#include <iomanip>   // setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <string>    // std::string
#include <map>       // std::map
#include <numeric>   // std::accumulate
#include <utility>   // pair, make_pair
#include <fstream>   // fopen, fclose
#include <ctime>     // time
#include <cstdio>    // printf
#include <cstdlib>   // exit, srand, rand
#include <cmath>     // sin, cos, tan

//文を計測しやすいよう下処理
void Replacement(void);

//確率測定
void Word_Probability(void);

//文の作成
void Word_Sentence(void);

//確率計算用
std::vector<std::pair<long long, std::string>> word_probability;

int main(void)
{
    Replacement();
    Word_Probability();
    Word_Sentence();
    return 0;
}

//Sentence.txtを開き、アルファベット、空白、改行以外を空白に置換し、Replacement.txtに保存
void Replacement(void)
{
    //ファイルを読み込み
    FILE *read_file, *write_file;
    if ((read_file = fopen("Sentence.txt", "r")) == NULL)
    {
        fprintf(stderr, "Can not find Sentence.txt\n");
        exit(1);
    }
    if ((write_file = fopen("Replacement.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can not find Replacement.txt\n");
        exit(1);
    }

    //大文字と小文字を区別す津かどうかのフラグ立て
    int flag = 0;
    puts("大文字と小文字の区別をする場合は1を入力してください。");
    puts("区別しない場合は0を入力してください。");
    scanf("%d", &flag);

    //文字の一時保存
    char tmp;

    while (fscanf(read_file, "%c", &tmp) != EOF)
    {
        //小文字を書き込み
        if (tmp >= 'a' && tmp <= 'z')
            fprintf(write_file, "%c", tmp);
        //大文字を小文字にして書き込み
        else if (tmp >= 'A' && tmp <= 'Z' && flag == 0)
            fprintf(write_file, "%c", tmp - 'A' + 'a');
        //大文字を書き込み
        else if (tmp >= 'A' && tmp <= 'Z' && flag == 1)
            fprintf(write_file, "%c", tmp);
        //改行の書き込み
        else if (tmp == 0x0a)
            fprintf(write_file, "\n");
        //その他のものを空白に
        else
            fprintf(write_file, " ");
    }

    fclose(read_file);
    fclose(write_file);
}

//単語ごとに区別
void Word_Probability()
{
    FILE *read_file, *write_file;
    if ((read_file = fopen("Replacement.txt", "r")) == NULL)
    {
        fprintf(stderr, "Can not find Replacement.txt\n");
        exit(1);
    }
    if ((write_file = fopen("Probability.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can not find Probability.txt\n");
        exit(1);
    }

    //文字の一時保存
    char c_tmp;
    std::string tmp;
    long long word = 0;

    //文字の出た回数を保存
    std::map<std::string, long long> probability;

    //単語の種類の記憶
    std::vector<std::string> key;

    while (fscanf(read_file, "%c", &c_tmp) != EOF)
    {
        if (c_tmp == ' ' || c_tmp == 0x0a)
        {
            //単語の記憶
            if (probability.count(tmp))
                probability[tmp] += 1;
            else
            {
                if (tmp[0] == ' ' || tmp[0] == 0x0a)
                {
                    word = 0;
                }
                else
                {
                    probability[tmp] = 1;
                    key.push_back(tmp);
                }
            }

            word = 0;
        }
        else
        {
            if (word == 0)
            {
                tmp = c_tmp;
                word++;
                continue;
            }
            //読み込んだものをcharからstringに
            tmp.push_back(c_tmp);
        }
    }

    for (long long i = 0; i < key.size(); i++)
    {

        //char型をstring型に
        tmp = key[i];

        //word_probabilityにpush
        word_probability.push_back(std::make_pair(probability[tmp], tmp));
    }

    std::sort(word_probability.begin(), word_probability.end());
    std::reverse(word_probability.begin(), word_probability.end());

    for (long long i = 0; i < word_probability.size(); i++)
    {
        std::cout << word_probability[i].second << "\t:" << word_probability[i].first << std::endl;
        fprintf(write_file, "%s\t%lld\n", word_probability[i].second.c_str(), word_probability[i].first);
    }

    fclose(read_file);
    fclose(write_file);
}

void Word_Sentence()
{
    //乱数取得
    std::srand(time(NULL));

    //ファイルを読み込み
    FILE *write_file;
    if ((write_file = fopen("English.txt", "w")) == NULL)
    {
        fprintf(stderr, "Can not find English.txt\n");
        exit(1);
    }

    //文字数カウント
    long long sum = 0;
    for (long long i = 0; i < word_probability.size(); i++)
    {
        sum += word_probability[i].first;
    }

    long long count = 0;
    do
    {
        count++;
        //乱数取得
        long long position = rand() % sum;

        //現在地を取得
        long long tmp = 0;
        for (long long i = 0; i < word_probability.size(); i++)
        {
            tmp += word_probability[i].first;

            //乱数を超えたらその文字を出力
            if (tmp >= position)
            {
                //出力
                std::cout << word_probability[i].second << (count != 130 ? " " : ".\n");

                //ファイルに書き込み
                if (count != 130)
                    fprintf(write_file, "%s ", word_probability[i].second.c_str());
                else
                    fprintf(write_file, "%s.\n", word_probability[i].second.c_str());
                break;
            }
        }
    } while (count != 130);

    fclose(write_file);
}