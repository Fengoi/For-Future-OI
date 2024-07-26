//O(3^M) => n = 2^M
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 3e5 + 10, mod = 1e9 + 7;
lt n, a[N], f[N], ans;

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    for(int i = n; i >= 1; i--){
        for(lt x = a[i] & (a[i]-1); x; x = a[i] & (x-1)){//枚举 a 的二进制（真）子集有一个常用的套路
            f[a[i]] += f[x];
        } 
        ans = (ans + f[a[i]]) % mod;
        f[a[i]]++;
    }
    printf("%lld", ans);
    return 0;
}
// 上述代码中的 f[a[i]]++ 表示一个以 ai 组成的长度为 1 的子序列。
//因此，如果我们要把统计答案写进上述过程中，为了保证统计到的答案是长度至少为 2 的子序列，ans += f[a[i]] 必须发生在 f[a[i]]++ 之前。