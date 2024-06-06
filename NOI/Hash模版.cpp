//双模数 双进制(基)
#include<bits/stdc++.h>
using namespace std;
const long long p1 = 10000000643, p2 = 10000001087, b1 = 233, b2 = 366;
int T;
string s;
unordered_map<long long, bool> g;
long long calc(string s, long long p, long long b){
    long long res = 0;
    for(int i = s.size()-1; i >= 0; i--){
        res = (res*b + (s[i]-'0'+1)) % p;
    }
    return res;
}
int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);
    scanf("%d", &T);
    long long ans;
    while(T--){
        cin>>s;
        long long h1 = calc(s, p1, b1);
        long long h2 = calc(s, p2, b2);
        ans += h1;
    }
    cout<<ans;
    return 0;
}