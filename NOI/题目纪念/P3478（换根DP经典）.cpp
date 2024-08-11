// 换根DP经典
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 1e6 + 10;
lt n, depth[N], size[N], f[N], ans, id;
vector<lt> g[N];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

void dfs1(lt s, lt fa){
    depth[s] = depth[fa] + 1; size[s] = 1;
    for(lt v : g[s]){
        if(v == fa) continue;
        dfs1(v, s);
        size[s] += size[v];
    }
}

void dfs2(lt s, lt fa){
    if(s != 1){
        f[s] = f[fa] + n - size[s] - size[s];
    }
    for(lt v : g[s]){
        if(v == fa) continue;
        dfs2(v, s);
    }
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n; lt x, y;
    for(int i = 1; i < n; i++){
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs1(1, 0);
    for(int i = 1; i <= n; i++){
        f[1] += depth[i];
    }

    dfs2(1, 0);

    for(int i = 1; i <= n; i++){
        if(ans < f[i]) ans = f[i], id = i;
    } cout << id << '\n';
    return 0;
}
/*
size[i]：i 所包含的子节点和自己

以 x 的 父亲是 y 为例，若将 x 变为根，不难发现：

1. x 变为根，x 的子节点和他自己的深度都要 -1，也就是付出 size[x] 的代价！
2. x 变为根，除 x 的子节点和他自己的深度都会 +1，因此就会得到 n-size[x] 的价值！

因此：
f[x] = f[y] + n - size[x] - size[x]；

这就是换根DP
*/