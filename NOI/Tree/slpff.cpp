#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> g[N];
int n, m;
int fa[N], hson[N], top[N], sz[N], dep[N], dfn[N], dfc=0;

void add(int o, int l, int r, int nl, int nr, int k){
}

void pathadd(int x, int y, int k){
    while(top[x] != top[y]){
        if(dep[top[x]] > dep[top[y]]){
            add(1, 1, n, dfn[top[x]], dfn[x], k);
            x = fa[top[x]];
        } else {
            add(1, 1, n, dfn[top[y]], dfn[y], k);
            y = fa[top[y]];
        }
    }
    if(dep[x] > dep[y]) add(1, 1, n, dfn[y], dfn[x], k);
    else add(1, 1, n, dfn[x], dfn[y], k);
}

int main(){
}