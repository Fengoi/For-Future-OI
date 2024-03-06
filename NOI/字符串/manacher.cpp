//  #a#a#b#b#a#a#a# 15个字符(0-14)
//  这样处理之后，可以把所有回文串都当成奇数长度
//  p[i]: 表示i位置的最大回文半径
//        就是以i位置为中心，向左右对称扩展，最多能扩展几格

#include<bits/stdc++.h>
using namespace std;

const int N = 1.1e7+5;
char s[N], mncs[N*2];
int p[N*2];

//    维护一个右端点最靠右的回文串
//    --------9|7678-8767|8----------
//               j  #  i

void manacher(char s[], int p[]){
    int n = strlen(s);
    mncs[0] = '#';
    for(int i = 0; i < n; i++){
        mncs[2*i+1] = s[i];
        mncs[2*i+2] = '#';
    }

    int mid, r = -1;
    for(int i = 0; i <= 2*n; i++){
        // if(i <= r) p[i] = min(p[2*mid-i], r-i);
        // else p[i] = 0;
        p[i] = (i <= r) ? min(p[2*mid-i], r-i) : 0;
        while(p[i] < i && mncs[i-p[i]-1] == mncs[i+p[i]+1]) p[i]++;
        if(i + p[i] > r) r = i + p[i], mid = i;
        // r 最多往右移动 n 次
    }
}

int main(){
    scanf("%s", s);
    int n = strlen(s);
    manacher(s, p);
    int ans = 0;
    for(int i = 0; i <= 2*n; i++)
        ans = max(ans, p[i]);
    cout << ans << endl;
    return 0;
}