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
void Pair_Probability(void);

//確率計算用
std::vector<std::pair<long long, std::string>> pair_probability;

int main(void)
{
    Replacement();
    Pair_Probability();
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

//2文字の出現頻度を計測
void Pair_Probability(void)
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
    char c_tmp, c_tmp_two;
    std::string tmp, tmp_two;

    //文字の出た回数を保存
    std::map<std::string, long long> probability;

    //処理回数
    long long count = 0;

    //一文字前の文字を記憶
    char before_tmp;

    while (fscanf(read_file, "%c", &c_tmp) != EOF)
    {
        //2個ペアで読みたいので初回はやらない
        if (count > 0)
        {
            //読み込んだものをcharからstringに
            tmp = before_tmp;
            tmp.push_back(c_tmp);
            if (probability.count(tmp))
                probability[tmp] += 1;
            else
                probability[tmp] = 1;
        }

        //一文字前の文字を記憶
        before_tmp = c_tmp;
        count++;
    }

    tmp = 'a' - 1;
    for (long long i = 0; i < 26; i++)
    {
        //char型にして一文字進める
        c_tmp = (char)(tmp[0] + 1);
        tmp_two = 'a' - 1;
        for (long long j = 0; j < 26; j++)
        {
            c_tmp_two = (char)(tmp_two[0] + 1);
            tmp_two[0] += 1;

            //char型をstring型に
            tmp = c_tmp;
            tmp.push_back(c_tmp_two);

            //pair_probabilityにpush
            pair_probability.push_back(std::make_pair(probability[tmp], tmp));
        }
    }

    tmp = 'a' - 1;
    for (long long i = 0; i < 26; i++)
    {
        std::string out;
        //char型にして一文字進める
        c_tmp = (char)(tmp[0] + 1);

        //後ろに空白、改行がある場合

        std::string T;
        //char型をstring型に
        T = c_tmp;
        T.push_back(' ');

        //pair_probabilityにpush
        out = c_tmp;
        out.push_back(' ');
        out.push_back('s');
        out.push_back('p');
        out.push_back('a');
        out.push_back('c');
        out.push_back('e');
        pair_probability.push_back(std::make_pair(probability[T], out));

        //char型をstring型に
        T = c_tmp;
        T.push_back(0x0a);

        //pair_probabilityにpush
        out = c_tmp;
        out.push_back(' ');
        out.push_back('e');
        out.push_back('n');
        out.push_back('t');
        out.push_back('e');
        out.push_back('r');
        pair_probability.push_back(std::make_pair(probability[T], out));

        //前に空白、改行がある場合

        //char型をstring型に
        T = ' ';
        T.push_back(c_tmp);

        //pair_probabilityにpush
        out = "space ";
        out.push_back(c_tmp);
        pair_probability.push_back(std::make_pair(probability[T], out));

        //char型をstring型に
        T = 0x0a;
        T.push_back(c_tmp);

        //pair_probabilityにpush
        out = "enter ";
        out.push_back(c_tmp);
        pair_probability.push_back(std::make_pair(probability[T], out));
        tmp = tmp[0] + 1;
    }

    /*
    tmp = 'A' - 1;
    for (long long i = 0; i < 26; i++)
    {
        //char型にして一文字進める
        c_tmp = (char)(tmp[0] + 1);
        tmp_two = 'A' - 1;
        for (long long j = 0; j < 26; j++)
        {
            c_tmp_two = (char)(tmp_two[0] + 1);
            tmp_two[0] += 1;

            //char型をstring型に
            tmp = c_tmp;
            tmp.push_back(c_tmp_two);

            //pair_probabilityにpush
            pair_probability.push_back(std::make_pair(probability[tmp], tmp));
        }
    }

    tmp = 'A' - 1;
    for (long long i = 0; i < 26; i++)
    {
        std::string out;
        //char型にして一文字進める
        c_tmp = (char)(tmp[0] + 1);

        //後ろに空白、改行がある場合

        std::string T;
        //char型をstring型に
        T = c_tmp;
        T.push_back(' ');

        //pair_probabilityにpush
        out = c_tmp;
        out.push_back(' ');
        out.push_back('s');
        out.push_back('p');
        out.push_back('a');
        out.push_back('c');
        out.push_back('e');
        pair_probability.push_back(std::make_pair(probability[T], out));

        //char型をstring型に
        T = c_tmp;
        T.push_back(0x0a);

        //pair_probabilityにpush
        out = c_tmp;
        out.push_back(' ');
        out.push_back('e');
        out.push_back('n');
        out.push_back('t');
        out.push_back('e');
        out.push_back('r');
        pair_probability.push_back(std::make_pair(probability[T], out));

        //前に空白、改行がある場合

        //char型をstring型に
        T = ' ';
        T.push_back(c_tmp);

        //pair_probabilityにpush
        out = "space";
        out.push_back(c_tmp);
        pair_probability.push_back(std::make_pair(probability[T], out));

        //char型をstring型に
        T = 0x0a;
        T.push_back(c_tmp);

        //pair_probabilityにpush
        out = "enter ";
        out.push_back(c_tmp);
        pair_probability.push_back(std::make_pair(probability[T], out));
        tmp = tmp[0] + 1;
    }
    */

    std::sort(pair_probability.begin(), pair_probability.end());
    std::reverse(pair_probability.begin(), pair_probability.end());

    for (long long i = 0; i < pair_probability.size(); i++)
    {
        std::cout << pair_probability[i].second << "\t:" << pair_probability[i].first << std::endl;
        if (pair_probability[i].second.size() == 2)
            fprintf(write_file, "%s\t\t%lld\n", pair_probability[i].second.c_str(), pair_probability[i].first);
        else
            fprintf(write_file, "%s\t%lld\n", pair_probability[i].second.c_str(), pair_probability[i].first);
    }

    fclose(read_file);
    fclose(write_file);
}