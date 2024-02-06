#include <bits/stdc++.h>
using namespace std;

int x[105];

int main(){
    freopen("data.in", "w", stdout);
    int n = 100;
    cout << n << endl;
    for(int i = 1; i <= n; i++) x[i] = i;
    for(int i = 1; i <= n; i++){
        int b = 0;
        for(int j = 1; j <= n; j++){
            if(j<i) cout << "-1 ", b += -1*x[j];
            else if(j==i) cout << "1 ", b += 1*x[j];
            else if(j==n) cout << "1 ", b += 1*x[j];
            else cout << "0 ";
        }
        cout << b << endl;
    }
    return 0;
}