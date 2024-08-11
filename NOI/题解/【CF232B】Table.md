# 【CF232B】Table（补充版）

## 前言

楼中的大佬们讲解的正解，但并未讲解 $cnt_i = \sum\limits_{j=1}^m [j \mod n = i]$（$i$、$j$这两列放的点的个数应该是相同的）的 $O(1)$ 的代码实现是怎么得来的，我的题解则给出了解释。   
（~~也可能是我太蒟蒻了~~）

## 分析问题

### 题意

有一个 $n\times m$ 的矩阵，求使得每个 $n\times n$ 的矩阵中都有正好 $k$ 个点的方案数，方案数对 $1000000007$（$1e9+7$）取模。  
$1\le n\le100,n\le m\le10^{18},0\le k\le n^2$

### 分析

通过题目的样例分析，我们可以得出：$m$ 很大，如果我们可以考虑求出前 $n$，从而直接得到 $m$ 列的方案数（因为我们知道前 $n$ 列一定要放 $k$ 个点，所以，只要知道前 $n$ 列的方案数，那么便知道全部的方案数）。

其实也就是找规律，得到：对于 $i$、$j$（$i\equiv j \pmod{n}$），这两列放的点的个数应该是一样的。

然后，我们便可以使用 DP 的思路，求出前 $n$ 列的方案，其中 $f[i][j]$ 表示前 i 列放 $j$ 个点的方案数。

DP 转移方程如下：
$$
f[i][j] = \sum\limits_{t=0}^{\min(j,n)} f[i-1][j-t] \times \dbinom{n}{t} ^ {p_i}
$$

其中，$p_i = \sum\limits_{j=1}^m [j \mod n = i]$（显然，相同列数的方案数相乘）

### 问题

1. $p_i = \sum\limits_{j=1}^m [j \mod n = i]$ 如何 $O(1)$ 计算（$i \in [1,n]$）？

- 暴力枚举的话就是在 $i$ 的基础上每回加 $n$（不超过 $m$）就是 $j$：

$$
\left\lfloor\dfrac{m-i}{j}\right\rfloor + 1
$$

- 高级的（~~笑死，我当时没懂~~）（常数更快一点）：

```cpp
(m-1)/n + (i <= (m-1)%n+1)
```

2. 组合数的计算
  
- 一种 $O(n^2)$ 预处理：

```cpp
for(int i = 1; i <= n; i++){
	C[i][0] = C[i][i] = 1;
	for(int j = 1; j < i; j++)
		C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
}
```

- 一种是 $O(\log n)$ 预处理（两种都可通过）:

```cpp
lt qp(lt a, lt n, lt p){
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b;
}

void cfac(){
    fac[0] = 1 % p;
    for(int i = 1; i <= 220; i++){
        fac[i] = fac[i-1] * i % p;
    }
}

void cifac(){
    ifac[220] = qp(fac[220], p-2, p);
    for(int i = 220 - 1; i >= 0; i--){
        ifac[i] = ifac[i+1] * (i+1) % p;
    }
}

lt C(lt n, lt k){
    if(n < k) return 0;
    return fac[n] * ifac[k] % p * ifac[n-k] % p;
}
```

## Code 
复杂度：$O(n^4)$

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 110, p = 1000000007;
lt n, m, k;
lt fac[N*N], ifac[N*N];
lt fp[N][N], f[N][N*N], cnt[N];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

lt qp(lt a, lt n, lt p){
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b;
}

void cfac(){
    fac[0] = 1 % p;
    for(int i = 1; i <= 220; i++){
        fac[i] = fac[i-1] * i % p;
    }
}

void cifac(){
    ifac[220] = qp(fac[220], p-2, p);
    for(int i = 220 - 1; i >= 0; i--){
        ifac[i] = ifac[i+1] * (i+1) % p;
    }
}

lt C(lt n, lt k){
    if(n < k) return 0;
    return fac[n] * ifac[k] % p * ifac[n-k] % p;
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cfac(); cifac();

    cin >> n >> m >> k;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= n; j++){
            fp[i][j] = qp(C(n, j), (m-i)/n+1, p);
        }
    }

    f[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= min(k, i*n); j++){
            for(int t = 0; t <= min((lt)j, n); t++){
                f[i][j] = (f[i][j] + f[i-1][j-t] * fp[i][t] % p) % p; 
            }
        }
    }

    cout << f[n][k];
    return 0;
}
```