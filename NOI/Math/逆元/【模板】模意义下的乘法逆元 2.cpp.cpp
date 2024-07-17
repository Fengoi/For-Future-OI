/*
求解 a[1] - a[n] 的 逆元

s[0] = 1;
for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p;
sv[n] = qpow(s[n], p - 2);
// 当然这里也可以用 exgcd 来求逆元,视个人喜好而定。
for (int i = n; i >= 1; --i) sv[i - 1] = sv[i] * a[i] % p;
for (int i = 1; i <= n; ++i) inv[i] = sv[i] * s[i - 1] % p;

*/

#include<bits/stdc++.h>
using namespace std;

typedef int type;
inline type read(){
	type x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){  
		x = (x<<1) + (x<<3) + (ch^48);
		ch = getchar();
	}
	return x * f;
}
inline void write(type x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

typedef long long lt;
const int N = 5e6 + 10;
int n, p, a[N], sum[N], sv[N], inv[N];
int k;
int ans;

int qp(int a, int n, int p){//快速幂
    int b = 1;
    for(; n; n >>= 1, a = 1ll * a * a % p)
        if(n & 1) b = 1ll *b * a % p;
    return b;
}

lt exgcd(lt a, lt b, lt &x, lt &y){
    lt gcd, tmp;
    if(!b){
        x = 1, y = 0;
        return a;
    }
    gcd = exgcd(b, a % b, x, y);
    tmp = x;
    x = y;
    y = tmp - a / b * y;
    return gcd;
}

int main(){
    n = read(), p = read(), k = read();

    sum[0] = 1;
    for(int i = 1; i <= n; i++){
        a[i] = read();
        sum[i] = 1ll * sum[i-1] * a[i] % p;
    }

    //invc();
    sv[n] = qp(sum[n], p-2, p);
    for (int i = n; i >= 1; i--) sv[i - 1] = 1ll * sv[i] * a[i] % p;
    for (int i = 1; i <= n; i++) inv[i] = 1ll * sv[i] * sum[i - 1] % p;

    int ks = k;
    for(int i = 1; i <= n; i++, ks = 1ll * ks * k % p){
        ans = (ans +  1ll * ks * inv[i] % p) % p;
    }
    write(ans);

    return 0;
}