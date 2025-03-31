# 最大公约数问题

#### 题目：

scutsky给你一个长度为$n$的序列$a$，再给你$q$个询问，每个询问以$l,r$的形式给出，保证$l<r$，他想问你$max_{l\leqslant x<y\leqslant r}(y-x+1)^2\times GCD(x,y)$，其中$GCD(a,b)$表示区间$[a,b]$的所有数的最大公约数。

#### 输入格式：

第一行包含一个整数 $T$ ( $1\leqslant T \leqslant 10^4$  ),接下来是$T$个测试样例。


每个测试样例的第一行包含两个整数 $n$ 和 $q$ ( $2\leqslant n \leqslant 3\times 10^5,1\leqslant q\leqslant 3\times 10^5$ )。

每个测试样例的第二行包含$n$个整数$a_1, a_2, \dots, a_n$（$1 \leqslant a_i \leqslant 10^8$）。

接下来的 $q$ 行每行包含两个整数$l ,r$（$1 \leqslant l < r \leqslant n$）。

保证所有测试用例中$\sum n , \sum q \leqslant 300000$。

#### 输出格式：

对于每个测试样例，输出 $q$ 行，每行一个整数表示$max_{l\leqslant x<y\leqslant r}(y-x+1)^2\times GCD(x,y)$。

#### 样例：

输入1:

1
5 5
6 2 6 3 11
2 4
2 5
1 3
3 4
2 3

输出1：

12
16
18
12
8





