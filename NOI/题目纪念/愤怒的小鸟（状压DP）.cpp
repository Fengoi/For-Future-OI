// O(T * n * 2^n)
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 45;
const double eps = 1e-8;
lt T, n, m, lines[N][N], start[1<<19], dp[1<<19];
double x[N], y[N];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

void equation(double &a, double &b, lt i, lt j){
    a = -(y[i]*x[j] - y[j]*x[i]) / 
         (x[j]*x[j]*x[i] - x[i]*x[i]*x[j]);

	b = (y[i]*x[j]*x[j] - y[j]*x[i]*x[i])/
        (x[i]*x[j]*x[j] - x[j]*x[i]*x[i]);
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    for(int i = 0; i < (1<<18); i++){
		int j = 1;
		for(; j <= 18 && i & (1<<(j-1)); j++);
		start[i] = j;
	}

    cin >> T;

    while(T--){
        memset(lines, 0, sizeof lines);
		memset(dp, 0x3f, sizeof dp); dp[0] = 0;

        cin >> n >> m;
        for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(fabs(x[i]-x[j]) < eps) continue;
                double a, b;
                equation(a, b, i, j);
                if(a > -eps) continue; // a > 0
                for(int k = 1; k <= n; k++){
                    if(fabs(a*x[k]*x[k] + b*x[k] - y[k]) < eps)
                        lines[i][j] |= (1<<(k-1));
                }
            }
        }

        for(int i = 0; i < (1<<n); i++){
            lt j = start[i];
            dp[i|(1<<(j-1))] = min(dp[i|(1<<(j-1))], dp[i]+1);
            for(int k = 1; k <= n; k++)
                dp[i|lines[j][k]] = min(dp[i|lines[j][k]], dp[i]+1);
        }

        cout << dp[(1<<n)-1] << '\n';
    }

    return 0;
}