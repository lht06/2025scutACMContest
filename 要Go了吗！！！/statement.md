# 要Go了吗！！！

#### 题目：

众所周知，scutsky很喜欢下围棋。但是byyq不会下围棋，所以这天，scutsky想了一种新的下棋方式和byyq对弈。scutksy拿来了一堆棋子，上面分别刻着$\{a,...,LIM\}$，且每种棋子都有无限个。$LIM$的值由题目给出，且保证$'a'\leqslant LIM \leqslant 'z'$。例如当$LIM$为$'d'$时，双方能用的棋子上面刻着$\{a,b,c,d\}$。scutsky又拿来一个一行的棋盘，他们从棋盘的最左端开始下棋，可以认为棋盘是无限向右延伸的。现在他们开始下棋：

### 比赛规则：

1. **准备环节**：
	scutsky和byyq会分别准备$n$，$m$个字符串为他们自己所用。当然这些字符串里面的字符必须要在某种棋子中出现过。
2. **游戏规则**：
	游戏开始时，棋盘是空的，双方从棋盘的最左端开始交替下棋，scutsky先手。每次下棋时，当前棋手选择一种棋子放到当前棋盘最后一个棋子的右边。每当有一个选手落子后，对当前棋盘进行检查。若棋盘中有连续的棋子满足，它们上面的字符构成的字符串在scutsky准备的字符串中出现时，则游戏结束，scutsky获胜。然后，若棋盘中有连续的棋子满足，它们上面的字符构成的字符串在byyq准备的字符串中出现时，则游戏结束，byyq获胜。若scutsky和byyq在完美策略下，即使自己不能获胜，也不会使得对方获胜，则双方平手。
   

scutsky和byyq都十分聪明，他们都会以最优策略下棋。现在给定scutsky和byyq分别选定的$n$个和$m$个字符串，请你判断比赛的结果。

#### 输入格式：

第一行包含一个整数 $T$($1 \leqslant T \leqslant 10^4$  ),接下来是$T$个测试样例。

对于每个测试样例，第一行输入两个整数$n$，$m$和一个字符$LIM$，（$1\leqslant n,m \leqslant 5 \times 10^5$，$'a'\leqslant LIM \leqslant 'z'$）

接下来的 $n$ 行每行包含一个字符串$S$，为scutsky选定的字符串。

接下来的 $m$ 行每行包含一个字符串$S$，为byyq选定的字符串。

保证所有测试用例中双方所选择的字符串总长的和$\leqslant 10^6$。

#### 输出格式：

对于每个测试样例，输入一行一个字符串表示结果。

若scutsky获胜，则输出"scutsky"(不包含双引号）。

若byyq获胜，则输出"byyq"(不包含双引号）。

若双方平局，则输出"draw"(不包含双引号）。    

#### 样例：

输入1:

2
5 6 b
bb
aaa
abb
aabbb
ba
aaaaba
bb
abb
a
baba
baaaba
1 1 d
cbc
ad

输出1：

scutsky
draw

