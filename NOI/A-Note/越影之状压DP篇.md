# 状压 DP

## 0. 前言

- 这里是**越影**的笔记典藏之**状压 DP**！—— $ysl$_$wf$

### 忠告

1. 如君是**初学者**，本篇的入门效果极佳？！？！

2. 如君是**复习者**，本片的例题祝您旅途愉快！

## 1. 引入

- 在进行前，请读者对于**位运算**有一定理解！~~毕竟这也是初赛内容！~~

### 1.1 定义

状压 DP 是动态规划的一种，通过将状态压缩为整数来达到优化转移的目的。

- 所谓状态压缩，本质就是对二进制**位运算**以及二进制 $01$ 的性质的一种应用！

- 当数据范围过大时，或者 DP 为是否存在性问题时，我们考虑转换成 $01$ 串的形式，$01$表示是否存在。如此，$01$ 串便转化成了一个二进制数！

### 1.2 技巧

- 主要讲解状压 DP 时的几个小技巧！

#### 1.2.1 枚举 a 的二进制（真）子集

设 $x$ 为 $a$ 的子集

初始化 `x = a`，下一个集合表示是 `x = (x-1) & s`，枚举到 `t == 0` 时可以结束。`(x-1)&a` 表示如果 `x` 不为 $0$（$x$ 非空），则 `x-1` 相当于将 `x` 最小的 $bit$ 去掉，加上所有位次比它低的 $bit$，由于又包含在 `a` 中，再将结果和 `a` 做与运算，从而排除掉在 `a` 之外的 $bit$；如果 `x` 为 $0$（$T$ 为空），假设 `x` 是带符号补码实现的整数，那么 `(x-1)&a` 结果为 `a`。

```cpp
for(lt x = a & (a-1); x; x = a & (x-1))
```

手动模拟即可理解本代码！

## 2. 例题解析

- 只有通过**例题**，在可以深刻了解状压 DP 的精妙之处！
- 本篇例题绝对具有典型性与权威性！（非常好！）

### 2.1 [【SCOI2005】互不侵犯](https://www.luogu.com.cn/problem/P1896)

- 本题如板子，热身。

#### 2.1.1 题目描述

在 $N \times N$ 的棋盘里面放 $K$ 个国王，使他们互不攻击，共有多少种摆放方案。国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各一个格子，共 $8$ 个格子。  

对于全部数据，$1 \le N \le 9$，$0 \le K \le N\times N$。

#### 2.1.2 分析

设 $f(i,j,l)$ 表示前 $i$ 行，第 $i$ 行的状态为 $j$，且棋盘上已经放置了 $l$ 个国王时的方案数。

对于上文 $j$ 的状态，我们就使用二进制 $sit(j)$ 表示国王的放置情况！$sit(j)$ 的某个二进制位为零表示对应位置不放国王，$1$ 则代表对应位置放置！

- 例如：$010011$，表示第 ${1,2,5}$ 位置放置了国王。（棋盘左边对应二进制低位）

我们用 $sta(j)$ 表示该状态的国王个数，即二进制数 $sit(j)$ 中 $1$ 的个数。

设当前行的状态为 $j$，上一行的状态为 $x$，可以得到下面的状态转移方程：

$$
f(i,j,l) = \sum_{}^{}f(i-1,x,l-sta(j))
$$

#### 2.1.3 Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
lt sta[2010], sit[2010], f[15][2010][110];
lt n, k, cnt;

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

void dfs(lt x, lt num, lt cur){
    if(cur >= n){
        sit[++cnt] = x;
        sta[cnt] = num;
        return ;
    }
    dfs(x, num, cur + 1);// cur位置不放国王
    dfs(x + (1 << cur), num + 1, cur + 2); // cur位置放国王，与它相邻的位置不能再放国王
}

bool judge(lt j, lt x){
    if(sit[j] & sit[x]) return false;
    if((sit[j] << 1) & sit[x]) return false;
    if(sit[j] & (sit[x] << 1)) return false;
    return true;
}

