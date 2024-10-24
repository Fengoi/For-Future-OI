// CF1175E：Minimal Segment Cover（最小线段覆盖问题）
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 600005;
lt n, m, l, r, ma, a[N], f[N][22];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> l >> r;
        a[l] = max(a[l], r);
        ma = max(ma, r);
    }
    for(int i = 1; i <= ma; i++){
        a[i] = max(a[i], a[i-1]);
    }//预处理出从一个左端点用一条线段最远能覆盖到哪个右端点 注意线段起点可能在这个左端点左边
    for(int i = 0; i <= ma; i++) f[i][0] = a[i];
    for(int k = 1; k <= 20; k++)
        for(int i = 0; i <= ma; i++)
            f[i][k] = f[f[i][k-1]][k-1];
    while(m--){
        cin >> l >> r;
        lt ans = 0;
        for(int i = 20; i >= 0; i--){
            if(f[l][i] < r){
                ans += 1<<i;
                l = f[l][i];
            }
        }
        if(a[l] >= r) cout << ans + 1 << '\n';
        else cout << -1 << '\n';
    }
    
    return 0;
}