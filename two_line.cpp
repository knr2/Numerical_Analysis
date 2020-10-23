#include <algorithm> // next_permutation
#include <iomanip>   //setprecsion
#include <iostream>  // std::cout, std::endl, std::cin
#include <vector>    // std::vector
#include <string>    // std::string
#include <map>
#include <utility> // pair, make_pair
#include <fstream> //fopen, fclose
#include <cstdio>  // printf
#include <cstdlib>
#include <cmath> // sin, cos, tan

//関数定義
void setting(void);     //設定
void manual(void);      //説明文
void style_input(void); //式の入力
//ここまで

typedef long long ll;

int main(void)
{
    setting();
    manual();
    style_input();
    std::cout << "正常終了しました。"<< std::endl;
    return 0;
}

//設定
void setting(void)
{
    std::cout << std::fixed << std::setprecision(10); //少数は10桁まで表示するように設定
}

void manual(void)
{
    std::string read;
    std::cout << "使用方法を読む場合は1を入力し、読まない場合は0を入力してください。" << std::endl;
    getline(std::cin, read);
    if (read == "1" || read == "１")
    {
        std::cout << "*******************************************************" << std::endl;
        std::cout << "　使い方の説明" << std::endl;
        std::cout << "　方程式 → コマンド" << std::endl;
        std::cout << std::endl;
        std::cout << "　足し算　→　+2と打つ" << std::endl;
        std::cout << "　ex)　x + 1     → x + 1" << std::endl;
        std::cout << std::endl;
        std::cout << "　引き算　→　-2と打つ" << std::endl;
        std::cout << "　ex)　x - 1     → x - 1" << std::endl;
        std::cout << std::endl;
        std::cout << "　掛け算　→　*2と打つ" << std::endl;
        std::cout << "　ex)　x * 2     → x * 2" << std::endl;
        std::cout << std::endl;
        std::cout << "　割り算　→　/2と打つ" << std::endl;
        std::cout << "　ex)　x ÷ 2     → x / 2" << std::endl;
        std::cout << std::endl;
        std::cout << "　累乗　→　pow(x, 指数)と打つ" << std::endl;
        std::cout << "　ex)　x² + 1     → pow(x, 2) + 1" << std::endl;
        std::cout << "　ex)　√x + 1     → pow(x, 0.5) + 1" << std::endl;
        std::cout << "　ex)　2x² + 1    → 2 * pow(x, 2) + 1" << std::endl;
        std::cout << std::endl;
        std::cout << "　三角関数、逆三角関数　→　使いたい関数名(角度[rad])を打つ\n度数法の場合は角度[度] × PI / 180" << std::endl;
        std::cout << "　ex)　sin(x) + 1 でx[度]の場合       → sin(x * PI / 180) + 1" << std::endl;
        std::cout << "　ex)　arcsin(x) + 1 でx[度]の場合    → asin(x * PI / 180) + 1" << std::endl;
        std::cout << "　ex)　cos(x) + 1 でx[rad]の場合      → cos(x) + 1" << std::endl;
        std::cout << "　ex)　arccos(x) + 1 でx[rad]の場合   → acos(x) + 1" << std::endl;
        std::cout << "　ex)　tan(x) + 1 でx[rad]の場合      → tan(x) + 1" << std::endl;
        std::cout << "　ex)　arctan(x) + 1 でx[rad]の場合   → atan(x) + 1" << std::endl;
        std::cout << std::endl;
        std::cout << "　指数関数　→　exp(x)を打つ" << std::endl;
        std::cout << "　ex)　e^(x) + 1      → exp(x) + 1" << std::endl;
        std::cout << std::endl;
        std::cout << "　対数関数　→　log(x)を打つ" << std::endl;
        std::cout << "　ex)　log(x) + 1     → log(x) + 1" << std::endl;
        std::cout << std::endl;
        std::cout << "マニュアルは以上です。\nマニュアルにないものを使いたい場合はC言語の標準ライブラリのmath.hを参照してください。\n"
                  << std::endl;
        std::cout << "*******************************************************" << std::endl;
    }
    return;
}

