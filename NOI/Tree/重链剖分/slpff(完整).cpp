#include <bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 1e5 + 10;
vector<int> g[N], t[N];
int n, l[N], m, r;
lt p;//模数 
lt fa[N], hson[N], top[N], sz[N], depth[N], dfn[N], dfc = 0;
lt sum[N*4], lazy[N*4];

//求 fa
void dfs(int u){
    for(int v : g[u]){
        if(v == fa[u]) continue;
        fa[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
    }
}

//求 sz 和 hson
int dfs1(int s){// hson 一开始也是 0 ，hson[0] 永远
    for(int v : t[s]) sz[s] += dfs1(v);
    hson[fa[s]] = sz[hson[fa[s]]] <= sz[s] ? s : hson[fa[s]];
    return sz[s] + 1;
}

//求 top
void dfs2(int s){
    for(int v : t[s]){
        top[v] = v != hson[s] ? v : top[s];
        dfs2(v);
    }
}

//求dfn
void qdfn(int r){
    if(!sz[r]) return ;//无儿子
    dfn[hson[r]] = ++dfc;
    qdfn(hson[r]);
    for(int v : t[r]){
        if(v != hson[r]){
            dfn[v] = ++dfc;
            qdfn(v);
        }
    }
    return ;
}

//子树加（区间加）
void add(int u, int l, int r, int x, int y, int k){
    if(l == x && r == y) { lazy[u] += k; lazy[u] %= p; return; }
    sum[u] += k * (y-x+1) % p;
    int mid = (l+r) / 2;
    if(y <= mid) 
        add(u<<1, l, mid, x, y, k);
    else if(x > mid)
        add(u<<1|1, mid+1, r, x, y, k);
    else{
        add(u<<1, l, mid, x, mid, k);
        add(u<<1|1, mid+1, r, mid+1, y, k);
    }
}

//子树求和（区间求和）
lt get_sum(int u, int l, int r, int x, int y){
    lt res = lazy[u] * (y-x+1) % p;
    if(x <= l && r <= y) return (sum[u] + res) % p; 
    int mid = (l+r) / 2;
    if(y <= mid)
        { res += get_sum(u<<1, l, mid, x, y); res %= p; }
    else if(x > mid)
        { res += get_sum(u<<1|1, mid+1, r, x, y); res %= p; }
    else{
        res += get_sum(u<<1, l, mid, x, mid); res %= p;
        res += get_sum(u<<1|1, mid+1, r, mid+1, y); res %= p;
    }
    return res;
}

//LCA加
void pathadd(int x, int y, int k){
    while(top[x] != top[y]){
        if(depth[top[x]] > depth[top[y]]){
            add(1, 1, n, dfn[top[x]], dfn[x], k);
            x = fa[top[x]];
        } else {
            add(1, 1, n, dfn[top[y]], dfn[y], k);
            y = fa[top[y]];
        }
    }
    if(depth[x] > depth[y]) add(1, 1, n, dfn[y], dfn[x], k);
    else add(1, 1, n, dfn[x], dfn[y], k);
}

//LCA求和
lt pathget(int x, int y){
    lt ans = 0;
    while(top[x] != top[y]){
        if(depth[top[x]] > depth[top[y]]){
            ans += get_sum(1, 1, n, dfn[top[x]], dfn[x]);
            ans %= p;
            x = fa[top[x]];
        } else {
            ans += get_sum(1, 1, n, dfn[top[y]], dfn[y]);
            ans %= p;
            y = fa[top[y]];
        }
    }
    if(depth[x] > depth[y]) { ans += get_sum(1, 1, n, dfn[y], dfn[x]); ans %= p; }
    else { ans += get_sum(1, 1, n, dfn[x], dfn[y]); ans %= p; }
    return ans;
}

int main(){
    scanf("%d%d%d%lld", &n, &m, &r, &p);
    for(int i = 1; i <= n; i++){
        scanf("%d", &l[i]);
    }

    fa[r] = 0;
    for(int i = 1; i < n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(r);

    //创造一个新的树
    for(int i = 1; i <= n; i++)
        t[fa[i]].push_back(i);
    
    top[r] = r;
    dfs1(r);//求 sz 和 hson
    dfs2(r);//求 top

    //求dfs序（重儿子优先）
    dfn[r] = ++dfc; qdfn(r);
    
    //先给每个点加上初始值！
    for(int i = 1; i <= n; i++){
        add(1, 1, n, dfn[i], dfn[i], l[i]);
    }

    //开始操作~
    int num, x, y, z;
    for(int i = 1; i <= m; i++){
        scanf("%d", &num);
        if(num == 1){
            scanf("%d%d%d", &x, &y, &z);
            pathadd(x, y, z);
        }
        if(num == 2){
            scanf("%d%d", &x, &y);
            printf("%lld\n", pathget(x, y));
        }
        if(num == 3){
            scanf("%d%d", &x, &z);
            add(1, 1, n, dfn[x], dfn[x] + sz[x], z);
        }
        if(num == 4){
            scanf("%d", &x);
            printf("%lld\n", get_sum(1, 1, n, dfn[x], dfn[x] + sz[x]));
        }
    }
}