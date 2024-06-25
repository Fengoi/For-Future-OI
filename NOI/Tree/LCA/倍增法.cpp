#include<bits/stdc++.h>
using namespace std;
int fa[500005], depth[500005];
int jump[500005][20];
vector<int> g[500005];
void dfs(int u){
	/*
    for(int v : g[u]){
        if(v==fa[u]) continue;
        fa[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
    }
    */
    for(int i=0;i<g[u].size();i++){
    	if(g[u][i]==fa[u]) continue;
    	fa[g[u][i]]=u;
    	depth[g[u][i]]=depth[u]+1;
    	dfs(g[u][i]);
	}
}
int arbitaryJump(int u, int x){
    for(int k = 0; k <= 19; k++){
        if(x&(1<<k)) u = jump[u][k];
    }
    return u;
}

int LCA(int x, int y){
    if(depth[y] > depth[x]) swap(x,y);
    x = arbitaryJump(x, depth[x]-depth[y]);
    if(x==y){
//		cout<<x<<"ccc"<<endl;
		return x;
	}
//	cout<<x<<" "<<y<<endl;
    for(int k = 19; k >= 0; k--){
        if(jump[x][k] != jump[y][k]){
            x = jump[x][k];
            y = jump[y][k];
        }
    }
    return fa[x];
}

int main(){
	int n,m,s;
    cin >> n >> m >> s;
    fa[s] = 0;
    for(int i = 1; i <= n-1; i++){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(s);
    for(int i = 1; i <= n; i++){
    	jump[i][0] = fa[i];
//	   	cout<<jump[i][0]<<" ";
	}
    for(int k = 1; k <= 19; k++)
        for(int i = 1; i <= n; i++){
			jump[i][k] = jump[ jump[i][k-1] ][k-1];
//			cout<<jump[i][k]<<endl;
		}
    for(int i=1;i<=m;i++){
    	int a,b;
    	cin>>a>>b;
    	cout<<LCA(a,b)<<endl;
	}
}