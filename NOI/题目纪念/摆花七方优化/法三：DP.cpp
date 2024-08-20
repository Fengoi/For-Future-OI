//法三：DP
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 210, mod = 1e6 + 7;
lt n, m, a[N], f[N][N];

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

    f[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= m; j++){
            for(int k = 0; k <= min<lt>(j, a[i]); k++){
                f[i][j] = (f[i][j] + f[i-1][j-k]) % mod;
            }
        }
    }

    cout << f[n][m];
    return 0;
}