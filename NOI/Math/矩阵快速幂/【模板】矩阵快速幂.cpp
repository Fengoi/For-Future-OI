#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 110, mod = 1e9 + 7;
lt l, n;

struct T{
    lt g[N][N];
    //Remember！！！
    T(){ memset(g, 0, sizeof(g)); }
}s;

T operator * (const T &a, const T &b){
    T c;
    for(int k = 1; k <= l; k++){
        for(int i = 1; i <= l; i++){
            for(int j = 1; j <= l; j++){
                c.g[i][j] = (c.g[i][j] + a.g[i][k] * b.g[k][j] % mod) % mod;
            }
        }
    }
    return c;
}

T qp(T a, lt n){
    T ans;
    for(int i = 1; i <= l; i++){
        ans.g[i][i] = 1;
    }
    for(; n; n >>= 1, a = a * a)
        if(n&1) ans = ans * a;
    return ans;
}

int main(){
    // freopen("P3390_1.in", "r", stdin);
    // freopen("6.out", "w", stdout);
    scanf("%lld%lld", &l, &n);
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= l; j++){
            scanf("%lld", &s.g[i][j]);
        }
    }
    auto ans = qp(s, n);
    for(int i = 1; i <= l; printf("\n"), i++)
        for(int j = 1; j <= l; j++)
            printf("%lld ", ans.g[i][j] % mod);
    return 0;
}