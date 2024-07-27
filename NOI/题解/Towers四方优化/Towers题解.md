# $Towers$ 的四方进阶教学【保姆级】

## 前言

- [原题目传送门](https://www.luogu.com.cn/problem/CF229D)
- [加强版：P2300](https://www.luogu.com.cn/problem/P2300)
- [博客食用更佳！](https://www.cnblogs.com/ysl-fengem/articles/18327343)

## 题目描述

有$n(1<=n<=5000)$座塔排在一条直线上，从左到右每个塔的高度分别为$h_i(1<=h_i<=100000)$.

每次操作你可以选择一座塔（假设是第$i$座），用吊车把它吊起来，然后放到与它相邻的一座塔上（可以是第$i-1$座也可以是第$i+1$座），这样，新塔的高度为两座塔的和，完成操作后，塔的总数减少一座。

问最少需要多少次操作可以使得所有的塔从左到右形成一个**非递减**序列。

## 进阶做法一 $O(n^2)$：朴素 DP

### 分析

首先记 $s_i$ 为 $h_i$ 的前缀和。  
容易想到，令 $f_i$ 表示合并后到前 $i$ 个位置，所需的最少操作次数。  
由于合并后的高度满足递增性质，我们记录 $g_i$ 为最少操作次数合并后 $i$ 位置塔高；如果有多种最少操作次数的方案，我们希望 $g_i$ 尽可能小。
因此，我们便可以写出如下 DP

```cpp
for(int i = 1; i <= n; i++){
    for(int j = 0; j < i; j++){
        if(s[i] - s[j] < g[j]) continue;//不符合条件
        if(f[i] > f[j] + (i-j-1)){//方案数更少，全不更新
            f[i] = f[j] + (i-j-1);
            g[i] = s[i] - s[j];
        }
        else if(f[i] == f[j] + (i-j-1)){//我们希望 g[i] 尽可能小
            g[i] = min(g[i], s[i]-s[j]);
        }
    }
}
```

### 记得初始化！

```cpp
for(int i = 1; i <= n; i++){
    g[i] = INT_MAX; f[i] = INT_MAX;
}
```

## 进阶做法二 $O(n^2)$：常数优化

稍加思考，我们就能发现，每个 $f_i$ 都是从最后一个满足 $g_i \le s_i - s_j$ 的位置 $j$ 转移过来的，因此我们可以做一点常数优化：

```cpp
for(int i = 1; i <= n; i++){
        for(int j = i-1; j >= 0; j--){
            if(s[i]-s[j] >= g[j] && f[j] + (i-j-1) < f[i]){
                f[i] = f[j] + (i-j-1);
                g[i] = s[i] - s[j];
                break;//遇到就 break，因为显然
            }
        }
    }
```

## 进阶做法三 $O(nlogn)$

### 分析

注意到 $j$ 位置能够更新 $i$ 位置答案的前提是

$$
g_i \le s_i - s_j
$$

稍作变形得到：

$$
s_i \ge g_j + s_j
$$

另外，如果 $j$ 位置能够更新 $i$ 位置，那它就一定也能更新 $i+1$，$i+2$，···，$n$ 位置（*）。  
考虑正向 DP，即对于每一个位置 $j$，用 $f_j$ 来更新它能够更新的位置 $i$。  
首先，找到第一个满足 $s_i \ge g_i + s_j$ 的位置 $i$，这可以用 lower_bound 简单实现。然后令 `tag[i] = j`，其中 tag[i] 用来表示能够更新 $i$ 的最后一个位置。由于（*）所述，我们在使用 tag[i] 之前，还需要与 tag[i-1] 取 max。
于是，我们便得到一下 code：

### Code

```cpp
for(int j = 1; j <= n; j++){
    // 找到 j-1 能够更新的第一个位置 i
    lt i = lower_bound(s + 1, s + 1 + n, g[j-1] + s[j-1]) - s;
    // 给位置 i 打上标记
    tag[i] = j - 1;
    // 使用 tag 之前，要和前一个位置的 tag 取 max
    tag[j] = max(tag[j], tag[j-1]);
    // tag[j] 是最后一个能够更新 j 的位置，因此从 tag[j] 位置转移过来
    f[j] = f[tag[j]] + (j - tag[j] - 1);
    g[j] = s[j] - s[tag[j]];
    }
```

## 进阶做法四 $O(n)$

### 分析

观察可知，$j$ 满足：
$$
sum_i - sum_j \ge tag_j
$$
的最大数。  
$$
f_i = f_j + i - j - 1
$$
$$
tag_i = sum_i - sum_j
$$
显然 $tag_i$ 越小越好，这样找到一个就可以退出！
所以可以直接用单调队列优化！

### Code

```cpp
tail = 1;
for(int i = 1; i <= n; i++){
    while(head + 1 < tail && sum[i] >= sum[q[head+1]] + ta[q[head+1]])
        head++;
    f[i] = f[q[head]] + 1;
    tag[i] = sum[i] - sum[q[head]];
    while(head < tail && sum[q[tail-1]] + tag[q[tail-1]] > sum[i] + tag[i])
        tail--;
    q[tail++] = i;
}
```

## 四版完整代码

### Code1

```cpp
//O(n^2)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 50000 + 10;
lt n, a[N], s[N], f[N], g[N];
//s:前缀和；f：合并前 i 个位置的最少操作次数；g：最少操作次数后 i 位置的塔高

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        s[i] = s[i-1] + a[i];
    }
    for(int i = 1; i <= n; i++){
        g[i] = INT_MAX; f[i] = INT_MAX;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < i; j++){
            if(s[i] - s[j] < g[j]) continue;
            if(f[i] > f[j] + (i-j-1)){
                f[i] = f[j] + (i-j-1);
                g[i] = s[i] - s[j];
            }
            else if(f[i] == f[j] + (i-j-1)){
                g[i] = min(g[i], s[i]-s[j]);
            }
        }
    }
    printf("%lld", f[n]);
    return 0;
}
```

### Code2

```cpp
//O(n^2)
//稍加思考我们就能发现，每个 f[i] 都是从最后一个满足 g[j] ≤ s[i] − s[j] 的位置 j 转移过来的，因此我们可以做一点常数优化
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 50000 + 10;
lt n, a[N], s[N], f[N], g[N];
//s:前缀和；f：合并前 i 个位置的最少操作次数；g：最少操作次数后 i 位置的塔高

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        s[i] = s[i-1] + a[i];
    }
    for(int i = 1; i <= n; i++){
        f[i] = INT_MAX;
        g[i] = INT_MAX;
    }
    for(int i = 1; i <= n; i++){
        for(int j = i-1; j >= 0; j--){
            if(s[i]-s[j] >= g[j] && f[j] + (i-j-1) < f[i]){
                f[i] = f[j] + (i-j-1);
                g[i] = s[i] - s[j];
                break;
            }
        }
    }
    printf("%lld", f[n]);
    return 0;
}
```

### Code3

```cpp
//O(nlogn)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 50000 + 10;
lt n, a[N], s[N], f[N], g[N], tag[N];
//s:前缀和；f：合并前 i 个位置的最少操作次数；g：最少操作次数后 i 位置的塔高

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        s[i] = s[i-1] + a[i];
    }
    for(int j = 1; j <= n; j++){
        // 找到 j-1 能够更新的第一个位置 i
        lt i = lower_bound(s + 1, s + 1 + n, g[j-1] + s[j-1]) - s;
        // 给位置 i 打上标记
        tag[i] = j - 1;
        // 使用 tag 之前，要和前一个位置的 tag 取 max
        tag[j] = max(tag[j], tag[j-1]);/*哇~~~~~这一步真的很牛逼！*/
        // tag[j] 是最后一个能够更新 j 的位置，因此从 tag[j] 位置转移过来
        f[j] = f[tag[j]] + (j - tag[j] - 1);
        g[j] = s[j] - s[tag[j]];
    }
    printf("%lld", f[n]);
    return 0;
}
```

### Code4

```cpp
// O(n)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 2e5 + 10;
lt head, tail;
lt n, f[N], tag[N], sum[N], q[N];

int main(){
    scanf("%lld", &n);
    lt x;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &x);
        sum[i] = sum[i-1] + x;
    }
    tail = 1;
    for(int i = 1; i <= n; i++){
        while(head + 1 < tail && sum[i] >= sum[q[head+1]] + tag[q[head+1]])
            head++;
        f[i] = f[q[head]] + 1;
        tag[i] = sum[i] - sum[q[head]];
        while(head < tail && sum[q[tail-1]] + tag[q[tail-1]] > sum[i] + tag[i])
            tail--;
        q[tail++] = i;
    }
    printf("%lld", n-f[n]);
    return 0;
}
```

## 后记

- 愿你有所收获！