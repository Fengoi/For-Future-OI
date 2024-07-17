/*
线性求解1 - n的逆元

inv[1] = 1;
for (int i = 2; i <= n; ++i) {
  inv[i] = (long long)(p - p / i) * inv[p % i] % p;
}

*/

#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 3e6 + 10;
lt n, p, invs[N];


lt qp(lt a, lt n, lt p){//快速幂
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b;
}

void invc(){//线性求解1 - n的逆元
    invs[1] = 1;
    for(int i = 2; i <= n; i++){
        invs[i] = (p - p / i) * invs[p % i] % p;
    }
}

int main(){
    scanf("%lld%lld", &n, &p);
    invc();
    for(int i = 1; i <= n; i++){
        printf("%lld\n", invs[i]);
    }
    return 0;
}