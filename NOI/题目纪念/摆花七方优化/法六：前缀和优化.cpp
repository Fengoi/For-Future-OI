//法六：前缀和优化
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 210, mod = 1e6 + 7;
lt n, m, a[N], f[N], sum[N];

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

    f[0] = 1;
    for(int i = 0; i <= m; i++) sum[i] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = m; j >= 1; j--){
            lt t = j - min<lt>(a[i], j) - 1;
            if(t < 0) f[j] = (f[j] + sum[j-1]) % mod;
            else f[j] =  (f[j] + sum[j-1] - sum[t] + mod) % mod;
        }
        for(int j = 1; j <= m; j++) sum[j] = (sum[j-1] + f[j])%mod;
    }

    cout << f[m];
    return 0;
}