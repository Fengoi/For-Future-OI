#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int n, m, c, fa[N], depth[N], sz[N]/*表示子孙的个数*/;
vector<int> g[N]/*读入*/, t[N]/*树*/;
int hson[N], top[N];

void dfs(int u){
    for(int v : g[u]){
        if(v==fa[u]) continue;
        fa[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
    }
}

int dfs1(int s){// hson 一开始也是 0 ，hson[0] 永远
    for(int v : t[s]) sz[s] += dfs1(v);
    hson[fa[s]] = sz[hson[fa[s]]] <= sz[s] ? s : hson[fa[s]];
    return sz[s] + 1;
}

void dfs2(int s){
    for(int v : t[s]){
        top[v] = v != hson[s] ? v : top[s];
        dfs2(v);
    }
}

int jump(int s){ return top[s] != c ? fa[top[s]] : c; }

int LCA(int u, int v){ 
    while(top[u] != top[v]){
        if(depth[top[u]] > depth[top[v]]) u = jump(u);
        else if(depth[top[u]] < depth[top[v]]) v = jump(v);
        else u = fa[u];
    }
    return depth[u] <= depth[v] ? u : v;
}

int main(){
    // freopen("P3379_1.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    scanf("%d%d%d", &n, &m, &c);

    //得出 fa 数组
    fa[c] = 0;
    for(int i = 1; i <= n-1; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(c);

    //创造一个新的树
    for(int i = 1; i <= n; i++)
        t[fa[i]].push_back(i);

    top[c] = c;
    dfs1(c);//求 sz 和 hson
    dfs2(c);//求 top

    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", LCA(x, y));
    }
    return 0;
}