#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 2e6 + 10;
struct Edge{
	int u, v;
}e[N];
vector<pair<int,int>> g[N];
int dfn[N], low[N], cnt = 0;
stack<int> stk;

bool cut[N];//割边

lt dccn;
lt dcc[N];
vector<lt> dccs[N];

void Tarjan(int u, int fa){
	int son = 0;
	low[u] = dfn[u] = ++cnt;
	stk.push(u);
	for(auto p : g[u]){
        lt v = p.first;
		if(!dfn[v]){
			son++;
			Tarjan(v, p.second);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) cut[p.second] = true;//割边
		}
		else if(p.second != fa) low[u] = min(low[u], dfn[v]);
	}
}

void dfs(lt s, lt dccn){
    dcc[s] = dccn;
    for(auto p : g[s]){
        lt v = p.first;
        if(dcc[v] || cut[p.second]) continue;
        // 如果这个点属于其他分量或者这条边是割边，就停止搜索。
        dfs(v, dccn);
    }
}

int main(){
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d", &u, &v);
		g[u].push_back({v, i});
		g[v].push_back({u, i});
		e[i] = (Edge){u, v};
	}
	for(int i = 1; i <= n; i++){
		if(dfn[i] == 0){
			//stk.clear();只能手动清空
			while(!stk.empty()) stk.pop();
			Tarjan(i, 0);
		}
	} 
	int sum = 0;
	for(int i = 1; i <= n; i++){
		if(cut[i]) sum++;
	}
    for(int i = 1; i <= n; i++){
        if(!dcc[i]) dfs(i, ++dccn);
    }
    printf("%lld\n", dccn);
    for(int i = 1; i <= n; i++){
        dccs[dcc[i]].push_back(i);
    }
    for(int i = 1; i <= dccn; i++){
        printf("%d ", dccs[i].size());
        for(lt v : dccs[i]) printf("%lld ", v);
        printf("\n");
    }
	return 0;
}