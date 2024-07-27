#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 600;
lt n, m, dist[N][N], mp[N][N], ans;

int main(){
    scanf("%lld%lld", &n, &m);
    memset(dist, 0x1f, sizeof(dist));
    memset(mp, 0x1f, sizeof(mp));
    ans = dist[0][0];
    for(int i = 1; i <= n; i++) dist[i][i] = 0, mp[i][i] = 0;
    lt x, y, z;
    for(int i = 1; i <= m; i++){
        scanf("%lld%lld%lld", &x, &y, &z);
        dist[x][y] = min(dist[x][y], z);
        dist[y][x] = min(dist[y][x], z);
        mp[x][y] = min(mp[x][y], z);
        mp[y][x] = min(mp[y][x], z);
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(k != i && i != j && k != j)
                    ans = min(ans, dist[i][j] + mp[i][k] + mp[k][j]);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
    if(ans == dist[0][0]) printf("No solution.");
    else printf("%lld", ans);
    return 0;
}