// 区间加、区间乘、区间求和

#include <bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 500005;
lt n, m, Mod, a[N];
lt sum[N*4], lazy_add[N*4], lazy_mult[N*4];
// lazy_add[u]=k, lazy_mult[u]=p 表示：[l,r]整个区间的每个数都应该先*p再+k（注意：此时sum[u]是已经更新过了）

// push_up 的作用是更新sum[u]
void push_up(lt u){
    sum[u] = (sum[u<<1] + sum[u<<1|1]) % Mod;
}

// push_down 的作用是 把u的lazy标记清空，并且传递给左右儿子
void push_down(lt u, lt l, lt r){
    (lazy_mult[u<<1] *= lazy_mult[u]) %= Mod;
    (lazy_mult[u<<1|1] *= lazy_mult[u]) %= Mod;

    //   左儿子本应该 *p1 + k1
    //   现在，u的lazy标记要求整个区间 *p
    //   (左儿子就应该 *p1 + k1)  * p，所以左儿子的 lazy_add 也要 *p
    (lazy_add[u<<1] *= lazy_mult[u]) %= Mod;
    (lazy_add[u<<1|1] *= lazy_mult[u]) %= Mod;
    (sum[u<<1] *= lazy_mult[u]) %= Mod;
    (sum[u<<1|1] *= lazy_mult[u]) %= Mod;
    lazy_mult[u] = 1;

    (lazy_add[u<<1] += lazy_add[u]) %= Mod;
    (lazy_add[u<<1|1] += lazy_add[u]) %= Mod;
    lt mid = (l+r) / 2;
    (sum[u<<1] += lazy_add[u] * (mid-l+1)) %= Mod;
    (sum[u<<1|1] += lazy_add[u] * (r-mid)) %= Mod;
    lazy_add[u] = 0;
}

// 建立初始线段树，一次 build(1,1,n) 的复杂度是 O(n)
//        T(n) = 2*T(n/2) + O(1) = O(n)
// 不要和这个混淆：  T(n) = 2*T(n/2) + O(n) = O(n log n)
void build(lt u, lt l, lt r){
    lazy_add[u] = 0;
    lazy_mult[u] = 1;
    if(l==r){
        sum[u] = a[l];
        return;
    }
    lt mid = (l+r) / 2;
    build(u<<1, l, mid);
    build(u<<1|1, mid+1, r);
    push_up(u);
}

void multi(lt u, lt l, lt r, lt x, lt y, lt k){
    if(x==l && r==y){
        (sum[u] *= k) %= Mod;
        (lazy_mult[u] *= k) %= Mod;
        (lazy_add[u] *= k) %= Mod;
        return;
    }
    int mid = (l+r) / 2;
    push_down(u, l, r);
    // 分三种情况
    if(y <= mid)  // [x,y] 全在左儿子里
        multi(u<<1, l, mid, x, y, k);
    else if(x > mid)  // [x,y] 全在右儿子里
        multi(u<<1|1, mid+1, r, x, y, k);
    else{  // [x,y] 一部分在左儿子里、一部分在右儿子里
        multi(u<<1, l, mid, x, mid, k);
        multi(u<<1|1, mid+1, r, mid+1, y, k);
    }
    push_up(u);
}

// add(u,l,r,x,y,k)
// 做的是：把 [l,r] 和 [x,y] 交集的地方 +k
// u: 当前节点编号
// [l,r]: 当前节点所表示的线段
// [x,y]: 要 +k 的位置
void add(lt u, lt l, lt r, lt x, lt y, lt k){
    if(x==l && r==y){
        (sum[u] += k * (r-l+1)) %= Mod;
        (lazy_add[u] += k) %= Mod;
        return;
    }
    lt mid = (l+r) / 2;
    push_down(u, l, r);
    // 分三种情况
    if(y <= mid)  // [x,y] 全在左儿子里
        add(u<<1, l, mid, x, y, k);
    else if(x > mid)  // [x,y] 全在右儿子里
        add(u<<1|1, mid+1, r, x, y, k);
    else{  // [x,y] 一部分在左儿子里、一部分在右儿子里
        add(u<<1, l, mid, x, mid, k);
        add(u<<1|1, mid+1, r, mid+1, y, k);
    }
    push_up(u);
}

// get_sum(u,l,r,x,y)
// 求的是 [l,r] 和 [x,y] 交集的和
// u: 当前节点编号
// [l,r]: 当前节点所表示的线段
// [x,y]: 求和区间 
lt get_sum(lt u, lt l, lt r, lt x, lt y){
    // 如果当前节点完全落在求和区间内，直接返回sum
    if(x<=l && r<=y) return sum[u];
    // 在递归访问左右儿子之前，必须push down以保证左右儿子的sum是最新的
    push_down(u, l, r);
    int mid = (l+r) / 2;
    // 分三种情况
    lt res = 0;
    if(y <= mid)  // [x,y] 全在左儿子里
        res += get_sum(u<<1, l, mid, x, y);
    else if(x > mid)  // [x,y] 全在右儿子里
        res += get_sum(u<<1|1, mid+1, r, x, y);
    else{  // [x,y] 一部分在左儿子里、一部分在右儿子里
        res += get_sum(u<<1, l, mid, x, mid);
        res += get_sum(u<<1|1, mid+1, r, mid+1, y);
    }
    push_up(u);
    return res % Mod;
}

int main(){
    int n, m, op, x, y;
    lt k;
    scanf("%d%d%d", &n, &m, &Mod);
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);   // a+i 等价于 &a[i]
    build(1, 1, n);
    while(m--){
        scanf("%d%d%d", &op, &x, &y);
        if(op==1) scanf("%lld", &k), multi(1,1,n,x,y,k);
        else if(op==2) scanf("%lld", &k), add(1,1,n,x,y,k);
        else printf("%lld\n", get_sum(1,1,n,x,y));
    }
    return 0;
}