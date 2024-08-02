// 线段树优化建图板子题
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 3e6 + 5, K = 5e5, inf = 0x3f3f3f3f3f3f3f3fll;
lt n, m, s, opt, x, y, z, l, r, w, a[N];
lt cnt, hd[N], to[N], nxt[N], val[N], d[N];
bool v[N];

priority_queue<pair<lt, lt>> q;

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

void add(lt x, lt y, lt z){
    to[++cnt] = y, nxt[cnt] = hd[x], hd[x] = cnt, val[cnt] = z;
}

void build(lt p, lt l, lt r){
    if(l == r){//a: 记录叶子节点的编号 
        a[l] = p;
        return ;
    }
    lt mid = (l+r)/2;
    add(p, p<<1, 0), add(p, p<<1|1, 0);//出树（从 p 向 p 的左右儿子连一条边权为 0 的边） 
    add((p<<1)+K, p+K, 0), add((p<<1|1)+K, p+K, 0);//入树（从 p 的左右儿子向 p 连一条边权为 0 的边） 
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r); 
}

void modify(lt p, lt l, lt r, lt x, lt y, lt v, lt w){
    if(l >= x && r <= y){//如果当前区间被涵盖
        if(opt == 2) add(v+K, p, w);//对于操作二，就从入树的叶子节点向出树中的对应区间连边。
        else add(p+K, v, w);//对于操作三，就从入树中的对应区间向出树中的叶子节点连边。
        return ;
    }
    lt mid = (l+r)/2;
    if(x <= mid) modify(p<<1, l, mid, x, y, v, w);
    if(y > mid) modify(p<<1|1, mid+1, r, x, y, v, w);
}

void Dijkstra(lt s){
    memset(d, 0x3f, sizeof d), d[s] = 0;
    q.push(make_pair(0, s));
    while(q.size()){
        lt x = q.top().second; q.pop();
        if(v[x]) continue;
        v[x] = 1;
        for(lt i = hd[x]; i; i = nxt[i]){
            lt y = to[i], z = val[i];
            if(d[y] > d[x] + z) d[y] = d[x] + z, q.push(make_pair(-d[y], y));
        }
    }
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> m >> s; build(1, 1, n);
    for(int i = 1; i <= n; i++){
        add(a[i], a[i]+K, 0), add(a[i]+K, a[i], 0);  //两棵线段树的叶子节点之间连边 
    }
    for(int i = 1; i <= m; i++){
        cin >> opt;
        if(opt == 1) cin >> x >> y >> z, add(a[x]+K, a[y], z);//对于操作一，就从入树的叶子节点向出树的叶子节点连边。
        else{
            cin >> x >> l >> r >> w;
            modify(1, 1, n, l, r, a[x], w);
        }
    }

    Dijkstra(a[s]+K);

    for(int i = 1; i <= n; i++){
        lt ans = d[a[i]] != inf ? d[a[i]] : -1;
        cout << ans << ' ';
    }
    return 0;
}