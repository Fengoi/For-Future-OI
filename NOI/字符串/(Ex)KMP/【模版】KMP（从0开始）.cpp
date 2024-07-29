// pi 表示 下标
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 1e6 + 10;
lt pi[N];
lt la, lb, j;
char a[N], b[N];

int main(){
    cin >> a;
    cin >> b;
    la = strlen(a), lb = strlen(b);
    j = -1; pi[0] = -1;
    for(int i = 1; i < lb; i++){
        while(j >= 0 && b[i] != b[j+1]) 
            j = pi[j];
        if(b[j+1] == b[i]) 
            j++;
        pi[i] = j;
    }
    j = -1;
    for(int i = 0; i < la; i++){
        while(j >= 0 && b[j+1] != a[i])
            j = pi[j];
        if(b[j+1] == a[i])
            j++;
        if(j == lb-1){
            printf("%lld\n", i-lb+2);
            j = pi[j];
        }
    }
    for(int i = 0; i < lb; i++){
        printf("%lld ", pi[i]+1);
    }
}