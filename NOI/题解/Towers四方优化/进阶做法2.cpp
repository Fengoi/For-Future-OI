//O(n^2)
//稍加思考我们就能发现，每个 f[i] 都是从最后一个满足 g[j] ≤ s[i] − s[j] 的位置 j 转移过来的，因此我们可以做一点常数优化
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
        f[i] = INT_MAX;
        g[i] = INT_MAX;
    }
    for(int i = 1; i <= n; i++){
        for(int j = i-1; j >= 0; j--){
            if(s[i]-s[j] >= g[j] && f[j] + (i-j-1) < f[i]){
                f[i] = f[j] + (i-j-1);
                g[i] = s[i] - s[j];
                break;
            }
        }
    }
    printf("%lld", f[n]);
    return 0;
}