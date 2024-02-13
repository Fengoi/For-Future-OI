## ST表

给定一个序列，多次询问一段区间内的最大值

`maxx[i][k]`：表示 $[i,i+2^k)$ 中的最大值

```cpp
// a是输入的序列
for(int i = 1; i <= n; i++)
    maxx[i][0] = a[i];
for(int k = 1; k <= 19; k++)
    for(int i = 1; i <= n; i++)
        maxx[i][k] = max(maxx[i][k-1], maxx[i+(1<<(k-1))][k-1]);
```

$O(\log n)$ 查询 $[l,r]$ 中的最大值

```cpp
int askMax(int l, int r){
    int x = r-l+1; // 从l出发向右跳x步，找 [l,l+x) 中的最大值
    int ans = 0;
    for(int k = 0; k <= 19; k++){
        if(x&(1<<k)){
            ans = max(ans, maxx[l][k]);
            l = l + (1<<k);
        }
    }
    return ans;
}
```

如何优化到 $O(1)$ ?

```
[3,8]
[3,6] 的最大值 maxx[3][2]
[5,8] 的最大值 maxx[5][2]
所以 [3,8] 的最大值 max(maxx[3][2], maxx[5][2]);
```

对于一个一般的区间$[l,r]$，我们找到一个$k$，使得 $[l,l+2^k) \cup (r-2^k,r]=[l,r]$

$k$ 只与区间长度 $r-l+1$ 有关

```cpp
int askMax(int l, int r){
    int k = p[r-l+1]; // 表示r-l+1的二进制最高位对应的数
    return max(maxx[l][k], maxx[r-(1<<k)+1][k]);
}

// O(n log n) 预处理 p
for(int len = 1; len <= n; len++){
    for(int k = 19; k >= 0; k++)
        if( len&(1<<k) ){
            p[len] = 1<<k;
            break;
        }
}
```

1. 预处理`maxx`：$O(n\log n)$
2. 预处理`p`：$O(n\log n)$
3. $m$次询问：$O(m)$

总：$O(n\log n+m)$

- [ST表模板](https://www.luogu.com.cn/problem/P3865)