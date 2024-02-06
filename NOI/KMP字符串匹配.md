# KMP

给定字符串 $S,T$，问 $S$ 中所有出现 $T$ 的位置

字符串的下标都从 0 开始

$$
\pi(i)=\max \{k\;|\; T[0,...,k-1]=T[i-k+1,...,i],\; k=0,...,i\}
$$

特别规定：$\pi(0)=0$

```cpp
string T;
int k;
for(k = i; k >= 0; k--)
    if(T.substr(0,k)==T.substr(i-k+1,k))
        break;
pi[i] = k;
```

```
aa
pi[0] = 0
pi[1] = 1
```

```
anana
// anana = banana - b，表示剥皮后的香蕉
pi[0] = 0
pi[1] = 0
pi[2] = 1
pi[3] = 2
pi[4] = 3
```

## 用 $\pi$ 数组来做匹配

我们把 $T$（长$m$） 和 $S$（长$n$，$n>m$） 放到一起

```
A = T#S
```

假设我们知道了 $A$ 的 $\pi$ 数组

我们会知道，对于任意一个位置 $i$，一定会满足 $\pi(i)\leq m$

对于一个位置 $i$，如果 $\pi(i)=m$，说明 $T$ 从 $i-m+1$ 位置开始出现；反过来，如果 $T$ 从 $i-m+1$ 位置开始出现，那么一定 $\pi(i)=m$

我们只要找到 $\pi(i)=m$ 的位置，然后就知道答案了。

## 现在来求 $\pi$ 数组

最暴力的求法，$O(n^3)$：

```cpp
string A;
pi[0] = 0;
for(int i = 1; i < A.size(); i++){
    int k;
    for(k = i; k >= 0; k--)
        // substr 里面有一个循环
        if(A.substr(0,k)==A.substr(i-k+1,k))
            break;
    pi[i] = k;
}
```

我们观察到：$\pi(i+1)\leq \pi(i)+1$，为什么？

比如说 $\pi(i)=3$

```
0             i
***.........***O
```

如果 $\pi(i+1)=5$（或者更大），会怎么样？

```
0             i
****O......****O
```

但是这样的话，$\pi(i)$ 就应该等于 $4$（或者更大） 了，矛盾！

借助这个观察，我们可以优化代码：

```cpp
string A;
pi[0] = 0;
for(int i = 1; i < A.size(); i++){
    int k;
    for(k = pi[i-1]+1 /*这里优化！*/; k >= 0; k--)
        // substr 里面有一个循环
        if(A.substr(0,k)==A.substr(i-k+1,k))
            break;
    pi[i] = k;
}
```

这个复杂度是 $O(n^2)$，为什么？

我们看这个集合：

$$
\mathcal{P}(i)=\{k\;|\; T[0,...,k-1]=T[i-k+1,...,i],\; k=0,...,i\}
$$

（$\pi(i)=\max \mathcal{P}(i)$），比如说

```
anana
当 i=4 的时候，上面这个集合就等于：
{0, 1, 3}
```

考虑
```
0         i
***O....***O
```

其中 `***O` 的长度是 $\pi(i+1)$，

我们假设 `***` 的长度为 $x$，显然 $x\in \mathcal{P}(i)$

换句话说 $\pi(i+1)-1\in\mathcal{P}(i)$

那么我的 $k$ 循环可不可以只枚举 $\mathcal{P}(i)$ 里的数呢？（从大到小）

```cpp
string A;
pi[0] = 0;
for(int i = 0; i < A.size()-1; i++){
    int k;
    for(k = max(P(i)); k >= 0; k=P(i)里面比k小的那个数)
        if(A[k] == A[i+1])
            break;
    pi[i+1] = k+1;
}
```

这时候复杂度已经是 $O(n)$ 了，关键是 $k$ 循环怎么用代码写出来

我们先来看 $\mathcal{P}(i)$ 里面第二大的数是啥。我们假设 $\pi(i)=7$

```
0     6            i
*******......*******
```

如果 $5$ 是 $\mathcal{P}(i)$ 里面第二大的数，那么：

```
0     6            i
@@@@@**......**@@@@@
**@@@@@
```

那么：$\pi(6)=5$，也就是说 $\mathcal{P}(i)$ 里面第二大的数是 $\pi(6)$，也就是 $\pi(\pi(i)-1)$，

$\mathcal{P}(i)$ 里面第三大的数一定是 $\mathcal{P}(6)$ 里面第二大的数

其实继续循环下去也很简单

```cpp
string A;
pi[0] = 0;
for(int i = 0; i < A.size()-1; i++){
    int k;
    for(k = pi[i]; k >= 0; k=pi[k-1])
        if(A[k] == A[i+1])
            break;
    pi[i+1] = k+1;
}
```

## 模板题里的 border

其实 border 就是 $\mathcal{P}(i)$，最长 border 就是 $\pi(i)$

```
S = ABABABC
T = ABA
```

我们实际上是拼起来：

```
A = T#S
```

然后求 $A$ 的 $\pi$ 数组

但我们只要输出前 $|T|$ 个 $\pi$ 值

另外，输出位置的时候注意：如果 $\pi(i)=m$，我们就输出 $(i-m+1)-m$

## 动物园

我们看这个集合：

$$
\mathcal{P}(i)=\{k\;|\; T[0,...,k-1]=T[i-k+1,...,i],\; k=0,...,i\}
$$

显然：

$$
|\mathcal{P}(i)|=|\mathcal{P}(\pi(i)-1)|+1
$$

我们要求的是这个集合：

$$
\mathcal{Q}(i)=\{k\;|\;k\in \mathcal{P}(i) \;且\; k\leq i/2\}
$$

的大小。我们是怎么遍历 $\mathcal{P}(i)$ 里的元素？

```cpp
for(k=pi[i] ; k>=0 ; k=pi[k-1]){
    if(A[k] == A[i+1]){
        flag = true;
        break;
    }
    if( k==0 ) break;
}
```

```
i=10
P(i)={1,3,4,7,9,10}

0  3      i
***********
#.........#
###.....###
####...####

#..#

这里你可以知道 num[4-1] 一定等于 2
```