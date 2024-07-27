//O(nlogn)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 50000 + 10;
lt n, a[N], s[N], f[N], g[N], tag[N];
//s:前缀和；f：合并前 i 个位置的最少操作次数；g：最少操作次数后 i 位置的塔高

int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        s[i] = s[i-1] + a[i];
    }
    for(int j = 1; j <= n; j++){
        // 找到 j-1 能够更新的第一个位置 i
        lt i = lower_bound(s + 1, s + 1 + n, g[j-1] + s[j-1]) - s;
        // 给位置 i 打上标记
        tag[i] = j - 1;
        // 使用 tag 之前，要和前一个位置的 tag 取 max
        tag[j] = max(tag[j], tag[j-1]);/*哇~~~~~这一步真的很牛逼！*/
        // tag[j] 是最后一个能够更新 j 的位置，因此从 tag[j] 位置转移过来
        f[j] = f[tag[j]] + (j - tag[j] - 1);
        g[j] = s[j] - s[tag[j]];
    }
    printf("%lld", f[n]);
    return 0;
}