//书上的经典例题！（洛谷上也有）

#include<bits/stdc++.h>
using namespace std;

typedef long long lt;

lt exgcd(lt a, lt b, lt &x, lt &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    lt gcd = exgcd(b, a%b, x, y);
    lt t = x;
    x = y;
    y = t - a/b * y;
    return gcd;
}

int main(){
    lt nok = 0, x, y, m, n, l, X, Y, gcd;

    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);

    lt b = n-m, a = x-y;

    if(b < 0){
        b = -b;
        a = -a;
    }

    if((x-y) % (gcd = exgcd(b, l, X, Y)) != 0) printf("Impossible\n");

    else printf("%lld\n", (a/gcd * X % (l/gcd) + (l/gcd)) % (l/gcd));
    return 0;
}