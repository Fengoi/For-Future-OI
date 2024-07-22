#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 4e5 + 10;
lt n, m, q, a[N], chi[N], l[N], r[N];

lt dx[N], lazy[N];
lt vis[N];// 额外数组储存 是否 修改值

void build(lt l, lt r, lt p, lt s){
    // 对 [l, r] 区间建立线段树，当前根的编号为 p
    if(l == r){
        dx[p] = (a[l] >= s);
        lazy[p] = 0;
        vis[p] = 0;//清空标记！
        return ;
    }
    lt mid = l + ((r - l) >> 1);
    // 移位运算符的优先级小于加减法，所以加上括号
    // 如果写成 (l + r) >> 1，可能会超出 int 范围
    build(l, mid, p * 2, s), build(mid + 1, r, p * 2 + 1, s);
    // 递归对左右区间建树
    dx[p] = dx[p * 2] + dx[p * 2 + 1];
    vis[p] = 0; lazy[p] = 0;
}

void update(lt l, lt r, lt s, lt x, lt y, lt p){
    // [l, r] 为修改区间（询问区间）, s 为被修改的元素的变化量, [x, y] 为当前节点包含的区间（线段树二分区间）, p 为当前节点的编号
    if(l <= x && y <= r){
        dx[p] = (y-x+1) * s, lazy[p] = s;
        vis[p] = 1;
        return ;
    }
    lt mid = x + ((y - x) >> 1);
    if(vis[p]){
        dx[p * 2] = lazy[p] * (mid - x + 1);
        dx[p * 2 + 1] = lazy[p] * (y - mid);
        lazy[p * 2] = lazy[p * 2 + 1] = lazy[p];
        vis[p * 2] = vis[p * 2 + 1] = 1;
        vis[p] = 0;
    }
    if (l <= mid) update(l, r, s, x, mid, p * 2);
    if (r > mid) update(l, r, s, mid + 1, y, p * 2 + 1);
    dx[p] = dx[p * 2] + dx[p * 2 + 1];
}

lt get_sum(lt l, lt r, lt x, lt y, lt p){
    if (l <= x && y <= r) return dx[p];
    lt mid = x + ((y - x) >> 1);
    if(vis[p]){
        dx[p * 2] = lazy[p] * (mid - x + 1);
        dx[p * 2 + 1] = lazy[p] * (y - mid);
        lazy[p * 2] = lazy[p * 2 + 1] = lazy[p];
        vis[p * 2] = vis[p * 2 + 1] = 1;
        vis[p] = 0;
    }
    lt sum = 0;
    if (l <= mid) sum += get_sum(l, r, x, mid, p * 2);
    if (r > mid) sum += get_sum(l, r, mid + 1, y, p * 2 + 1);
    return sum;
}

bool check(lt mid){
    build(1, n, 1, mid);
    for(int i = 1; i <= m; i++){
        lt cnt = get_sum(l[i], r[i], 1, n, 1);
        if(chi[i] == 0){//升序
            if(r[i] - cnt + 1 <= r[i]) update(r[i] - cnt + 1, r[i], 1, 1, n, 1);
            if(l[i] <= r[i] - cnt) update(l[i], r[i] - cnt, 0, 1, n, 1);
        }
        else{
            if(l[i] <= l[i] + cnt - 1) update(l[i], l[i] + cnt - 1, 1, 1, n, 1);
            if(l[i] + cnt <= r[i]) update(l[i] + cnt, r[i], 0, 1, n, 1);
        }
    }
    return get_sum(q, q, 1, n, 1);
}

int main(){
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for(int i = 1; i <= m; i++) scanf("%lld%lld%lld", &chi[i], &l[i], &r[i]);
    scanf("%lld", &q);
    //二分
    lt l = 1, r = n;
    lt ans = 0;
    while(l <= r){
        lt mid = (l+r) >> 1;
        if(check(mid)){//比mid大
            ans = mid, l = mid+1;
        }
        else{
            r = mid - 1;
        }
    }
    printf("%lld", ans);
    return 0;
}