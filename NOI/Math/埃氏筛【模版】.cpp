#include<bits/stdc++.h>
using namespace std;
bool prime[100000010];
int kth_prime[6000010],cnt = 0;
int main(){
	int n,q;
	scanf("%d %d", &n, &q);
	memset(prime, 1 ,sizeof(prime));
	prime[1]=0;
	for(int i=2 ; i<=n ; i++){
		if(prime[i]) kth_prime[ ++cnt ] = i;
		for(int j=1;j<=cnt && i*kth_prime[j]<=n;j++){
			prime[i*kth_prime[j]] = 0;
			if(i % kth_prime[j] == 0) break;
		}
	}
	while(q--){
		int k;
		scanf("%d", &k);
		printf("%d\n", kth_prime[k]);
	}
	return 0;
}