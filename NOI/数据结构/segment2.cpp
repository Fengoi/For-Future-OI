// 区间加、区间求和

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 500005;
int n, m;
LL sum[N*4], lazy[N*4];
// lazy[u]=k 表示：[l,r]整个区间都应该 +k，但是这整个区间的 sum 都没有加

// add(u,l,r,x,y,k)
// 做的是：把 [l,r] 和 [x,y] 交集的地方 +k
// u: 当前节点编号
// [l,r]: 当前节点所表示的线段
// [x,y]: 要 +k 的位置
void add(int u, int l, int r, int x, int y, LL k){
    if(x==l && r==y){
        lazy[u] += k;
        return;
    }
    sum[u] += k * (y-x+1);
    int mid = (l+r) / 2;
    // 分三种情况
    if(y <= mid)  // [x,y] 全在左儿子里
        add(u<<1, l, mid, x, y, k);
    else if(x > mid)  // [x,y] 全在右儿子里
        add(u<<1|1, mid+1, r, x, y, k);
    else{  // [x,y] 一部分在左儿子里、一部分在右儿子里
        add(u<<1, l, mid, x, mid, k);
        add(u<<1|1, mid+1, r, mid+1, y, k);
    }
}

// get_sum(u,l,r,x,y)
// 求的是 [l,r] 和 [x,y] 交集的和
// u: 当前节点编号
// [l,r]: 当前节点所表示的线段
// [x,y]: 求和区间
LL get_sum(int u, int l, int r, int x, int y){
    // 如果当前节点完全落在求和区间内，直接返回sum
    LL res = lazy[u] * (y-x+1);
    if(x<=l && r<=y) return sum[u] + res;
    int mid = (l+r) / 2;
    // 分三种情况
    if(y <= mid)  // [x,y] 全在左儿子里
        res += get_sum(u<<1, l, mid, x, y);
    else if(x > mid)  // [x,y] 全在右儿子里
        res += get_sum(u<<1|1, mid+1, r, x, y);
    else{  // [x,y] 一部分在左儿子里、一部分在右儿子里
        res += get_sum(u<<1, l, mid, x, mid);
        res += get_sum(u<<1|1, mid+1, r, mid+1, y);
    }
    return res;
}

int main(){
    int n, m, op, x, y;
    LL k;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &x);
        add(1, 1, n, i, i, x);
    }
    while(m--){
        scanf("%d%d%d", &op, &x, &y);
        if(op==1) scanf("%lld", &k), add(1,1,n,x,y,k);
        else printf("%lld\n", get_sum(1,1,n,x,y));
    }
    return 0;
}