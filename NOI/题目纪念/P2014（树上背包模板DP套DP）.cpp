// 一个点可以被选择，当且仅当它到根节点的路径上的所有点都被选择。
// Dp 套 Dp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 310;
lt n, m, dp[N][N];
vector<lt> g[N];

void dfs(lt u){
    for(int v : g[u]) dfs(v);
    //背包部分
    for(int v : g[u]){
        for(int j = m; j > 0; j--){
            for(int k = 0; k < j; k++){//这里是不同之处，子节点的重量需要规定
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
            }
        }
    }
}

int main(){
    scanf("%lld%lld", &n, &m);
    m++;
    lt u;
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld", &u, &dp[i][1]);//思考：为什么直接用dp[i][1]？
        g[u].push_back(i);
    }
    dfs(0);
    printf("%lld", dp[0][m]);
    return 0;
}