void style_input(void)
{
    std::string flag = "keykeykey";
    std::string s;
    do
    {
        if (flag == "keykeykey")
            std::cout << "式を入力をしてください。" << std::endl;
        else if (flag == "0" || flag == "０")
            std::cout << "式を再入力をしてください。" << std::endl;
        else
            std::cout << "確認の際の入力が指定されたものではないです。\n式を再入力をしてください。" << std::endl;
        getline(std::cin, s);
        std::cout << "式が正しいかを確認をしてください。\n"
                  << s << "\n正しければ1を、正しくなければ0を入力してください。" << std::endl;
        getline(std::cin, flag);
    } while (flag != "1" && flag != "１");
    FILE *fp1;
    if ((fp1 = fopen("math.cpp", "w")) == NULL)
    {
        fprintf(stderr, "Can not find math.cpp\n");
        exit(1);
    }
    fprintf(fp1, "#include <algorithm> // next_permutation\n#include <iomanip>   //setprecsion\n#include <iostream>  // std::cout, std::endl, std::cin\n#include <vector>    // std::vector\n#include <string>    // std::string\n#include <map>       //map\n#include <utility>   // pair, make_pair\n#include <fstream>   //fopen, fclose\n#include <cstdio>    // printf\n#include <cstdlib>\n#include <cmath> // sin, cos, tan\n\ntypedef long long ll;\ntypedef long double ld;\n\n#define MAX 100\n\nconst ld PI = acos(-1.0);\n\n//変数定義\nll count = 0;                            //ある程度の回数処理を回すため\nld max = MAX, min = -1 * MAX;            //区間の橋の設定\nld search_range = 0.5;                   //探索する際の範囲幅\nstd::vector<std::pair<ld, ld>> interval; //±の変化した区間を記憶\n//ここまで\n\n//関数定義\nvoid setting(void);    //設定\nvoid zero_point(void); //零点を含む区間を探す\nld style(ld);          //式の実行\nvoid output(void);     //出力\n//ここまで\n\nint main(void)\n{\n    setting();\n    std::cout << \"零点の探索をする際の探索幅を決めてください。\\n1以上だと解が見つからないこともあるため、1未満の少数1桁を設定することが望ましいです。\" << std::endl;\n    std::cin >> search_range;\n    zero_point();\n    output();\n    return 0;\n}\n\n//設定\nvoid setting(void)\n{\n    std::cout << std::fixed << std::setprecision(10); //少数は10桁まで表示するように設定\n}\n\nvoid zero_point(void)\n{\n    ld left = min;\n    ld right = left + fabs(search_range);\n    std::map<ld, ll> memory;\n    while (right < MAX)\n    {\n        ld a, b;\n        a = style(left);\n        b = style(right);\n        if (a * b <= 0)\n        {\n            if (memory.count(left))\n                break;\n            interval.push_back(std::make_pair(left, right));\n            if (style(right) < 0.000000001)\n                memory[right] = 1;\n        }\n        left += fabs(search_range);\n        right += fabs(search_range);\n    }\n    return;\n}\n\n//式\nld style(ld x)\n{\n    return ");
    for (ll i = 0; i < s.size(); i++)
        fprintf(fp1, "%c", s[i]);
    fprintf(fp1, ";\n}\n\nvoid output(void)\n{\n    for (ll i = 0; i < interval.size(); i++)\n    {\n        ld center, left, right;\n        count = 0;\n        left = interval[i].first;\n        right = interval[i].second;\n        while (fabs(left - right) > 1e-10)\n        {\n            if (count == 100000)\n                break;\n            left = interval[i].first;\n            right = interval[i].second;\n            center = (left + right) / 2.;\n            if (style(center) == 0)\n                break;\n            if (style(left) == 0)\n            {\n                interval[i].second = interval[i].first;\n                break;\n            }\n            if (style(right) == 0)\n            {\n                interval[i].first = interval[i].second;\n                break;\n            }\n            if (style(left) * style(center) < 0)\n                interval[i].second = center;\n            if (style(left) * style(center) > 0)\n                interval[i].first = center;\n            count++;\n        }\n        if (fabs(interval[i].first - interval[i].second) > 1e-10)\n            std::cout << \"零点が区間内に複数個存在しています。\\n零点の探索幅を狭くすることで解が見つかる可能性があります。\" << std::endl;\n        else\n            std::cout << \" 解\" << i + 1 << \":\" << ((interval[i].first + interval[i].second) / 2.) << std::endl;\n    }\n    return;\n}\n");
    fclose(fp1);
    //math.cppを実行
    std::system("g++ math.cpp -o test;./test");
    return;
}