# 线段树Pushdown法

## 建树

### Code

```cpp
typedef long long lt;
const lt N = 1e4 + 10;
lt a[N], dx[N*4];

void build(lt l, lt r, lt p){
    // 对 [l, r] 区间建立线段树，当前根的编号为 p
    if(l == r){
        dx[p] = a[l];
        return ;
    }
    lt mid = l + ((r - l) >> 1);
    // 移位运算符的优先级小于加减法，所以加上括号
    // 如果写成 (l + r) >> 1，可能会超出 int 范围
    build(l, mid, p * 2), build(mid + 1, r, p * 2 + 1);
    // 递归对左右区间建树
    dx[p] = dx[p * 2] + dx[p * 2 + 1];
}
```

## 区间查询

### Code

```cpp
typedef long long lt;
const lt N = 1e4 + 10;
lt a[N], dx[N*4];

lt get_sum(lt l, lt r, lt x, lt y, lt p){
    // [l, r] 为查询区间（询问区间），[x, y]为当前节点包含的区间（线段树二分区间），p 为当前节点的编号
    if(l <= x && y <= r){
        return dx[p];
    }
    lt mid = x + ((y - x) >> 1), sum = 0;
    if(l <= mid) sum += get_sum(l, r, x, mid, p*2);
    // 如果左儿子代表的区间 [x, mid] 与询问区间有交集, 则递归查询左儿子
    if(r > mid) sum += get_sum(l, r, mid + 1, y, p*2+1);
    // 如果右儿子代表的区间 [mid + 1, y] 与询问区间有交集, 则递归查询右儿子
    return sum;
}
```

## 线段树的区间修改与懒惰标记

### 原理

概述：
> 懒惰标记，简单来说，就是通过延迟对节点信息的更改，从而减少可能不必要的操作次数。每次执行修改时，我们通过打标记的方法表明该节点对应的区间在某一次操作中被更改，但不更新该节点的子节点的信息。实质性的修改则在下一次访问带有标记的节点时才进行。

（详见 “ 线段树大总结.md ” ）

- [OI-WIKI](https://oi-wiki.org/ds/seg/#%E7%BA%BF%E6%AE%B5%E6%A0%91%E7%9A%84%E5%8C%BA%E9%97%B4%E4%BF%AE%E6%94%B9%E4%B8%8E%E6%87%92%E6%83%B0%E6%A0%87%E8%AE%B0)

### 区间加上某个值
```cpp
typedef long long lt;
const lt N = 1e4 + 10;
lt a[N], dx[N*4], lazy[N*4];

void push_up(lt p){
    dx[p] = dx[p * 2] + dx[p * 2 + 1];
}

void push_down(lt p, lt x, lt y){
    lt mid = x + ((y - x) >> 1);
    if(lazy[p]){
        // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
        dx[p * 2] += lazy[p] * (mid - x + 1);
        dx[p * 2 + 1] += lazy[p] * (y - mid);
        lazy[p * 2] += lazy[p], lazy[p * 2 + 1] += lazy[p]; // 将标记下传给子节点
        lazy[p] = 0;// 清空当前节点的标记
    }
}

void update(lt l, lt r, lt s, lt x, lt y, lt p){
    // [l, r] 为修改区间（询问区间）, s 为被修改的元素的变化量, [x, y] 为当前节点包含的区间（线段树二分区间）, p 为当前节点的编号
    if(l <= x && y <= r){
        dx[p] += (y-x+1) * s, lazy[p] += s;
        return ;
    }// 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
    lt mid = x + ((y - x) >> 1);
    push_down(p, x, y);
    if (l <= mid) update(l, r, s, x, mid, p * 2);
    if (r > mid) update(l, r, s, mid + 1, y, p * 2 + 1);
    push_up(p);
}
```

### 区间查询（区间求和）
```cpp
typedef long long lt;
const lt N = 1e4 + 10;
lt a[N], dx[N*4], lazy[N*4];

void push_down(lt p, lt x, lt y){
    lt mid = x + ((y - x) >> 1);
    if(lazy[p]){
        // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
        dx[p * 2] += lazy[p] * (mid - x + 1);
        dx[p * 2 + 1] += lazy[p] * (y - mid);
        lazy[p * 2] += lazy[p], lazy[p * 2 + 1] += lazy[p];// 将标记下传给子节点
        lazy[p] = 0;// 清空当前节点的标记
    }
}

lt get_sum(lt l, lt r, lt x, lt y, lt p){
    // [l, r] 为查询区间, [x, y] 为当前节点包含的区间（线段树二分区间）, p 为当前节点的编号
    if (l <= x && y <= r) return dx[p];
    // 当前区间为询问区间的子集时直接返回当前区间的和
    lt mid = x + ((y - x) >> 1);
    push_down(p, x, y);
    lt sum = 0;
    if (l <= mid) sum += get_sum(l, r, x, mid, p * 2);
    if (r > mid) sum += get_sum(l, r, mid + 1, y, p * 2 + 1);
    return sum;
}
```

### 区间修改
如果你是要实现区间修改为某一个值而不是加上某一个值的话

```cpp
typedef long long lt;
const lt N = 1e4 + 10;
lt a[N], dx[N*4], lazy[N*4];
lt vis[N*4];// 额外数组储存 是否 修改值

void push_up(lt p){
    dx[p] = dx[p * 2] + dx[p * 2 + 1];
}

void push_down(lt p, lt x, lt y){
    lt mid = x + ((y - x) >> 1);
    if(vis[p]){
        dx[p * 2] = lazy[p] * (mid - x + 1);
        dx[p * 2 + 1] = lazy[p] * (y - mid);
        lazy[p * 2] = lazy[p * 2 + 1] = lazy[p];
        vis[p * 2] = vis[p * 2 + 1] = 1;
        vis[p] = 0;
    }
}

void update(lt l, lt r, lt s, lt x, lt y, lt p){
    // [l, r] 为修改区间, s 为被修改的元素的变化量, [x, y] 为当前节点包含的区间（线段树二分区间）, p 为当前节点的编号
    if(l <= x && y <= r){
        dx[p] = (y-x+1) * s, lazy[p] = s;
        vis[p] = 1;
        return ;
    }
    lt mid = x + ((y - x) >> 1);
    push_down(p, x, y);
    if (l <= mid) update(l, r, s, x, mid, p * 2);
    if (r > mid) update(l, r, s, mid + 1, y, p * 2 + 1);
    push_up(p);
}

lt get_sum(lt l, lt r, lt x, lt y, lt p){
    if (l <= x && y <= r) return dx[p];
    lt mid = x + ((y - x) >> 1);
    push_down(p, x, y);
    lt sum = 0;
    if (l <= mid) sum += get_sum(l, r, x, mid, p * 2);
    if (r > mid) sum += get_sum(l, r, mid + 1, y, p * 2 + 1);
    return sum;
}
```