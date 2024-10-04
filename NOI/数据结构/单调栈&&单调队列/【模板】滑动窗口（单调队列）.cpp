#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 1e6 + 10;
lt n, k, a[N], q[N], p[N];

void min_solve(){
    lt tail = 0;
    lt head = 1;
    for(int i = 1; i <= n; i++){
        while(head <= tail && q[tail] >= a[i]) tail--;
        q[++tail] = a[i];
        p[tail] = i;
        while(p[head] <= i-k) head++;
        if(i >= k) printf("%lld ", q[head]);
    } printf("\n");
}

void max_solve(){
    lt tail = 0;
    lt head = 1;
    for(int i = 1; i <= n; i++){
        while(head <= tail && q[tail] <= a[i]) tail--;
        q[++tail] = a[i];
        p[tail] = i;
        while(p[head] <= i-k) head++;
        if(i >= k) printf("%lld ", q[head]);
    } printf("\n");
}

int main(){
    scanf("%lld%lld", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    min_solve();
    max_solve();
}