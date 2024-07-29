#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 3e5 + 10;

struct T{
    lt w, l, r;
}p[N];

struct Node{
    lt w, id;
    bool operator < (Node b) const{
        return w < b.w;
    }
};

lt n, m, ans;
bool vis[N];

priority_queue<Node> q;

void Del(lt x){
    p[x].l = p[p[x].l].l;
    p[x].r = p[p[x].r].r;
    p[p[x].l].r = x;
    p[p[x].r].l = x;
}

int main(){
    scanf("%lld%lld", &n, &m);
    if(n < m*2){
        printf("Error!");
        return 0;
    }
    for(int i = 1; i <= n; i++){
        scanf("%lld", &p[i].w);
        p[i].l = i-1;
		p[i].r = i+1;
        q.push((Node){p[i].w, i});
    }
    for(int i = 1; i <= m; i++){
        while(vis[q.top().id]) q.pop();
        Node now = q.top(); q.pop();
        if(now.w < 0) break;
        ans += now.w;
        vis[p[now.id].l] = vis[p[now.id].r] = 1;
        p[now.id].w = p[p[now.id].l].w + p[p[now.id].r].w - p[now.id].w;
        q.push((Node){p[now.id].w, now.id});
        Del(now.id);
    }
    printf("%lld", ans);
    return 0;
}