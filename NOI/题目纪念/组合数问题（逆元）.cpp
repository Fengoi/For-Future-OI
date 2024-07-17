#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 5e6 + 10;
lt T, n, m, p;
lt fac[N], ifac[N], ans;

lt qp(lt a, lt n, lt p){//快速幂
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b;
}

void cfac(){//求取模意义下的阶乘
    fac[0] = 1 % p ,fac[1] = 1 % p;
    for(int i = 2; i <= n; i++)
        fac[i] = fac[i-1] * i % p;
}

void cifac(){//求取模意义下的逆元
    ifac[n] = qp(fac[n], p - 2, p);
    for(int i = n - 1; i >= 0; i--)
        ifac[i] = 1ll * ifac[i+1] * (i+1) % p;
}

lt C(lt n, lt k){//组合数
    if(n < k) return 0;
    return 1ll * fac[n] * ifac[k] % p * ifac[n-k] % p;
}

int main(){
    scanf("%d%d", &T, &n);
    p = 998244353;
    memset(fac, 0, sizeof fac);
    memset(ifac, 0, sizeof ifac);
    cfac();//求取模意义下的阶乘
    cifac();//求取模意义下的逆元
    ans = 0;
    while(T--){
        scanf("%d%d", &n, &m);
        ans = ans ^ C(n, m);
    }
    printf("%d", ans);
    return 0;
}