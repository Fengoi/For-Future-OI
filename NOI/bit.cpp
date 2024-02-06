//  树状数组：单点修改+区间求和

#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
int a[N], bit[N], n;

// lowbit(x) 表示 x 的最低非零二进制位的值
// 比如  x = 14 = (1110), lowbit(x) = 2
//       x = 80 = (1010000), lowbit(x) = 16
//                 0101111 反码
//                 0110000 补码
//                 0010000 lowbit
int lowbit(int x){
    return x & (-x);
}

// bit[i] = a[i] + a[i-1] + ... + a[i-lowbit(i)+1]，就是从第i个位置往前 lowbit(i) 个数的和

void add(int x, int k){
    for(; x <= n; x += lowbit(x))
        bit[x] += k;
}

int sum(int x){
    int ans = 0;
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


//   树状数组2
//   记 d[i] = a[i] - a[i-1]，也就是 a 的差分数组
//   我们让树状数组是 d 的树状数组
//   如果让 a 的 [l,r] 都 +k
//   那么： d[l] += k,  d[r+1] -= k,  d[l+1]...d[r] 不受影响,  所以相当于对d数组的单点修改
//   求 a[i] 的值怎么办？
//   a[i] = d[1] + d[2] + ... + d[i] = sum(i)