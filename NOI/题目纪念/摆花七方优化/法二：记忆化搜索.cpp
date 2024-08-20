//法二：记忆化搜索
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 210, mod = 1e6 + 7;
lt n, m, a[N], rmb[N][N];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

lt dfs(lt x, lt k){
    if(k == m) return 1;
    if(k > m) return 0;
    if(x > n) return 0;
    if(rmb[x][k]) return rmb[x][k];

    lt ans = 0;
    for(int i = 0; i <= a[x]; i++) ans = (ans +  dfs(x+1, k+i)) % mod;

    rmb[x][k] = ans;

    return ans;
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    cout << dfs(1, 0);
    return 0;
}