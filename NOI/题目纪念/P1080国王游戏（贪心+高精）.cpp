#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 1e3 + 10;
lt n;

struct T{
	lt a, b;
	char cnta[10000], all[10000];//cnta 为前面所有a的乘积的逆序 all为乘积正序 
	char ca[100];// a转化成字符数组
	char ans[10000];//所获得金币数 
	int lans;
}f[N];

bool cmp(T a, T b){
	return a.a * a.b < b.a * b.b;
}

bool cmp2(T a,T b){//高精度比较 
	if(a.lans != b.lans)
		return a.lans > b.lans;
	else{
		for(int i = 0; i < a.lans; i++)
			if(a.ans[i] == b.ans[i]) continue;
			else return a.ans[i] > b.ans[i];
	}
	return 1 == 1;
}

void doit(int a, char b[]){//将数值转化成字符数组
	int lb = 0;
	while(a > 0){
		b[lb++] = a%10 + '0';
		a /= 10;
	}
	b[lb] = '\0';
}

void add(char c[], char d[], int i){//错位相加 
	int lc = strlen(c), j;
	int jw = 0, tmp;
	for(j = 0; j < lc; j++, i++){
		tmp = (d[i] > 0 ? d[i]-'0' : 0) + c[j] - '0' + jw;
		d[i] = tmp % 10 + '0';
		jw = tmp / 10;
	}
	if(jw){
		d[i++] = jw + '0';
	}
	d[i] = '\0';
}

void gc(char a[], char b[], char d[]){//高乘
	int i, j;
	int la = strlen(a);
	int lb = strlen(b);
	char c[10000];//记录乘数的每一位乘以被乘数的积 
	for(i = 0; i < la; i++){
		int tmp;
		int jw = 0;
		int lc = 0;
		for(j = 0; j < lb; j++){
			tmp = (a[i]-'0') * (b[j]-'0') + jw;
			c[lc++] = tmp % 10 + '0';
			jw = tmp / 10;
		}
		if(jw) c[lc++] = jw+'0';
		c[lc] = '\0'; 
		add(c, d, i);
	}
}

void mult(char a[], int b, char c[]){
	int i = 0 , tag = 0 , la = strlen(a) , lc = 0;
	int d = 0;
	while(i <= la){
		if(b > d){
			d = d * 10 + a[i++] - '0';
			if(tag) c[lc++] = '0';
		}else{
			c[lc++] = d / b + '0';
			d = d % b;
			d = d * 10 + a[i++] - '0';
			tag = 1;
		}
	}
	if(tag == 0) c[lc++] = '0';
	c[lc] = '\0';
}

int main(){
	scanf("%lld", &n);
	memset(f, 0, sizeof(f));
	scanf("%lld%lld", &f[0].a, &f[0].b);
	for(int i = 1; i <= n; i++){
		scanf("%lld%lld", &f[i].a, &f[i].b);
	}

	sort(f+1, f+1+n, cmp);

	//模版


	doit(f[0].a, f[0].ca); 
	f[0].cnta[0] = '1';
	f[0].cnta[1] = '\0';

	//得到前面大臣左手金币数的乘积的逆序 
	for(int i = 1; i <= n; i++){
		doit(f[i].a, f[i].ca);
		gc(f[i-1].cnta, f[i-1].ca, f[i].cnta);
	}

	//将乘积逆转 
	for(int i = 1; i <= n; i++){
		int k = 0;
		for(int j = strlen(f[i].cnta) - 1; j >= 0; j--)
			f[i].all[k++] = f[i].cnta[j];
		f[i].all[k] = '\0';
	}

	//得到每一位大臣能获得的金币数 
	for(int i = 1; i <= n; i++){
		mult(f[i].all, f[i].b, f[i].ans);
		f[i].lans = strlen(f[i].ans);
	}

	int ans = 1;
	for(int i = 2; i <= n; i++){
		if(!cmp2(f[ans], f[i]))
			ans = i;
	}
	printf("%s\n", f[ans].ans);
	return 0;
}