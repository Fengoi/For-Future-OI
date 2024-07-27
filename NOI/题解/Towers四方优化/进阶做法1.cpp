//O(n^2)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 50000 + 10;
lt n, a[N], s[N], f[N], g[N];
//s:前缀和；f：合并前 i 个位置的最少操作次数；g：最少操作次数后 i 位置的塔高

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        s[i] = s[i-1] + a[i];
    }
    for(int i = 1; i <= n; i++){
        g[i] = INT_MAX; f[i] = INT_MAX;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < i; j++){
            if(s[i] - s[j] < g[j]) continue;
            if(f[i] > f[j] + (i-j-1)){
                f[i] = f[j] + (i-j-1);
                g[i] = s[i] - s[j];
            }
            else if(f[i] == f[j] + (i-j-1)){
                g[i] = min(g[i], s[i]-s[j]);
            }
        }
    }
    printf("%lld", f[n]);
    return 0;
}