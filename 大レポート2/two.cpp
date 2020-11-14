#include <algorithm> // next_permutation
#include <iomanip>   // setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <string>    // std::string
#include <map>       // map
#include <utility>   // pair, make_pair
#include <fstream>   // fopen, fclose
#include <cstdio>    // printf
#include <cstdlib>   // exit
#include <cmath>     // sin, cos, tan

void Replacement(void);
void Char_Probability(void);

//確率計算用
std::vector<std::pair<long long, std::string>> char_probability;

int main(void)
{
    Replacement();
    Char_Probability();
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

//1文字の出現頻度を計測
void Char_Probability(void)
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

    //文字の出た回数を保存
    std::map<std::string, long long> probability;

    while (fscanf(read_file, "%c", &c_tmp) != EOF)
    {
        //読み込んだものをcharからstringに
        tmp = c_tmp;

        if (probability.count(tmp))
            probability[tmp] += 1;
        else
            probability[tmp] = 1;
    }

    tmp = 'a' - 1;
    for (long long i = 0; i < 26; i++)
    {
        //char型にして一文字進める
        c_tmp = (char)(tmp[0] + 1);

        //char型をstring型に
        tmp = c_tmp;

        //char_probabilityにpush
        char_probability.push_back(std::make_pair(probability[tmp], tmp));
    }

    tmp = 'A' - 1;
    for (long long i = 0; i < 26; i++)
    {
        //char型にして一文字進める
        c_tmp = (char)(tmp[0] + 1);

        //char型をstring型に
        tmp = c_tmp;

        //char_probabilityにpush
        char_probability.push_back(std::make_pair(probability[tmp], tmp));
    }

    char_probability.push_back(std::make_pair(probability[" "], ("space")));
    char_probability.push_back(std::make_pair(probability["\n"], ("enter")));

    std::sort(char_probability.begin(), char_probability.end());
    std::reverse(char_probability.begin(), char_probability.end());

    for (long long i = 0; i < char_probability.size(); i++)
    {
        std::cout << char_probability[i].second << "\t:" << char_probability[i].first << std::endl;
        if(char_probability[i].second.size() == 1)
            fprintf(write_file, "%s\t\t%lld\n", char_probability[i].second.c_str(), char_probability[i].first);
        else
            fprintf(write_file, "%s\t%lld\n", char_probability[i].second.c_str(), char_probability[i].first);
    }

    fclose(read_file);
    fclose(write_file);
}