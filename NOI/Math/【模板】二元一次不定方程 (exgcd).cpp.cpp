#include<bits/stdc++.h>
using namespace std;

typedef int type;
inline type read(){
	type x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){  
		x = (x<<1) + (x<<3) + (ch^48);
		ch = getchar();
	}
	return x * f;
}
inline void write(type x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

typedef long long lt;
lt T, a, b, c;

lt exgcd(lt a, lt b, lt &x, lt &y){
    lt gcd, tmp;
    if(!b){
        x = 1, y = 0;
        return a;
    }
    gcd = exgcd(b, a%b, x, y);
    tmp = x;
    x = y;
    y = tmp - a/b*y;
    return gcd;
}

int main(){
    T = read();
    while(T--){
        a = read(), b = read(), c = read();
        lt x, y;
        lt d = exgcd(a, b, x, y);
        if(c % d != 0) printf("-1\n");
        else{
            x *= c / d, y *= c / d;
            lt p = b / d, q = a / d, k;
            if(x < 0) k = ceil((1.0-x)/p), x += p*k, y -= q*k; //将x提高到最小正整数 
            else if(x >= 0) k = (x-1)/p, x -= p*k, y += q*k; //将x降低到最小正整数 
            if(y > 0){  //有正整数解
                printf("%lld ", (y-1)/q+1);	//将y减到1的方案数即为解的个数 
				printf("%lld ", x);			//当前的x即为最小正整数x
				printf("%lld ", (y-1)%q+1); 	//将y取到最小正整数 
				printf("%lld ", x+(y-1)/q*p);	//将x提升到最大 
				printf("%lld ", y);			//特解即为y最大值 
            }
            else{ //无正整数解
                printf("%lld " ,x);			//当前的x即为最小的正整数x 
                printf("%lld",y + q * (lt)ceil((1.0-y)/q)); //将y提高到正整数 
            }
            printf("\n");
        }
    }
    return 0;
}

// ax + by = c;