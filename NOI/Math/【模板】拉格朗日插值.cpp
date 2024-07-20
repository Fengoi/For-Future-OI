#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 2e3 + 10, mod = 998244353;
lt n, k, x[N], y[N];

lt qp(lt a, lt n, lt p){
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b;
}

lt lagrange(lt _x){
    lt ans = 0;
    for(int i = 1; i <= n; i++){
        lt s1 = 1, s2 = 1;
        for(int j = 1; j <= n; j++){
            if(i == j) continue;
            s1 = s1 * (_x - x[j]) % mod;
            s2 = s2 * (x[i] - x[j]) % mod;
        }
        ans = (ans + y[i] * s1 % mod * qp(s2, mod-2, mod) % mod ) % mod;
    }
    return (ans + mod) % mod;
}

int main(){
    scanf("%lld%lld", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%lld%lld", &x[i], &y[i]);
    }
    printf("%lld", lagrange(k));
    return 0;
}