#include<bits/stdc++.h>
using namespace std;

struct Edge{
    int u, v;
}e[500005];
vector<int> g[500005];
int dfn[100005], low[100005], cnt = 0;
int scc[100005], sccn;
stack<int> stk;
int w[100005];
int sccw[100005];
int deg[500005], topo[500005], L, dist[500005];

void Tarjan(int u){
    stk.push(u);
    dfn[u] = low[u] = ++cnt;
    for(int v : g[u]){
        if(dfn[v]){
            if(scc[v] == 0) low[u] = min(low[u], dfn[v]);
            continue;
        }
        Tarjan(v);
        low[u] = min(low[u], low[v]);
    }
    if(dfn[u] == low[u]){
        sccn++;
        while(1){
            if(stk.top() == u){
                scc[stk.top()] = sccn;
                stk.pop();
                break;
            }
            scc[stk.top()] = sccn;
            stk.pop();
        }
    }
}

int main(){
    int u, v, m, n;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> w[i];
    }
    for(int i = 1; i <= m; i++){
        cin >> u >> v;
        g[u].push_back(v);
        e[i] = (Edge){u, v};
    }
    for(int i = 1; i <= n; i++){
        if(dfn[i] == 0) Tarjan(i);
    }
    for(int i = 1; i <= n; i++){
        sccw[scc[i]] += w[i];
        g[i].clear();
    }
    for(int i = 1; i <= m; i++){
        if( scc[e[i].u] == scc[e[i].v] ) continue;
        g[scc[e[i].u]].push_back(scc[e[i].v]);
        deg[scc[e[i].v]]++;
    }
    //拓扑~
    for(int u = 1; u <= sccn; u++){
        dist[u] = INT_MIN/2;
        if(deg[u] == 0){
            topo[++L] = u;
            dist[u] = sccw[u];
        }
    }
//    cout<<" 入度 "<<deg[1]<<endl;
    int ans = 0;
    int p = 1;
    while(L < sccn){
        for(int e : g[topo[p]]){
            dist[e] = max(dist[e] , dist[topo[p]] + sccw[e]);
            deg[e]--;
            if(deg[e] == 0) topo[++L] = e;
        }
        p++;
    }
    for(int i = 1; i <= sccn; i++){
        ans = max(ans, dist[i]);
    }
    cout<<ans;
    return 0;
}