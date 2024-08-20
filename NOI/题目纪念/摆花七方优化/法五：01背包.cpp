//法五：01背包
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 210, mod = 1e6 + 7;
lt n, m, a[N], f[N];

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
    for(int i = 1; i <= n; i++){
        for(int j = m; j >= 0; j--){
            for(int k = 1; k <= min<lt>(j, a[i]); k++){
                f[j] = (f[j] + f[j-k]) % mod;
            }
        }
    }

    cout << f[m];
    return 0;
}