# Numerical_Analysis
数値解析学の課題置き場

- [ガウス・ジョルダン法](https://github.com/knr2/Numerical_Analysis/blob/main/Gauss_Jordan.cpp)

行列を単位行列に変換して連立方程式を解く。　

- [ガウス・ザイデル法](https://github.com/knr2/Numerical_Analysis/blob/main/Gauss_Seidel.cpp)

連立方程式を変形して、x₁,x₂...xnについて解いた式にする。

x₁の式について、文字を適当に定めて、x₁を求めて更新をする。これをxnまで計算することを繰り返すと解が収束し求まる。

- [二分探索(式の作成部)](https://github.com/knr2/Numerical_Analysis/blob/main/two_line.cpp) [二分探索(メイン)](https://github.com/knr2/Numerical_Analysis/blob/main/math.cpp)

適当な探索幅を決め、端同士の値を代入して正負が変わっていたらその間にx軸との接点があるので、二分探索を行い、解を探す。

- [ニュートン法](https://github.com/knr2/Numerical_Analysis/blob/main/newton.c)

適当なx座標を定め、その座標における接線を引き、x座標を更新していき、収束したら解が求まる。

- [台形法・シンプソン法](https://github.com/knr2/Numerical_Analysis/blob/main/integration.cpp)

台形法は適当な2点の座標を使い、直線を引き作成された台形を作成し面積を求める。

シンプソン法は適当な3点の座標を使い、二次曲線を引き数値積分を行う。

- [平方採中法](https://github.com/knr2/Numerical_Analysis/blob/main/rand_square.cpp)

適当な数値を2乗し、中央の4桁を取り出すことで乱数を生成する。

- [モンテカルロ法](https://github.com/knr2/Numerical_Analysis/blob/main/report2/Monte_Carlo_Method.cpp)

正方形の中に多量の点をランダムに打ち、中心からの距離が半径以内であるものの割合を求めて、円の面積を求めてから、πを求める。

- [マルコフ](https://github.com/knr2/Numerical_Analysis/blob/main/report2/language.cpp)

各文字列の出現回数を求め、自動で分を作成。
