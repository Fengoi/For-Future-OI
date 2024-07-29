#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 10007, inf = 0x3f3f3f3f;

struct T{
    lt w, l, r;
}p[N];

struct Node{
    lt w, id;
    bool operator < (Node b) const{
        return w > b.w;
    }
};

lt t, n, m, ans;
bool vis[N];

priority_queue<Node> q;

void Del(lt x){
    p[x].l = p[p[x].l].l;
    p[x].r = p[p[x].r].r;
    p[p[x].l].r = x;
    p[p[x].r].l = x;
}

int main(){
    scanf("%lld", &t);
    while(t--){
        memset(p,0,sizeof(p));
		memset(vis,0,sizeof(vis));
		ans=0;
		while(!q.empty())
			q.pop();
        scanf("%lld%lld", &n, &m);
        lt last; scanf("%lld", &last);
        for(int i = 1; i < n; i++){
            lt in;
            scanf("%lld", &in);
            p[i].w = in-last; last = in;
            p[i].l = i-1;
		    p[i].r = i+1;
            q.push((Node){p[i].w, i});
        }
        p[0].w = p[n].w = inf;
        for(int i = 1; i <= m; i++){
            while(vis[q.top().id]) q.pop();
            Node now = q.top(); q.pop();
            ans += now.w;
            vis[p[now.id].l] = vis[p[now.id].r] = 1;
            p[now.id].w = p[p[now.id].l].w + p[p[now.id].r].w - p[now.id].w;
            q.push((Node){p[now.id].w, now.id});
            Del(now.id);
        }
        printf("%lld\n", ans);
    }
    ////////
    return 0;
}