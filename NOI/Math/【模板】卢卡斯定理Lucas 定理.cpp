#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 1e5 + 10;
int T, n, m, p;
lt fac[N], ifac[N];

lt qp(lt a, lt n, lt p){//快速幂
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b; 
}

void cfac(){//求取模意义下的阶乘
    fac[0] = 1 % p ,fac[1] = 1 % p;
    for(int i = 2; i <= p; i++) 
        fac[i] = fac[i-1] * i % p;
}

void cifac(){//求取模意义下的逆元
    ifac[p - 1] = qp(fac[p - 1], p - 2, p);
    for(int i = p - 2; i >= 0; i--)
        ifac[i] = 1ll * ifac[i+1] * (i+1) % p;
}

lt C(lt n, lt k){//组合数
    if(n < k) return 0;
    return 1ll * fac[n] * ifac[k] % p * ifac[n-k] % p;
}

lt lucas(lt n, lt k){//Lucas定理
    if(k == 0) return 1;
    if(n < p) return C(n, k);
    else return 1ll * lucas(n/p, k/p) * C(n%p, k%p) % p;
}

int main(){
    scanf("%d", &T);
    while(T--){
        memset(fac, 0, sizeof fac);
        memset(ifac, 0, sizeof ifac);
        scanf("%d%d%d", &n, &m, &p);
        cfac();//求取模意义下的阶乘
        cifac();//求取模意义下的逆元
        printf("%lld\n", lucas(n+m, n));
    }
    return 0;
}
/*
调了一个晚上的模版题（当然开始写的时候也挺晚了）
明白了要注意这么几个事情！！！

1. lucas(lt n, lt k)中：if(k == 0) return 1;  

2. fac[0] = 1 ！！！！！别忘了初始化（后面每个测试点都有这一项。。。）

3.求ifac时，初始化p-1，for循环从p-2   -    0！！！！！

4. lucas(lt n, lt k)中：if(k == 0) return 1;
                        if(n < p) return C(n, k);
                        两句不可以写反。。。

（有个问题，为什么初始化时，ifac初始化到p-1就可以了，概念模糊...）
（愚蠢的喜讯：洛谷题目破200了。。。）
*/