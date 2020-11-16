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

int main(void)
{
    Replacement();
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
