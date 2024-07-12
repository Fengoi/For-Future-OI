#include<bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10, mod = 51123987;
char s[N], mncs[N*2];
int n, p[N*2];
long long pre[N*2], suf[N*2], mei, all;

void manacher(char s[], int p[]){
	mncs[0] = '#';
	for(int i = 0; i < n; i++)
		mncs[2*i+1] = s[i], mncs[2*i+2] = '#';
    
    // for(int i = 0; i < 2*n+1; i++){
    //     cout<<mncs[i];
    // }
    // cout<<endl;

	int mid, r = -1;
	for(int i = 0; i < 2*n+1; i++){
		p[i] = i <= r ? min(p[2*mid-i], r-i) : 0;
		while(p[i] < i && mncs[i+p[i]+1] == mncs[i-p[i]-1]) p[i]++;
		if(i+p[i] > r) r = i + p[i], mid = i;
	}
}

void pres(long long pre[]){
    for(int i = 0; i < 2*n+1; i++)
        pre[i]++, pre[i+p[i]+1]--;
    for(int i = 1; i < 2*n+1; i++)
        pre[i] += pre[i-1];
	// for(int i = 0; i < 2*n+1; i++){
    //     cout<<pre[i]<<" ";
    // }
	// cout<<endl;
}

void sufs(long long suf[]){
    //(1) : 开头位置在i的回文串个数
    for(int i = 0; i < 2*n+1; i++){
        suf[i]++;
        if(p[i] < i) suf[i-p[i]-1]--;
    }
    for(int i = 2*n; i >= 0; i--)
        suf[i] = (suf[i] + suf[i+1]) % mod;
    //(2) : 开头位置在i右边的回文串个数
	// for(int i = 0; i < 2*n+1; i++){
    //     cout<<suf[i]<<" ";
    // }
    // cout<<endl;
    for(int i = 2*n; i >= 0; i--){
        suf[i] = (suf[i] + suf[i+2]) % mod;
    }
	// for(int i = 0; i < 2*n+1; i++){
    //     cout<<suf[i]<<" ";
    // }
    // cout<<endl;
}

int main(){
	scanf("%d%s", &n, s);
	manacher(s, p);
    pres(pre);
    sufs(suf);
    for(int i = 1; i < 2*n+1; i+=2) //因为0位置时，无不相交 的串(i-1<0)
        mei = (mei + pre[i]*suf[i+2]%mod) % mod;
	//求all
    long long all = 0;
	for(int i = 0; i < 2*n+1; i++){
        all = (all + ((p[i]+1)/2)) % mod;
	}
    all = (all*(all-1)/2)%mod;
	printf("%lld", ((all - mei)%mod + mod)%mod);
	return 0;
}
/*
pre: "bab a bab"  "ababab a bababa"  (【恰好】以i结尾的回文串个数)
a b a b a b  a b a
| | | | | |  | | |
+ 0 0 0 0 -
    + 0 0 0  0 0 0 -
| | | | | |  | | |
1 0 1 0 0 -1 0 0 0 -1
1 1 2 2 2 1  1 1 1 0
*/

/*
suf: 

(1) : 开头位置在i的回文串个数
"abab a baba"  "ababab a bababa"  
   a b a b a b a b a
|  | | | | | | | | |
-  0 0 0 0 + 
     - 0 0 0 0 0 0 + 
|  | | | | | | | | |
-1 0 0 0 0 1 0 0 0 0 
0  1 1 2 2 2 1 1 1 1 

(2) : 开头位置在i右边的回文串个数 : 后缀和
*/