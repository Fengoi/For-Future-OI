#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 1e6+5;
long long n, m, a[N], maxx[N][21], p[N];

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0'||ch > '9'){if (ch == '-') f = -1; ch =getchar();}
	while (ch >= '0' && ch <= '9'){x = x*10+ch-48; ch = getchar();}
	return x * f;
}

int askMax(int l, int r){
	lt k = __lg(r-l+1); //log2(r-l+1) //p[r-l+1]
	return max(maxx[l][k], maxx[r-(1<<k)+1][k]);
}
int main(){
	int n = read(), m = read();
    for(int i = 1; i <= n; i++) maxx[i][0] = read();
	for(int k = 1; k <= 20; k++){//倍增
		for(int i = 1; i+(1<<k)-1 <= n/*i<=n*/; i++){
			maxx[i][k] = max(maxx[i][k-1], maxx[i+(1<<(k-1))][k-1]);
		}
	}
	for(int len = 1; len <= n; len++){
		for(int k = 20; k >= 0; k--){
			if(len & (1<<k)){
				p[len] = k;
				break;
			}
		}
	}
	for(int i = 1; i <= m; i++){
		int l = read(), r = read();
		printf("%d\n", askMax(l, r));
	}
	return 0;
}