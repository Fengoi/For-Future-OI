// pi 表示 长度
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6*2 + 5;
string S, T, A;
int pi[N];
int main(){
    cin >> S;
	cin >> T;
    int m = T.size();
    int n = S.size();
    A = T;
    A += '#';
	A += S;
    pi[0] = 0;
    int len = A.size();
    for(int i = 0; i < len-1; i++){
        int k;
        bool flag = false;
        for(k = pi[i]; k >= 0 ;k = pi[k-1]){
            if(A[k] == A[i+1]){
                flag = true; break;
            }
            if(k == 0) break;
        }
        if(flag) pi[i+1] = k+1;
        else pi[i+1] = 0;
    }
    for(int i = 0; i < len; i++){
        if(pi[i] == m){
            int num = i-m+1-m;
            printf("%d\n", num);
        }
    }
    for(int i = 0; i < m; i++){
        printf("%d ", pi[i]);
    }
    return 0;
}
//ABA
//ABABABC