#include <bits/stdc++.h>
using namespace std;

double A[1005][1005], x[1005];
int n;

bool gauss(){
    for(int i = 1; i <= n; i++){
        // 要把 A[i+1][i], A[i+2][i], ..., A[n][i] 都消掉
        // 首先要保证 A[i][i] 不是 0
        // 当一个 double 的绝对值小于 1e-16 时，我们就认为它是0，因为 double 永远有误差
        if( fabs(A[i][i]) < 1e-16 ){
            // int j = i+1;
            // while( j<=n && fabs(A[j][i])<1e-16 ) j++;
            // // 如果 j==n+1 说明 A[i][i], A[i+1][i], ..., A[n][i] 都是0，那么方程没有唯一解
            // if(j==n+1) return false;
            // swap(A[i], A[j]);

            // 列主元法：就是找到 A[i][i], A[i+1][i], ..., A[n][i] 里面绝对值最大的数，然后把那一行和第i行交换
            int j = i;
            for(int k = i+1; k <= n; k++)
                if(fabs(A[k][i]) > fabs(A[j][i])) j = k;
            if(fabs(A[j][i]) < 1e-16) return false;
            swap(A[i], A[j]);
        }
        for(int j = i+1; j <= n; j++){
            double c = -A[j][i] / A[i][i];
            for(int k = i; k <= n+1; k++)
                A[j][k] += c * A[i][k];
        }
    }
    for(int i = n; i >= 1; i--){
        x[i] = A[i][n+1] / A[i][i];
        for(int j = 1; j < i; j++)
            A[j][n+1] -= A[j][i] * x[i];
    }
    return true;
}

int main(){
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n+1; j++)
            scanf("%lf", &A[i][j]);
    bool result = gauss();
    if(result==false) cout << "No Solution" << endl;
    else{
        for(int i = 1; i <= n; i++)
            printf("%.8lf\n", x[i]);
    }
    return 0;
}