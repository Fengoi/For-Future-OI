// 区间加、区间求和

#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 5e5 + 10;
lt n, m, a[N];
lt sum[N*4], lazy[N*4];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

void build(lt l, lt r, lt p){
    if(l == r){
        sum[p] = a[l];
        return ;
    }
    lt mid = l + ((r - l) >> 1);
    build(l, mid, p<<1), build(mid+1, r, p<<1|1);
    sum[p] = sum[p<<1] + sum[p<<1|1];
}

void push_up(lt p){
    sum[p] = sum[p<<1] + sum[p<<1|1];
}

void push_down(lt p, lt x, lt y){
    lt mid = x + ((y - x) >> 1);
    if(lazy[p]){
        sum[p<<1] += lazy[p] * (mid - x + 1);
        sum[p<<1|1] += lazy[p] * (y - mid);
        lazy[p<<1] += lazy[p], lazy[p<<1|1] += lazy[p];
        lazy[p] = 0;
    }
}

void update(lt l, lt r, lt s, lt x, lt y, lt p){
    if(l <= x && y <= r){
        sum[p] += (y-x+1) * s, lazy[p] += s;
        return ;
    }
    lt mid = x + ((y - x) >> 1);
    push_down(p, x, y);
    if(l <= mid) update(l, r, s, x, mid, p<<1);
    if(r > mid) update(l, r, s, mid + 1, y, p<<1|1);
    push_up(p);
}

lt get_sum(lt l ,lt r, lt x, lt y, lt p){
    if(l <= x && y <= r){
        return sum[p];
    }
    lt mid = x + ((y - x) >> 1);
    push_down(p, x, y);
    lt res = 0;
    if(l <= mid){
        res += get_sum(l, r, x, mid, p<<1);
    }
    if(r > mid) res += get_sum(l, r, mid + 1, y, p<<1|1);
    return res;
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    } build(1, n, 1);
    for(int i = 1; i <= m; i++){
        lt h, x, y, k;
        cin >> h >> x >> y;
        if(h == 1){
            cin >> k;
            update(x, y, k, 1, n, 1);
        }
        if(h == 2){
            cout << get_sum(x, y, 1, n, 1) << '\n';
        }
    }
    return 0;
}