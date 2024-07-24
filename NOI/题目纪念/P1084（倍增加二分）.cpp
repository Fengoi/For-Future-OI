#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 5e4 + 10;
lt n, m, l, r, query[N];
lt ans, flag;

struct T{
    lt v, w;
};
vector<T> g[N];

lt fa[N], jump[N][25], dist[N][25], depth[N];
bool vis[N];

void dfs(lt u){
    if(!g[u].size()) return ;
    for(auto k : g[u]){
        lt v = k.v;
        vis[v] = 1;
        if(v == fa[u]) continue;
        fa[v] = u;
        dist[v][0] = k.w;
        depth[v] = depth[u] + 1;
        dfs(v);
    }
}

lt ctot = 0;
pair<lt, int> h[N];//闲置军队
bool sta[N];

bool need[N];
bool dfs1(lt x){
    bool pson = 0;
    if(sta[x]) return 1;
    for(auto k : g[x]){
        lt v = k.v;
        if(depth[v] < depth[x]){//转眼遇到爱
            continue;
        }
        pson = 1;
        if(!dfs1(v)) return 0;
    }
    if(!pson) return 0;
    return 1;
}

lt atot = 0;
lt tim[N];

lt btot = 0;
lt ned[N];

bool check(lt lim){
    //一会记得写初始化！！！
    memset(sta, 0, sizeof(sta));
    memset(tim, 0, sizeof(tim));
    memset(ned, 0, sizeof(ned));
    memset(h, 0, sizeof(h));
    memset(need, 0, sizeof(need));
    atot = 0, btot = 0, ctot = 0;
    ///////////////////////////////
    for(int i = 1; i <= m; i++){
        lt x = query[i], cnt = 0;
        for(int j = __lg(n) + 1; j >= 0; j--){
            if(jump[x][j] > 1 && cnt + dist[x][j] <= lim){
                cnt += dist[x][j];
                x = jump[x][j];
            }
        }
        if(jump[x][0] == 1 && cnt + dist[x][0] <= lim){
            h[++ctot] = make_pair(lim-cnt-dist[x][0], x);
        } else{
            sta[x] = 1;
        }
    }
    for(auto k : g[1]){
        if(!dfs1(k.v)) need[k.v] = 1;
    }
    sort(h+1, h+1+ctot);
    for(int i = 1; i <= ctot; i++){
        if(need[h[i].second] && h[i].first < dist[h[i].second][0]) need[h[i].second] = 0;
        else tim[++atot] = h[i].first;
    }

    for(auto k : g[1]){
        if(need[k.v]) ned[++btot] = dist[k.v][0];
    }

    if(atot < btot) return 0;
    sort(tim+1, tim+atot+1); sort(ned+1, ned+1+btot);
    
    lt i = 1, j = 1;//指针？！？！？！？！
    while(i <= btot && j <= atot){
        if(tim[j] >= ned[i]) i++, j++;
        else j++;
    }
    if(i > btot) return 1;
    return 0;
}

int main(){
    scanf("%lld", &n);
    for(int i = 1; i < n; i++){
        lt x, y, z;
        scanf("%lld%lld%lld", &x, &y, &z);
        g[x].push_back((T){y, z});
        g[y].push_back((T){x, z});
        r += z;
    }
    scanf("%lld", &m);
    for(int i = 1; i <= m; i++){
        scanf("%lld", &query[i]);
    }

    for(int i = 1; i <= n; i++) fa[i] = i;
    fa[1] = 1, vis[1] = 1;
    dfs(1);
    for(int i = 2; i <= n; i++){
		if(vis[i] == 0){
			fa[i] = i;
			vis[i] = 1;
			dfs(i);
		}
	}

    for(int i = 1; i <= n; i++){
        jump[i][0] = fa[i];
    }
    for(int k = 1; k <= __lg(n) + 1; k++){
        for(int i = 1; i <= n; i++){
            jump[i][k] = jump[jump[i][k-1]][k-1];
            dist[i][k] = dist[i][k-1] + dist[jump[i][k-1]][k-1];
        }
    }

    l = 1;
    while(l <= r){
        lt mid = (l+r) >> 1;
        if(check(mid)){
            r = mid - 1;
            ans = mid;
            flag = 1;//有解标记
        } else{
            l = mid + 1;
        }
    }

    if(!flag) printf("-1");
    else printf("%lld", ans);
    return 0;
}