int main(){
    // freopen("6.in", "r", stdout);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> k;

    dfs(0, 0, 0);// 先预处理一行的所有合法状态
    for(int j = 1; j <= cnt; j++) f[1][j][sta[j]] = 1;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j <= cnt; j++){
            for(int x = 1; x <= cnt; x++){
                if(!judge(j, x)) continue;// 排除不合法转移
                for(int l = sta[j]; l <= k; l++){
                    f[i][j][l] += f[i-1][x][l-sta[j]];
                }
            }
        }
    }

    lt ans = 0;
    for(int i = 1; i <= cnt; i++){
        ans += f[n][i][k];
    }
    cout << ans << '\n';

    return 0;
}
```

### 2.2 [P3773【CTSC2017】吉夫特](https://www.luogu.com.cn/problem/P3773)

#### 2.2.1 简化题目

输入一个长度为  $n$  的数列  $a_1, a_2, \cdots , a_n$  问有多少个长度大于等于  $2$  的不上升的子序列满足：

 $$\prod _{i=2}^{k} \binom{a_{b_{i-1}}}{a_{b_i}} \bmod 2 = \binom{a_{b_1}}{a_{b_2}} \times \binom{a_{b_2}}{a_{b_3}} \times \cdots \binom{a_{b_{k-1}}}{a_{b_k}} \bmod 2 > 0$$ 

输出这个个数对  $1000000007$  取模的结果。

G 君看到题目后，为大家解释了一些基本概念。

我们选择任意多个整数  $b_i$  满足

 $$1 \leq b_1 < b_2 < \dots < b_{k-1} < b_k \leq n$$ 

我们称  $a_{b_1}, a_{b_2}, \cdots, a_{b_k} $  是  $a$  的一个子序列。

如果这个子序列同时还满足

 $$a_{b_1} \geq a_{b_2} \geq \cdots \geq a_{b_{k-1}}\geq a_{b_k}$$ 

我们称这个子序列是不上升的。

对于 $100\%$ 的测试点，$1\leq n\leq 211985$，$1\leq a_i\leq 233333$。所有的 $a_i$ 互不相同，也就是说不存在 $i, j$ 同时满足 $1\leq i < j\leq n$ 和 $a_i = a_j$。

#### 2.2.2 分析

本题很难想到和二进制挂钩，但是，如果是**卢卡斯定理**，就显而易见：

$$
C^{a_j}_{a_i} \equiv C^{a_j/2}_{a_i/2} \times C^{a_j \bmod 2}_{a_i \bmod 2} \pmod {2}
$$

其中 $C^{a_j \bmod 2}_{a_i \bmod 2}$ 有四种情况：$C^0_1$、$C^1_1$、$C^1_0$、$C^0_0$，其中只有 $C^1_0 = 0$。

然后处理 $C^{a_j/2}_{a_i/2}$。

我们发现：卢卡斯的递归过程就是一步步将 $a_i$ 和 $a_j$ 拆分，所以只要出现 $C^1_0$，$C^{a_j}_{a_i}$ 就等于 $0$。

可是题目中要求的是结果大于 $0$，所以，不存在二进制下的某一位，$a_i$ 为 $0$，而 $a_j$ 为 $1$，也就是说 $a_j$ 是二进制下 $a_i$ 的子集！

这样的话，让我们重新理解一下题目：

> 求子序列的个数，满足每一项在二进制下是前一项的子集。

所有的 $a_i$ 互不相同。所以，我们直接**在输入时**枚举每一位二进制的真子集，直接累加：（$set(i)$ 表示 $i$ 的二进制真子集！）

$$
f(i) = \sum_{}^{}f(set(i))
$$

切记：一定是**在输入时**，这样一定保证了顺序问题！

而且都是它的子集了，就不用考虑序列的单调性了。

复杂度就是枚举子集的 $O(3^{\log_2{max\{a_i\}}})$

#### 2.2.3 Code

```cpp
//O(3^M) => n = 2^M
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 3e5 + 10, mod = 1e9 + 7;
lt n, a[N], f[N], ans;

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    for(int i = n; i >= 1; i--){
        for(lt x = a[i] & (a[i]-1); x; x = a[i] & (x-1)){//枚举 a 的二进制（真）子集有一个常用的套路
            f[a[i]] += f[x];
        } 
        ans = (ans + f[a[i]]) % mod;
        f[a[i]]++;
    }
    printf("%lld", ans);
    return 0;
}
//上述代码中的 f[a[i]]++ 表示一个以 ai 组成的长度为 1 的子序列。
//因此，如果我们要把统计答案写进上述过程中，为了保证统计到的答案是长度至少为 2 的子序列，ans += f[a[i]] 必须发生在 f[a[i]]++ 之前。
```

### 2.3 [CF463D Gargari and Permutations](https://www.luogu.com.cn/problem/CF463D)

- 本题并不是一道状压的题目，但是作为 $2.4$ 的引子，还是相当不错的！
- 也是一到相当不错的 $DAG$ 优化 $DP$ 的题目！
- **重要理论**：每个 $DP$ 本质上都是 $DAG$！

#### 2.3.1 题目描述

给你 $k$ 个长度为 $n$ 的排列，求这些排列的最长公共子序列的长度。

#### 2.3.2 分析

我们把每个数出现位置记下来，若**在所有排列中**，$i$ 都在 $j$ 的左边，那么就可以进行 $i$ 到 $j$ 的转移，因此我们对所有**满足条件**的 $(i,j)$ 连一条有向边，易发现该图是一个 $DAG$，因此只需要跑一条最长路即可！

#### 2.3.3 Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
lt n, k, a[10][1010], pos[10][1010], ans;
vector<lt> g[1010];
lt topo[1010], L, deg[1010], dist[1010], p;//拓扑（跑最长路）
lt degt[1010];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> k;
    for(int i = 1; i <= k; i++){
        for(int j = 1; j <= n; j++){
            cin >> a[i][j]; pos[i][a[i][j]] = j;
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j) continue;
            bool flag = true;
            for(int p = 1; p <= k; p++){
                if(pos[p][i] >= pos[p][j]){
                    flag = false; break;
                }
            }
            if(flag){
                g[i].push_back(j);
                deg[j]++;//入度
            }
        }
    }

    for(int o = 1; o <= n; o++){
        L = 0;
        for(int p = 1; p <= n; p++){
            dist[p] = INT_MIN/2;
            degt[p] = deg[p];
            if(deg[p] == 0) topo[++L] = p;
        }
        dist[o] = 0; p = 1;
        while(L < n){
            for(lt v : g[topo[p]]){
                dist[v] = max(dist[v], dist[topo[p]] + 1);
                degt[v] --;
                if(degt[v] == 0) topo[++L] = v;
            }
            p++;
        }
        for(int i = 1; i <= n; i++){
            ans = max(ans, dist[i]);
        }
    }
    cout << ans + 1;

    return 0;
}
/*
若在所有排列中，i 都在 j 的左边，那么就可以进行 i 到 j 的转移。
因此我们对所有满足条件的 (i,j) 连一条有向边
*/
```

