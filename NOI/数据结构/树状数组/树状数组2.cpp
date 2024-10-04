// 区间加，单点查询
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5*5 + 10;
int a[N], d[N], bit[N], n;

int lowbit(int x){// lowbit(x) 表示 x 的最低非零二进制位的值
    return x & (-x);
}

void add(int x, int k){
    for(; x <= n; x += lowbit(x))
        bit[x] += k;
}

int sum(int x){
    int ans = 0;
    for(; x > 0; x -= lowbit(x))
        ans += bit[x];
    return ans;
}

int main(){
    int m, opt, x, y, k;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    for(int i = 1; i <= n; i++) d[i] = a[i] - a[i-1];
    for(int i = 1; i <= n; i++) add(i, d[i]);
    for(int T = 1; T <= m; T++){
        scanf("%d", &opt);
        if(opt == 1){
            scanf("%d%d%d", &x, &y, &k);
            add(x, k);
            add(y+1, -k);
        }
        if(opt == 2) scanf("%d", &x),printf("%d\n", sum(x));
    }
}
//   树状数组2
//   记 d[i] = a[i] - a[i-1]，也就是 a 的差分数组
//   我们让树状数组是 d 的树状数组
//   如果让 a 的 [l,r] 都 +k
//   那么： d[l] += k,  d[r+1] -= k,  d[l+1]...d[r] 不受影响,  所以相当于对d数组的单点修改
//   求 a[i] 的值怎么办？
//   a[i] = d[1] + d[2] + ... + d[i] = sum(i)