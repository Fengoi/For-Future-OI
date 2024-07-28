#include<bits/stdc++.h>
using namespace std;
const int N = 1e7*4 + 20;
char s[N], g[N], t[N];
int z[N], zt[N], l, r;
int main(){
    scanf("%s", g+1);
    scanf("%s", s+1);
    int len = strlen(s+1);
    l = 1, r = 1;
    for(int i = 2; i <= len; i++){
        if(i > r) z[i] = 0;
        else if(z[i-l+1] < r-i+1){
            z[i] = z[i-l+1];
        }
        else if(z[i-l+1] >= r-i+1){
            z[i] = r-i+1;
        }
        while(s[1+z[i]] == s[i+z[i]] && 1+z[i] <= len && i+z[i] <= len) z[i]++;
        if(i+z[i]-1 > r){
            r = i+z[i]-1, l = i;
        }
    }
    z[1] = len;
    /////////////////////////////
    int leng = strlen(g+1);
    for(int i = 1; i <= len; i++){
        t[i] = s[i];
    }
    t[len+1] = '#';
    for(int i = 1; i <= leng; i++){
        t[len+1+i] = g[i];
    }
    /////////////////////////////
    int lent = len + leng +1;
    l = 1, r = 1;
    for(int i = 2; i <= lent; i++){
        if(i > r) zt[i] = 0;
        else if(zt[i-l+1] < r-i+1){
            zt[i] = zt[i-l+1];
        }
        else if(zt[i-l+1] >= r-i+1){
            zt[i] = r-i+1;
        }
        while(t[1+zt[i]] == t[i+zt[i]] && 1+zt[i] <= lent && i+zt[i] <= lent) zt[i]++;
        if(i+zt[i]-1 > r){
            r = i+zt[i]-1, l = i;
        }
    }
    zt[1] = lent;
    ///////////////////////////
    long long ans = 0;
    for(int i = 1; i <= len; i++){
        ans ^= 1ll*i*(z[i]+1);
    }
    printf("%lld\n", ans);
    ans = 0;
    for(int i = len+1+1; i <= lent; i++){
        ans ^= 1ll*(i-len-1)*(zt[i]+1);
    }
    printf("%lld", ans);
    return 0;
}