### 2.4 [CF1584F Strange LCS](https://www.luogu.com.cn/problem/CF1584F)

#### 2.4.1 题目描述

- 给定 $n$ 个字符串 $s_i$，每个字符串只包含大写和小写英文字母，且每个字母在每个字符串中最多出现两次。
- 求这些字符串的最长公共子序列。
- 多组数据。

#### 2.4.2 分析

与上题不同的，本来一种字符只出现一次，而这里却出现了两次，并且数据范围变大了。显然状压！

鉴于本题的属性让作者当时相当惊险，推荐 [xh39
](https://www.luogu.com.cn/article/c1s58pnf) 的题解！

### 2.5 [[ABC332E] Lucky bag](https://www.luogu.com.cn/problem/AT_abc332_e)

#### 2.5.1 题目翻译

你有 $n$ 个物品，第 $i$ 种物品重量为 $w_i$，将这些物品全部分到 $D$ 个盒子中，每个盒子的重量为其中物品重量之和，求盒子重量的方差最小值，答案误差在 $10^{-6}$ 之内。

允许存在盒子没有物品，此时其重量为 $0$ 。

$2\leq D\leq n\leq15$

#### 2.5.2 分析

本题也是相当的**好玩**~~~！

对方差的式子进行简化：

$$
V = \frac{1}{D} \sum_{i=1}^{D}(x_i - \overline x)^2
$$

其中：

$$
\sum_{i=1}^{D}(x_i - \overline x)^2
$$
$$
= \sum_{i=1}^{D}(x_i^2 - 2 x_i\overline x + \overline x^2)
$$
$$
= \sum_{i=1}^{D}x_i^2 + 2 \overline x \sum_{i=1}^{D}x_i + \sum_{i=1}^{D}\overline x^2
$$
$$
= \sum_{i=1}^{D}x_i^2 + 2 \overline x D \overline x + D \overline x^2
$$
$$
= \sum_{i=1}^{D}x_i^2 - D \overline x^2
$$
$$
= \sum_{i=1}^{D}x_i^2 + \frac{1}{D}(\sum_{i=1}^{D}x_i)^2
$$

则原式就等于：

$$
V = \frac{D \sum_{i=1}^{D}x_i^2 + (\sum_{i=1}^{D}x_i)^2}{D^2}
$$

显然：$\sum_{i=1}^{D}x_i = \sum_{i=1}^{N}W_i$。

所以，本题最后就变成了解决：

$$
\min \sum_{i=1}^{D}x_i^2
$$

设状态 $f(i,S)$ 表示包含物品集合 $S$ 的 $i$ 个袋子内重量平方和的最小值，转移方程为：

$$
f(i,S) = \min_{T\subseteq S} f(i-1,S-T) + f(1,T)（i \geq 2）
$$

而这里的集合 $S$ 便是 $01$ 串，表示是否包含对应第几位的物品！

复杂度是 $O(D3^N)$

- 还有一小点优化和其他做法请转移 [Terrible
](https://www.luogu.com.cn/article/t6ipmtes) 的超绝题解！

#### 2.5.3 Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
lt dp[16][1<<15], w[15];
lt n, d;

// void re_and_wr(){
//     ios::sync_with_stdio(false);
//     cin.tie(0), cout.tie(0);
// }

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    // re_and_wr();

    cin >> n >> d;
    lt sum = 0;
    for(int i = 1; i <= n; i++){
        cin >> w[i]; sum += w[i];
    }
    memset(dp, 0x3f3f3f3f, sizeof dp);

    for(int s = 0; s < 1<<n; s++){
        dp[1][s] = 0;
        for(int i = 1; i <= n; i++) if(s & (1<<(i-1))) dp[1][s] += w[i];
        dp[1][s] *= dp[1][s];
    }
    for(int i = 2; i <= d; i++){
        for(int s = 0; s < 1<<n; s++){
            lt t = s;
            do{
                dp[i][s] = min(dp[i][s], dp[i-1][s^t] + dp[1][t]);
            } while((t=(t-1)&s) != s);
            //for(int t=s;t;t=(t-1)&s)中 t 取遍所有非空子集
		    //此处是枚举所有子集，既不是非空子集也不是真子集
		    //当然，其实不必枚举所有子集
        }
    }
    printf("%.15Lf",(dp[d][(1<<n)-1] * d - sum*sum) * 1.0l / d / d);

    return 0;
}
```

### 2.6 [P2831 [NOIP2016 提高组] 愤怒的小鸟](https://www.luogu.com.cn/problem/P2831)

#### 2.6.1 简化题目

- 题目内容很简单，用一些抛物线来覆盖题目给出的一些点。

#### 2.6.2 分析

这个题也是相当的**好玩**！

设抛物线上的一点为 $x_i$，$y_i$，另一点 $x_j$，$y_j$。

列方程：

$$
y_i = -a x_i^2 + bx_i
$$
$$
y_j = -a x_j^2 + bx_j
$$

解方程：

$$
a = -\frac{y_ix_j - y_jx_i}{x_i^2x_j - x_ix_j^2}
$$
$$
a = \frac{y_ix_j^2 - y_jx_i^2}{x_ix_j^2 - x_i^2x_j}
$$

于是，我们只要知道抛物线上的两个点，我们必然能够求出抛物线方程 $a,b$ 的值！

```cpp
void equation(double &a, double &b, lt i, lt j){
    a = -(y[i]*x[j] - y[j]*x[i]) / 
         (x[j]*x[j]*x[i] - x[i]*x[i]*x[j]);

	b = (y[i]*x[j]*x[j] - y[j]*x[i]*x[i])/
        (x[i]*x[j]*x[j] - x[j]*x[i]*x[i]);
}
```

接下来，便是状压！$01$串表示每个位值的 $pig$ 存在与否！

我们穷举每一个状态，从 $0$ 到 $(1<<n)-1$

对于每一个状态，我们从他的第一位开始穷举，$i\&(1<<(j-1))$ 意思就是 $i$ 这个状态的第 $j$ 头 $pig$ 是否被打掉。于是 $start[i]$ 的意思就是 $i$ 这个状态内第一个 $0$ 的位置，也就是我们做 $dp$ 的起始位置：

```cpp
for(int i = 0; i < (1<<18); i++){
	int j = 1;
	for(; j <= 18 && i & (1<<(j-1)); j++);
	start[i] = j;
}
```

然后我们穷举每个点，然后看看这个点是否会在这一条抛物线中被打掉。而这个也可以被初始化！

若 $ax_i^2 + bx_i - y_i = 0$，这个点就是可以被打掉的，我们把它存在 $lines[i][j]$ 中，$lines[i][j]$ 表示进过 $i,j$ 两点的抛物线能够打掉的状态：

```cpp
for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
        if(fabs(x[i]-x[j]) < eps) continue;
        double a, b;
        equation(a, b, i, j);
        if(a > -eps) continue; // a > 0
        for(int k = 1; k <= n; k++){
            if(fabs(a*x[k]*x[k] + b*x[k] - y[k]) < eps)
                lines[i][j] |= (1<<(k-1));
        }
    }
}
```

如此，就有了如下的转移方程：

- $f[0] = 0$
- $f[S|(1<<(i-1))] = \min f[S] + 1$
- $f[S|lines[i][j]] = \min f[S] + 1$

```cpp
// O(T * n * 2^n)
for(int i = 0; i < (1<<n); i++){
    lt j = start[i];
    dp[i|(1<<(j-1))] = min(dp[i|(1<<(j-1))], dp[i]+1);
    for(int k = 1; k <= n; k++)
        dp[i|lines[j][k]] = min(dp[i|lines[j][k]], dp[i]+1);
}
```

#### 2.6.3 Code

```cpp
// O(T * n * 2^n)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 45;
const double eps = 1e-8;
lt T, n, m, lines[N][N], start[1<<19], dp[1<<19];
double x[N], y[N];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

