#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define lson (x<<1),l,mid
#define rson (x<<1|1),mid+1,r
using namespace std;
typedef long long LL;
const int maxn = 2e5+20;
int n, m;
struct node{
	int lx, rx, len;
	LL sum, suml, sumr;
}Tree[maxn<<2];

inline int read(){
    int x = 0, f = 1 ; char c = getchar() ;
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1 ; c = getchar() ; } 
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; c = getchar() ; } 
    return x * f ;
}

node pushup(node x,node y){
	node z;
	z.lx = x.lx; z.rx = y.rx ;
	z.sum = x.sum + y.sum; z.len = x.len + y.len ;
	if(x.rx <= y.lx){
		z.sum += 1ll * x.sumr * y.suml ;
		if(x.suml==x.len) z.suml = x.len + y.suml ;
		else z.suml = x.suml ;
		if(y.sumr==y.len) z.sumr = x.sumr + y.len ;
		else z.sumr = y.sumr ;
	}
	else z.suml = x.suml, z.sumr = y.sumr ;
	return z; 
}

void build(int x, int l, int r){
	if(l == r){
		Tree[x].lx = Tree[x].rx = read();
		Tree[x].len = Tree[x].sum = Tree[x].suml = Tree[x].sumr = 1;
		return ; 
	}
	build(lson); build(rson);
	Tree[x] = pushup(Tree[x<<1], Tree[x<<1|1]);
}

void update(int x, int l, int r, int pos, int k){
	if(l == r){
		Tree[x].lx = Tree[x].rx = k;
		return ;
	}
	if(pos <= mid) update(lson, pos, k);
	else update(rson, pos, k);
	Tree[x] = pushup(Tree[x<<1], Tree[x<<1|1]);
}

node query(int x, int l, int r, int L, int R){
	if(L<=l && r<=R) return Tree[x];
	if(R <= mid) return query(lson, L, R);
	if(mid < L) return query(rson, L, R);
	return pushup(query(lson, L, R), query(rson, L, R));
}

int main(){
	n = read(); m = read();
	build(1, 1, n);
	for(int i = 1; i <= m; i++){
		int op = read(), l = read(), r = read();
		if(op == 1) update(1, 1, n, l, r);
		else printf("%lld\n", query(1, 1, n, l, r).sum);
	}
	return 0;
}