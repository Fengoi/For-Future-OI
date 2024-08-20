//法四：滚动数组优化DP
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 210, mod = 1e6 + 7;
lt n, m, a[N], f[2][N];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    lt t = 0;
    f[0][0] = 1;
    for(int i = 1; i <= n; i++){
        t = 1 - t;
        for(int j = 0; j <= m; j++){
            f[t][j] = 0;
            for(int k = 0; k <= min<lt>(j, a[i]); k++){
                f[t][j] = (f[t][j] + f[1-t][j-k]) % mod;
            }
        }
    }

    cout << f[t][m];
    return 0;
}