void equation(double &a, double &b, lt i, lt j){
    a = -(y[i]*x[j] - y[j]*x[i]) / 
         (x[j]*x[j]*x[i] - x[i]*x[i]*x[j]);

	b = (y[i]*x[j]*x[j] - y[j]*x[i]*x[i])/
        (x[i]*x[j]*x[j] - x[j]*x[i]*x[i]);
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    for(int i = 0; i < (1<<18); i++){
		int j = 1;
		for(; j <= 18 && i & (1<<(j-1)); j++);
		start[i] = j;
	}

    cin >> T;

    while(T--){
        memset(lines, 0, sizeof lines);
		memset(dp, 0x3f, sizeof dp); dp[0] = 0;

        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(fabs(x[i]-x[j]) < eps) continue;
                double a, b;
                equation(a, b, i, j);
                if(a > -eps) continue; // a > 0
                for(int k = 1; k <= n; k++){
                    if(fabs(a*x[k]*x[k] + b*x[k] - y[k]) < eps)
                        lines[i][j] |= (1<<(k-1));
                }
            }
        }

        for(int i = 0; i < (1<<n); i++){
            lt j = start[i];
            dp[i|(1<<(j-1))] = min(dp[i|(1<<(j-1))], dp[i]+1);
            for(int k = 1; k <= n; k++)
                dp[i|lines[j][k]] = min(dp[i|lines[j][k]], dp[i]+1);
        }

        cout << dp[(1<<n)-1] << '\n';
    }

    return 0;
}
```

### 2.7 [P3959 [NOIP2017 提高组] 宝藏](https://www.luogu.com.cn/problem/P3959)

- 看到数据范围就知道大概是个状压了。考虑一下怎么设计状态。

#### 2.7.1 简化题目

- 找一棵生成树，使得代价和最小。

#### 2.7.2 分析

考虑在任意时刻，我们关心的只有我们已经把多少点加进生成树了，以及生成树的最大树高（也就是深度）是多少。

那么我们考虑设 $f_{S,i}$ 为当前生成树已经包含的集合 $S$ 中的点，并且树高是 $i$。

转移方程如下：

$$
f_{S,i} = \min\{f_{S_0,i-1} + pay\}
$$

其中，$S_0$ 是 $S$ 的子集，同时通过 $S_0$ 加边一定可以联结成 $S$。$pay$ 是这次加边的花费！

如何判断 $S_0$ 的合法性？我们可以求一个 $G_S$ 表示 $S$ 能拓展到的边的集合，预处理即可！

考虑 $pay$ 的计算（相当有意思！）

设 $ss = S \oplus S_0$，$\oplus$ 就是异或运算，则 $ss$ 表示在 $S$ 但不在 $S_0$ 中的元素！

这里 $pay$ 的计算显然是对于每个 $ss$ 中的元素取 $S_0$ 中的元素向它连一条最短的边求和后 ${} \times i$。

证明：

对于 $S$ 和 $S_0$，如果他们之间的边不是被 $S_0$中最大深度的点连接成的，那么一定存在另一个 $S_1$，包含另一种连边的情况使得 $S_1$ 包含除被最大深度点连接的点以外的所有点，那么通过 $S_1$ 转移的答案就是最小值，一定是正确的。所以不会漏解。

结束！

#### 2.7.3 Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt INF = 0x3f3f3f3f;
lt n, m, u, v, w, a, b, c, ans = INF;
lt frog[1<<15][15], gorf[1<<15], dis[15][15];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> m;
    memset(dis, 0x3f, sizeof dis);
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
    }
    memset(frog, 0x3f, sizeof frog);
    lt all = (1<<n) - 1;
    for(int i = 1; i <= all; i++){
        for(int j = 1; j <= n; j++){
            if(((1<<(j-1)) | i) == i){
                dis[j][j] = 0;
                for(int k = 1; k <= n; k++){
                    if(dis[j][k] != INF){
                        gorf[i] |= (1<<(k-1));
                    }
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) frog[1<<(i-1)][0] = 0;
    for(int i = 2; i <= all; i++){// i 就是 s
        for(int s0 = i-1; s0; s0 = (s0-1)&i){// 枚举 s 的子集
            if((gorf[s0]|i) == gorf[s0]){//一定可以从 s0 拓展 到 s
                lt sum = 0;
                lt ss = s0 ^ i;
                for(int k = 1; k <= n; k++){
                    if((1<<(k-1)) & ss){//枚举 ss 中的元素向 s0 连边
                        lt t = INF;
                        for(int h = 1; h <= n; h++){
                            if((1<<(h-1)) & s0){//枚举 s0 中的元素向 ss 连边
                                t = min(t, dis[h][k]);
                            }
                        }
                        sum += t;
                    }
                }
                for(int j = 1; j < n; j++){
                    if(frog[s0][j-1] != INF){
                        frog[i][j] = min(frog[i][j], frog[s0][j-1] + sum * j);
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; i++) ans = min(ans, frog[all][i]);
    cout << ans;

    return 0;
}
```

## 后记

### 修改记录

- $2024.9.16$ —— 第一次整理  
  基本无缺失。

### 参考资料

- oi-wiki

### 肺腑

- 愿君在**影越**这里受益匪浅。—— $ysl$_$wf$