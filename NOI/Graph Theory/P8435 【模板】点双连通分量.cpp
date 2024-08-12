#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 2e6 + 10;
struct Edge{
	int u, v;
}e[N];
vector<int> g[N];
int dfn[N], low[N], cnt = 0;
int scc[N], sccn;
stack<int> stk;
bool cut[N];

lt bcc;
vector<lt> ans[N];

void Tarjan(int u, int fa){
	int son = 0;
	low[u] = dfn[u] = ++cnt;
	stk.push(u);
	for(int v : g[u]){
		if(!dfn[v]){
			son++;
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u]){
				bcc++;
                cut[u] = true;
                while(stk.top() != v){
                    ans[bcc].push_back(stk.top()); 
                    stk.pop();//将子树出栈
                }
				ans[bcc].push_back(stk.top()); stk.pop();
                ans[bcc].push_back(u);//把割点/树根也丢到点双里
            }
		}
		else if(v != fa) low[u] = min(low[u], dfn[v]);
	}
	if(fa == 0 && son < 2) cut[u] = false;
    if(fa == 0 && son == 0) ans[++bcc].push_back(u);//特判独立点
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
			while(!stk.empty()){ stk.pop(); }
			Tarjan(i, 0);
		}
	}
    printf("%lld\n", bcc);
    for(lt i = 1; i <= bcc; i++){
        printf("%d ", (int)ans[i].size());
		for(int j : ans[i]) printf("%lld ", j);
		printf("\n");
    }
	return 0;
}
/*
当这个公共点对于这个子图不是一个割点时，也就意味着这两个点双有着另外的边相连，而这些边相连的点同样也是两个点双的公共点，可以归到第一种情况里。

对于一个点双，它在 DFS 搜索树中 dfn 值最小的点一定是割点或者树根。

当这个点是割点时，它所属的点双必定不可以向它的父亲方向包括更多点，因为一旦回溯，它就成为了新的子图的一个割点，不是点双。所以它应该归到其中一个或多个子树里的点双中。

当这个点是树根时，它的 dfn 值是整棵树里最小的。它若有两个以上子树，那么它是一个割点；它若只有一个子树，它一定属于它的直系儿子的点双，因为包括它；它若是一个独立点，视作一个单独的点双。

换句话说，一个点双一定在这两类点的子树中。

我们用栈维护点，当遇到这两类点时，将子树内目前不属于其它点双的非割点或在子树中的割点归到一个新的点双。注意这个点可能还是与其它点双的公共点，所以不能将其出栈。
*/