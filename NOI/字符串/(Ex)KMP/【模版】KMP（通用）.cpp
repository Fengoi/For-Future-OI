// pi 表示 下标
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 1e6 + 10;
lt pi[N];
lt la, lb, j;
char a[N], b[N];

int main(){
    cin >> a+1;
    cin >> b+1;
    la = strlen(a+1), lb = strlen(b+1);
    for(int i = 2; i <= lb; i++){
        while(j && b[i] != b[j+1])
            j = pi[j];
        if(b[j+1] == b[i]) 
            j++;
        pi[i] = j;
    }
    j = 0;
    for(int i = 1; i <= la; i++){
        while(j > 0 && b[j+1] != a[i])
            j = pi[j];
        if(b[j+1] == a[i])
            j++;
        if(j == lb){
            printf("%lld\n", i-lb+1);
            j = pi[j];
        }
    }
    for(int i = 1; i <= lb; i++){
        printf("%lld ", pi[i]);
    }
}