# 線形回帰分析を用いたロケットの頂点時間の導出

## モデル1: $y=at^2+bt+c$
放物線運動をする物体の，高度と時間のデータ ${(t_1,y_1),...,(t_n,y_n)}$ がある．高度 $y$ は時間 $t$ の関数であり，放物線運動（二次関数）に従うとして次のような基底関数で近似できると仮定する．（ただし $a,b,c$ は定数）
$$ y = a t^2 + b t + c $$
　取得したn個の高度と時間のデータから最小二乗法により $a,b,c$ を推定する．まず評価関数 $J$ を次のように定義する．
$$ J = \frac{1}{2} \sum_{i=1}^{n} (a t_i^2 + b t_i +c - y_i)^2 $$
　評価関数 $J$ を極小値とするようなパラメータ $a,b,c$ は，$a,b,c$ について偏微分したものが0となるから．
$$
\begin{eqnarray*}
\frac{\partial J}{\partial a} &=&
\sum_{i=1}^n(a t_i^2 + bt_i + c - y_i )t_i^2 = 0 \\
\frac{\partial J}{\partial b} &=&
\sum_{i=1}^n(a t_i^2 + bt_i + c - y_i )t_i = 0 \\
\frac{\partial J}{\partial c} &=&
\sum_{i=1}^n(a t_i^2 + bt_i + c - y_i )= 0 \\
\end{eqnarray*}
$$
　これを行列形式にすれば，
$$
( \sum_{i=1}^n
\left[
    \begin{array}{rrr}
      t_i^4 & t_i^3 & t_i^2 \\
      t_i^3 & t_i^2 & t_i \\
      t_i^2 & t_i & 1
    \end{array}
 \right]
 )
\left[ \begin{array}{rrr}
      a \\  b \\    c
\end{array} \right]
 =
( \sum_{i=1}^n\left[
    \begin{array}{rrr}
      t_i^2 y_i  \\  t_i y_i \\ y_i
    \end{array}
 \right] )
$$
　となりこの連立方程式をとけば評価関数 $J$ について最適なパラメータ $a,b,c$ がわかる．  
　また放物線の式を変形すれば頂点高度とその時間が得られる．
$$
\begin{eqnarray*}
y
&=& a t^2 + b t + c \\
&=& a(t+\frac{b}{2a})^2 + c - \frac{b^2}{4a} \\
\end{eqnarray*}
$$

## モデル2: $y=-\frac{1}{2}gt^2+bt+c$
 $a=-\frac{1}{2}g$という制約を加えることで，データ数の少ないケースでも妥当な値が推定できるようにする．評価関数はモデル1と同じとすると，評価関数を極小とするためには $b,c$ で偏微分した値が0となるから，
 $$
 \begin{eqnarray*}
 \frac{\partial J}{\partial b} &=&
 \sum_{i=1}^n(a t_i^2 + bt_i + c - y_i )t_i = 0 \\
 \frac{\partial J}{\partial c} &=&
 \sum_{i=1}^n(a t_i^2 + bt_i + c - y_i )= 0 \\
 \end{eqnarray*}
 $$
 これを行列形式にすれば，
 $$
 \begin{eqnarray*}
 ( \sum_{i=1}^n
 \left[
     \begin{array}{rrr}
       t_i^2 & t_i \\
       t_i & 1
     \end{array}
  \right]
  )
 \left[ \begin{array}{rrr}
        b \\    c
 \end{array} \right]
  &=&
 ( \sum_{i=1}^n\left[
     \begin{array}{rrr}
        t_i y_i - at_i^3\\
        y_i - at_i^2
     \end{array}
  \right] )\\
  &=&
 ( \sum_{i=1}^n\left[
     \begin{array}{rrr}
        t_i y_i + \frac{1}{2}gt_i^3\\
        y_i + \frac{1}{2}gt_i^2
     \end{array}
  \right] )
  \end{eqnarray*}
 $$
 を得る．頂点高度となる時間は，
 $$
 t_{top} = \frac{b}{g}
 $$
 となる．
