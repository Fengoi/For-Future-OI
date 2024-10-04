// 单点加，区间求和
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 5e5 + 10;
lt a[N], bit[N], n;

lt lowbit(int x){
	return x & -x;
}

void add(int x, int k){
	for(; x <= n; x += lowbit(x))
		bit[x] += k;
}

lt sum(lt x){
	lt ans = 0;
	for(; x > 0; x -= lowbit(x))
		ans += bit[x];
	return ans;
}

int main(){
	int m,opt,x,y;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) add(i,a[i]);
	for(int T=1;T<=m;T++)
	{
		scanf("%d",&opt);
		if(opt==1) scanf("%d%d",&x,&y),add(x,y);
		if(opt==2) scanf("%d%d",&x,&y),printf("%d\n",sum(y)-sum(x-1));
	}
	return 0;
}