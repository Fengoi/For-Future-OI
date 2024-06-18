/*
dfs序：
6 11 12 5 1 2 10 3 8 7 9

dfn[i] : i 在dfs序里是第几个



low[i]: i 及其子孙节点指出去的非树边中，所指向的最小的那个dfs序
low[3] = dfn[10];
$$纠正：low[u] 表示u及其⼦孙节点的返祖边所指向的最⼩dfs序$$

dfn[u]=low[u]说明u一定是一个强连通分量的开头

什么样的点在u的强连通分量里？

u的强连通分量里面不会有u的祖先

1. u的强连通分量只有u和他的一些子孙
2. 如果v在u的强连通分量里，那么low[v]=dfn[u]

如果v既是u的子孙，又满足low[v]=dfn[u]，那么v一定在u的强连通分量里，吗？（对）
*/


#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int u, v;
} e[500005];

vector<int> g[100005];
int dfn[100005], low[100005], cnt=0;
int scc[100005], sccn;
// scc[i]表示i在第几个强连通分量 (i所在的大点的编号)
stack<int> stk;
// push: 扔进去
// pop: 弹出顶上一个
// top: 问顶上那个是啥

int w[100005];
int sccw[100005];

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
    // dfn[u]=low[u] 表示 u 这个点是强连通分量的第一个点
    // 如何标注强连通分量里的所有点？
    if(dfn[u] == low[u]){
        sccn++;
        while( 1 ){
            if(stk.top()==u){
                scc[stk.top()] = sccn;
                stk.pop();
                break;
            }
            scc[stk.top()] = sccn;
            //cout<<sccn<<endl;
            stk.pop();
        }
    }
}


int main(){
    int u, v, m, n;
    // 读取了w

    for(int i = 1; i <= m; i++){
        cin >> u >> v;
        g[u].push_back(v);
        e[i]=(Edge){u,v};
    }

    for(int i = 1; i <= n; i++)
        if(dfn[i]==0) Tarjan(i);
    // 缩点完成之后，图里只有1,2,...,sccn这么些大点
    // 每个大点的权值是它所包含的小点权值之和

    for(int i = 1; i <= n; i++){
        sccw[scc[i]] += w[i];
        g[i].clear();
    }
    for(int i = 1; i <= m; i++){
        // 你知道小点之间的连边 e[i].u -> e[i].v
        // 对应于大点之间的连边 scc[e[i].u] -> scc[e[i].v]
        if(scc[e[i].u] == scc[e[i].v]) continue;
        g[scc[e[i].u]].push_back(scc[e[i].v]);
    }

    // 拓扑

    return 0;
}