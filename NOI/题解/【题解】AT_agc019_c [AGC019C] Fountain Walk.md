# 【题解】[AGC019C] Fountain Walk【保姆级】

## 前言
楼中的 [Ebola](https://www.luogu.com.cn/user/20158) 是我的老师，可以认为我的题解更加“平民化”，放心食用！

## 前置题目
[【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)

## 分析问题

### 简化题目

> 给定一个只有第一象限的直角坐标系，每两条横行纵列上，只能有一个“喷泉”，半径为 $10$，坐标系的单位长度为 $100$，给定两个点，求两者之间的最短距离。

### 假设

> 起点在左下，终点在右上。 

### Solve-1 走走看

也就是说我们会不断的往右上方走，遇到喷泉就绕 $1/4$ 周转弯，通过这样，我们可以把原来的转弯的 $20$ 优化成 5π。  
但如果绕 $1/2$ 圆周，你一定又会很容易的想到两点之间线段最短！  
因此，我们的策略便是：

> 我们希望在往右上走的过程中，尽可能遇到多的圆盘！

### Solve-2 怎么走

因为我们要一直往右上走，绝对不可以回头或者向下，也就是说，我们希望喷泉可以一直往右上，横纵坐标依次 **上升**！

但是，喷泉的位置是随机的！可是，喷泉仍然有规律可循：喷泉的横坐标从左往右可以依次 **遍历上升**！

我们可以想象这是某个数组的 **下标**，然后喷泉的纵坐标为数组对应的内容，那么解决问题的关键便是 **最长上升子序列**！

### Solve-3 优化呗

#### 保留

保留由起点和终点的横纵坐标包围而成的矩形！（这很好理解）

```cpp
scanf("%lld%lld%lld%lld", &ax, &ay, &bx, &by);
lt minx = min(ax, bx), maxx = max(ax, bx);
lt miny = min(ay, by), maxy = max(ay, by);
scanf("%lld", &n);
while(n--){
    scanf("%lld%lld", &a, &b);
    if(a >= minx && a <= maxx && b >= miny && b <= maxy)
        g.push_back({a, b});
}
```

#### 镜像翻转

上述的内容都基于：起点在左下，终点在右上。如果以此类推，那么你一定会崩溃！

这时，我们只需要通过镜像翻转的技巧！

1. 改变坐标的数据，让起点成为坐标原点！

2. 这时你会很容易的想到不断通过对称，将终点的新坐标变换到第一象限即可，也就是横纵坐标皆为正数！

```cpp
//以起点a为坐标原点(镜像翻转时我只需要让所有的点在第一象限（也就是说横纵坐标都为正数）。
void chg(){
    bx = bx - ax > 0 ? bx - ax : ax - bx;
    by = by - ay > 0 ? by - ay : ay - by;
    for(T v : g){
        v.x = v.x - ax > 0 ? v.x - ax : ax - v.x;
        v.y = v.y - ay > 0 ? v.y - ay : ay - v.y;
        as[++num].y = v.y, as[num].x = v.x;
    }
    ax = 0, ay = 0;
}
```

#### 离散化

实话说，不离散化，我真不道道友要如何完成 LIS，这是非常重要的操作，否则不管是数组大小还是求解，难度和内存上都是说不过去的！

```cpp
for(T v : g) as[++num].y = v.y, as[num].x = v.x;
```

#### 计算

~~找规律的东西不会有人要暴力模拟吧。~~ 其实只要找到要经过几个喷泉就可以！

到时这里有一个大问题：

> 若每一行都经过一个圆盘，或每一列都经过一个圆盘，则答案加上1/4圆周的长度！（应该好理解）

```cpp
z = LIS();//求最多经过几个
ans = (bx - ax + by - ay) * dl;
ans = ans - z * r * 2;
ans = ans + (double)z * (double)5 * pi;
if(z == by - ay + 1 || z == bx - ax + 1) 
    ans = ans + (double)5 * pi;
```

### 提醒

- 半径的大小为 $10$！！！
- 我们只需要 $11$ 位的精度！！！

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 2e5 + 10, dl = 100, r = 10;
const long double pi = 3.141592653589793;
lt ax, ay, bx, by, a, b, z;
long double ans;

lt n, num;
struct T{
    lt x, y;
};
vector<T> g;

T as[N];
lt d[N], L;

bool cmp(T a, T b){
    return a.x < b.x;
}

void scin(){//输入
    scanf("%lld%lld%lld%lld", &ax, &ay, &bx, &by);
    lt minx = min(ax, bx), maxx = max(ax, bx);
    lt miny = min(ay, by), maxy = max(ay, by);
    scanf("%lld", &n);
    while(n--){
        scanf("%lld%lld", &a, &b);
        if(a >= minx && a <= maxx && b >= miny && b <= maxy)
            g.push_back({a, b});
    }
}

void chg(){
    bx = bx - ax > 0 ? bx - ax : ax - bx;
    by = by - ay > 0 ? by - ay : ay - by;
    for(T v : g){
        v.x = v.x - ax > 0 ? v.x - ax : ax - v.x;
        v.y = v.y - ay > 0 ? v.y - ay : ay - v.y;
        as[++num].y = v.y, as[num].x = v.x;
    }
    ax = 0, ay = 0;
}

lt LIS(){
    sort(as+1, as+1+num, cmp);
    for(int i = 1; i <= num; i++){
        if(as[i].y >= d[L]){
            L++;
            d[L] = as[i].y;
        }
        else{
            int l = upper_bound(d+1, d+1+L, as[i].y) - d;
            d[l] = as[i].y;
        }
    }
    return L;
}

void count(){
    ans = (bx - ax + by - ay) * dl;
    ans = ans - z * r * 2;
    ans = ans + (double)z * (double)5 * pi;
    if(z == by - ay + 1 || z == bx - ax + 1) ans = ans + (double)5 * pi;
}

int main(){
    scin();//输入

    chg();
    //以起点a为坐标原点(镜像翻转时我只需要让所有的点在第一象限（也就是说横纵坐标都为正数）。

    z = LIS();//求最多经过几个

    count();//计算~

    printf("%.15Lf", ans);
    return 0;
}
//虽然答案要保留15位小数输出，但是实际只要11位的精度
```

## 后记

- 愿诸君如愿以偿。