#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 1e6 + 10, M = 1e12 + 10, mod = 19930726;
char s[N], mncs[N*2];
lt n, k, p[N*2], cnt[N], all, ans = 1;

void manacher(char s[], lt p[]){
    mncs[0] = '#';
    for(int i = 0; i < n; i++){
        mncs[2*i+1] = s[i];
        mncs[2*i+2] = '#';
    }

    lt mid, r = -1;
    for(int i = 0; i < 2*n+1; i++){
        p[i] = (i<=r) ? min(p[2*mid-i], (lt)r-i) : 0;
        while(p[i] < i && mncs[i-p[i]-1] == mncs[i+p[i]+1]) p[i]++;
        if(i + p[i] > r) r = i + p[i], mid = i;
    }
}

lt quick_power(lt a, lt n){//a的n次
    if(n == 1) return a; else if(n == 0) return 1;
    lt b = quick_power(a, n/2);
    return n%2 == 0 ? b*b%mod : b*b%mod*a%mod;
}

int main(){
    // freopen("P1659_15.in", "r", stdin);
    // freopen("6.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    scanf("%s", s);
    manacher(s, p);
    lt maxx = 0;
    for(int i = 0; i < 2*n+1; i++)
        cnt[p[i]]++, maxx = max(maxx, p[i]);
    for(int i = maxx; i >= 1; i--){
        cnt[i] = (cnt[i] + cnt[i+2]) % mod;
        all = (all + cnt[i]);
    }
    if(all < k){
        printf("-1");
        return 0;
    }
    for(int i = maxx; i >= 1; i--){
        if(!cnt[i] || i%2 == 0) continue;
        if(cnt[i] < k) ans = ans * quick_power(i,cnt[i]) % mod;
        else{
            ans = ans * quick_power(i, k) % mod;
            break;
        }
        k -= cnt[i];
    }
    // for(int i = maxx; i >= 1; i--)
    //     cout<<cnt[i]<<" "; cout<<endl;
    printf("%lld", ans);
    return 0;
}