#include<bits/stdc++.h>
using namespace std;

typedef long long lt; 
const lt N = 2e5 + 10;
lt n, m, f[N];
lt sumst, cnt;
struct Edge{
    lt u, v, w, id, fl;
}e[N];

lt asr[N];

lt st[N][21], p[N];
bool cmp(Edge a, Edge b){
    return a.w < b.w;
}

///并查集（MST）
//查询
lt find(lt u) { return (f[u] == u) ? u : (f[u] = find(f[u])); }

void merge(lt u, lt v){//合并
    lt x = find(u), y = find(v);
    if(x == y) return ;
    f[x] = y;
}

bool judge(lt u, lt v){//判断
    lt x = find(u), y = find(v);
    return x == y;
}

///树链剖分
vector<int> g[N], t[N];
lt fa[N], hson[N], top[N], sz[N], depth[N], dfn[N], dfc = 0;
map<lt, map<lt, lt> > l;
lt h[N];

void dfs(lt u){//求fa
    for(int v : g[u]){
        if(v == fa[u]) continue;
        fa[v] = u; depth[v] = depth[u] + 1;
        dfs(v);
    }
}

//求 sz 和 hson
int dfs1(lt s){// hson 一开始也是 0 ，hson[0] 永远
    for(lt v : t[s]) sz[s] += dfs1(v);
    hson[fa[s]] = sz[hson[fa[s]]] <= sz[s] ? s : hson[fa[s]];
    return sz[s] + 1;
}

void dfs2(lt s){//求 top
    for(lt v : t[s]){
        top[v] = v != hson[s] ? v : top[s];
        dfs2(v);
    }
}

void qdfn(lt r){//求dfn
    if(!sz[r]) return ;//无儿子
    st[dfn[hson[r]] = ++dfc][0] = h[hson[r]];
    qdfn(hson[r]);
    for(lt v : t[r]){
        if(v != hson[r]){
            st[dfn[v] = ++dfc][0] = h[v];
            qdfn(v);
        }
    }
    return ;
}

///ST表

void work(){
    for(int k = 1; k <= 22; k++){
        for(int i = 1; i+(1<<k)-1 <= n; i++){
            st[i][k] = max(st[i][k-1], st[i+(1<<(k-1))][k-1]);
        }
    }
    return ;
}

lt askMax(lt l, lt r){
    lt k = __lg(r-l+1);
    return max(st[l][k], st[r-(1<<k)+1][k]);
}

///跑LCA

lt con(lt x, lt y){
    lt ans = INT_MIN;
    while(top[x] != top[y]){
        if(depth[top[x]] > depth[top[y]]){
            ans = max(ans, askMax(dfn[top[x]], dfn[x]));
            x = fa[top[x]];
        } else{
            ans = max(ans, askMax(dfn[top[y]], dfn[y]));
            y = fa[top[y]];
        }
    }
    if(depth[x] > depth[y]) ans = max(ans, askMax(dfn[y]+1, dfn[x]));
    else if (x!=y) ans = max(ans, askMax(dfn[x]+1, dfn[y]));
    return ans;
}

int main(){
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= m; i++){
        scanf("%lld%lld%lld", &e[i].u, &e[i].v, &e[i].w);
        e[i].id = i, e[i].fl = 0;
    }
    //MST
    sort(e+1, e+1+m, cmp);
    for(int i = 1; i <= n; i++) f[i] = i;
    for(int i = 1; i <= m; i++){
        if(judge(e[i].u, e[i].v)) continue;
        sumst += e[i].w; cnt++;
        merge(e[i].u, e[i].v); 

        g[e[i].u].push_back(e[i].v);
        g[e[i].v].push_back(e[i].u);
        l[e[i].u][e[i].v] = e[i].w;
        l[e[i].v][e[i].u] = e[i].w;

        e[i].fl = 1;//选进去了
        if(cnt == n-1) break;
    }
    //树链剖分
    lt r = 1;
    dfs(r);
    for(int i = 1; i <= n; i++){//创造最小生成树
        t[fa[i]].push_back(i);
        h[i] = l[fa[i]][i];
    }
    top[r] = r;
    dfs1(r);//求 sz 和 hson
    dfs2(r);//求 top
    dfn[r] = ++dfc; qdfn(r);//求dfs序（重儿子优先）

    //ST表
    work();

    //求解答案
    for(int i = 1; i <= m; i++){
        if(e[i].fl) asr[e[i].id] = sumst;
        else asr[e[i].id] = sumst + e[i].w - con(e[i].u, e[i].v);
    }
    for(int i = 1; i <= m; i++){
        printf("%lld\n", asr[i]);
    }
    return 0;
}