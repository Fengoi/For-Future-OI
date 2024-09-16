#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt INF = 0x3f3f3f3f;
lt n, m, u, v, w, a, b, c, ans = INF;
lt frog[1<<15][15], gorf[1<<15], dis[15][15];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> m;
    memset(dis, 0x3f, sizeof dis);
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
    }
    memset(frog, 0x3f, sizeof frog);
    lt all = (1<<n) - 1;
    for(int i = 1; i <= all; i++){
        for(int j = 1; j <= n; j++){
            if(((1<<(j-1)) | i) == i){
                dis[j][j] = 0;
                for(int k = 1; k <= n; k++){
                    if(dis[j][k] != INF){
                        gorf[i] |= (1<<(k-1));
                    }
                }
            }
        }
    }

    for(int i = 1; i <= n; i++) frog[1<<(i-1)][0] = 0;
    for(int i = 2; i <= all; i++){// i 就是 s
        for(int s0 = i-1; s0; s0 = (s0-1)&i){// 枚举 s 的子集
            if((gorf[s0]|i) == gorf[s0]){//一定可以从 s0 拓展 到 s
                lt sum = 0;
                lt ss = s0 ^ i;
                for(int k = 1; k <= n; k++){
                    if((1<<(k-1)) & ss){//枚举 ss 中的元素向 s0 连边
                        lt t = INF;
                        for(int h = 1; h <= n; h++){
                            if((1<<(h-1)) & s0){//枚举 s0 中的元素向 ss 连边
                                t = min(t, dis[h][k]);
                            }
                        }
                        sum += t;
                    }
                }
                for(int j = 1; j < n; j++){
                    if(frog[s0][j-1] != INF){
                        frog[i][j] = min(frog[i][j], frog[s0][j-1] + sum * j);
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; i++) ans = min(ans, frog[all][i]);
    cout << ans;

    return 0;
}