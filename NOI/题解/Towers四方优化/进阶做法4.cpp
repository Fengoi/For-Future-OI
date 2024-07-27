// O(n)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 2e5 + 10;
lt head, tail;
lt n, f[N], tag[N], sum[N], q[N];

int main(){
    scanf("%lld", &n);
    lt x;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &x);
        sum[i] = sum[i-1] + x;
    }
    tail = 1;
    for(int i = 1; i <= n; i++){
        while(head + 1 < tail && sum[i] >= sum[q[head+1]] + tag[q[head+1]])
            head++;
        f[i] = f[q[head]] + 1;
        tag[i] = sum[i] - sum[q[head]];
        while(head < tail && sum[q[tail-1]] + tag[q[tail-1]] > sum[i] + tag[i])
            tail--;
        q[tail++] = i;
    }
    printf("%lld", n-f[n]);
    return 0;
}