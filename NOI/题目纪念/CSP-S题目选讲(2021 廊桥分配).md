# CSP-S 2021 廊桥分配

### 简化的问题

如果所有航班都是国内的，我们知道有$n$个廊桥，能不能【快速】判断有多少飞机能够停靠在廊桥？

1. 把所有航班按【来的时间】从小到大排序

```cpp
int cnt = 0;
for(int i = 1; i <= n; i++)
    P.push(-i);
for(int i = 1 to m){
    // T 表示正在停靠的飞机的集合
    // P 表示空闲的廊桥编号集合
    // stp[i] 表示 飞机i 停靠的廊桥编号
    int st = i 的 到达时刻。
    while(T.top() 的离开时刻 在 st 之前){
        P.push(stp[T.top().id]);
        T.pop();
    }
    if(!P.empty()){
        T.push( 飞机i );
        stp[i] = -P.top();
        P.pop();
        cnt++;
    } else {
        stp[i] = -1;
    }
}
```

你希望 T 是一个可以自动把离开时刻最小的飞机放在 top 中的优先队列

```cpp
struct Plane{
    int id;
    int arrive, depart;
    bool operator < (const Plane &b) const{
        // 想想为什么这里要反过来定义
        return depart > b.depart;
    }
};
priority_queue<Plane> T;
```

假如一开始 $n=5$，我们运行了一遍上面的程序。现在我们把国内航班的廊桥缩少到 $3$ 个，哪些飞机停不了了？

答：如果 `stp[i] > 3`，那 i 就停不了了

```cpp
// n1: 国内廊桥数量
// m1: 国内飞机数量
// n2: 国际廊桥数量
// m2: 国际飞机数量
// stp[i]: 国内的i号飞机停靠的廊桥
// stpi[i]: 国际的i号飞机停靠的廊桥
// cnt[c]: 数组stp的桶，表示stp=c的国内飞机有几个
// sum[c] = cnt[1] + cnt[2] + ... + cnt[c]
// cnti 与 sumi 表示国际的
sum[1] = cnt[1];
for(int c = 2; c <= n; c++)
    sum[c] = sum[c-1] + cnt[c];

for(int n1 = 0; n1 <= n; n1++){
    int n2 = n-n1;
    int ans = 0;

    // for(int i = 1; i <= m1; i++)
    //     if(stp[i]!=-1 && stp[i]<=n1) ans++;
    
    // for(int i = 1; i <= m2; i++)
    //     if(stpi[i]!=-1 && stpi[i]<=n2) ans++;
    
    ans = sum[n1] + sumi[n2];
    
    // 对ans取max
}
```