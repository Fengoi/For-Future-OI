#include<bits/stdc++.h>
using namespace std;
const long long N = 1100000 , mod = 1e9+7;
int n;
// 这里 num[i] 表示 P(i) 的大小，而不是 Q(i) 的大小
// numQ[i] 表示 Q(i) 的大小
long long pi[N],num[N],numQ[N];
char A[N];
long long sum;
int jump[19][N];
int main(){
    //int clc = clock();
    //freopen("P2375_2.in","r",stdin);
    //freopen("sss.out","w",stdout);
    scanf("%d",&n);
    while(n--){
        sum = 1;//pi[0]=0 => 0+1=1
        memset(jump, 0 ,sizeof(jump));
        memset(pi, 0 ,sizeof(pi));
        memset(num, 0 ,sizeof(num));
        memset(numQ, 0 ,sizeof(numQ));
        scanf("%s",A);
        pi[0]=0;
        int len = strlen(A);
        for(int i=0; i < len-1 ; i++){
            int k;
            bool flag = false;
            for(k=pi[i] ; k>=0 ;k=pi[k-1]){
                if(A[k] == A[i+1]){
                    flag = true;
                    break;
                }
                if( k==0 ) break;
            }
            if(flag) pi[i+1] = k+1;
            else pi[i+1] = 0;

            if(pi[i+1]==0) num[i+1] = 0;
            else num[i+1] = num[pi[i+1]-1] + 1;
        }

        //倍增
        for(int k=1;k<=18;k++){
            jump[k][0] = 0;
        }
        for(int i = 1;i <= len ; i++){
            if(pi[i]==0) jump[0][i]=0;
            else jump[0][i] = pi[i]-1;
        }
        for(int k=1;k<=18;k++){
            for(int i = 1 ; i <= len; i++){
                jump[k][i] = jump[k-1][ jump[k-1][i] ];
            }
        }
        
        for(int i = 0; i<len ;i++){
            if(pi[i] == 0){
                numQ[i] = 0;
                continue;
            }
            if(pi[i] == 1){
                numQ[i] = 1;
                continue;
            }
            int mid = (i+1)/2;
            int t = pi[i]-1;//这里的t表示的是位置
            if(t+1<=mid){
                numQ[i] = num[i] ;
                continue;
            }
            for(int k = 18; k >= 0; k--)
                if(jump[k][t]+1 > mid) t = jump[k][t];
            t = jump[0][t];
            numQ[i] = num[t] + 1; // 这个需要再斟酌一下
        }
        for(int i = 0; i<len ;i++){
            //cout<<i<<":"<<num[i]<<" ";
            sum = sum*((numQ[i]+1)%mod)%mod;
        }
        printf("%lld\n",sum);
    }
    //cout<<(double)(clock()-clc)/CLOCKS_PER_SEC;
    return 0;
}