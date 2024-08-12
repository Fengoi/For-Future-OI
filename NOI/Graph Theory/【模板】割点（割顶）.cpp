#include<bits/stdc++.h>
using namespace std;
const int N = 1e4*2+10;
struct Edge{
	int u, v;
}e[500005];
vector<int> g[N];
int dfn[N], low[N], cnt = 0;
int scc[N], sccn;
stack<int> stk;
bool cut[N];

void Tarjan(int u, int fa){
	int son = 0;//子树个数
	low[u] = dfn[u] = ++cnt;//打上时间戳标记
	stk.push(u);//u进入搜索树
	for(int v : g[u]){
		if(!dfn[v]){//树边
			son++;
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u]) cut[u] = true;
		}
		else if(v != fa) low[u] = min(low[u], dfn[v]);//返祖边
	}
	if(fa == 0 && son < 2) cut[u] = false;//是根节点，且子树小于2，不是割点
}

int main(){
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
		e[i] = (Edge){u, v};
	}
	for(int i = 1; i <= n; i++){
		if(dfn[i] == 0){
			//stk.clear();只能手动清空
			while(!stk.empty()){
				stk.pop();
			} 
			Tarjan(i, 0);
		}
	} 
	int sum = 0;
	for(int i = 1; i <= n; i++){
		if(cut[i]) sum++;
	}
	printf("%d\n", sum);
	for(int i = 1; i <= n; i++){
		if(cut[i]) printf("%d ", i);
	}
	return 0;
}