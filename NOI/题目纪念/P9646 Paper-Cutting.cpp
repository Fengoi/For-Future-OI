#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const int N = 1e6 + 10;
const int dx[4] = {1, 0, -1, 0}; // 移列
const int dy[4] = {0, -1, 0, 1}; // 移行
int T, n, m, min_p[N*2], min_pt[N*2], lf, lr, lo, lu, num;// n 行 m 列
string s[N], st[N]/*反转后的串*/;
int ans = 0;
char mncs[N*2]; int p[N*2];

void manacher(string s, int min_p[]){
    //static char mncs[N*2]; static int p[N*2];//"stadic" mean: 定义全局，但只能局部使用，且是一次性的(但需要手动初始化(清空))
    // memset(mncs, '\0', sizeof(mncs)); memset(p, 0, sizeof(p));
    int len = s.size();
    mncs[0] = '#';
    for(int i = 0; i < len; i++){
        mncs[i*2+1] = s[i];
        mncs[i*2+2] = '#';
    }

    int mid, r = -1;
    for(int i = 0; i <= 2*len; i++){
        p[i] = (i <= r) ? min(p[2*mid-i], r-i) : 0;
        while(p[i] < i && mncs[i-p[i]-1] == mncs[i+p[i]+1]) p[i]++;
        if(i + p[i] > r) r = i + p[i], mid = i;
    }
    for(int i = 0; i <= 2*len; i++){
        min_p[i] = min(min_p[i], p[i]);
    }
}

void dfs(int i, int j){// 第 i 行, 第 j 列
    s[i][j] = '1';  num--;  if(!num) return ;
    for(int c = 0; c < 4; c++){
        if(i + dy[c] >= lo && i + dy[c] <= lu && j + dx[c] >= lf && j + dx[c] <= lr && s[i + dy[c]][j + dx[c]] == '0') 
            { dfs(i + dy[c], j + dx[c]); }
    }
    return ;
}

int main(){
    scanf("%d", &T);
    while(T--){
        ans = 0;
        
        scanf("%d%d", &n, &m);

        memset(min_p, 0x3f, sizeof(int) * (2*m+1));
        memset(min_pt, 0x3f, sizeof(int) * (2*n+1));

        //处理min_p 以及 输入 和 翻转串 pt
        int nu = n - 1; // 翻转串 pt 的 列 = n
        for(int x = 0; x < m; x++)
            st[x].resize(n);
        for(int i = 0; i < n; i++){
            cin >> s[i];//长为 m
            for(int k = 0; k <= m*2; k++){
            	p[k] = 0;
			}
            manacher(s[i], min_p);
            for(int x = 0; x < m; x++){//这里表示 m 行 n 列
               st[x][nu] = s[i][x];
            }
            nu--;
        }
        memset(mncs, 0, sizeof(char) * (2*m+1));

        //处理min_pt
        for(int i = 0; i < m; i++){
        	for(int k = 0; k <= n*2; k++){
        		p[k] = 0;
			}
        	manacher(st[i], min_pt);
		}
        memset(mncs, 0, sizeof(char) * (2*n+1));
            

        //处理左右
        int csl = m*2+1;
        //从右往左翻
        lr = csl-1;
        for(int i = csl-1; i >= 0; i--){
            if(i+min_p[i] >= lr && i % 2 == 0 /* 保证折的位置是'#' */) lr = i;
        } lr--;//让它变成数字位置
        //从左往右折
        lf = 0;
        for(int i = 0; i < lr; i++){
            if(i-min_p[i] <= lf && i % 2 == 0) lf = i;
        } lf++;

        //处理上下
        int cslt = n*2+1;
        //从右往左折(从上往下)
        lo = cslt-1;
        for(int i = cslt-1; i >= 0; i--){
            if(i+min_pt[i] >= lo && i % 2 == 0) lo = i;
        } lo--;
        //从左往右折(从下往上)
        lu = 0;
        for(int i = 0; i < lo; i++){
            if(i-min_pt[i] <= lu && i % 2 == 0) lu = i;
        } lu++;
        lo = cslt - lo - 1; lu = cslt - lu - 1;

        //现在，我们要将 lf, lr, lo, lu 转化成"串"的 lf, lr, lo, lu
        lf = (lf+1)/2 - 1, lr = (lr+1)/2 - 1, lo = (lo+1)/2 - 1, lu = (lu+1)/2 - 1;
        // cout<<lf<< " " << lr << " " << lo << " " << lu << endl;

        num = 0;
        //dfs
        for(int i = lo; i <= lu; i++)
            for(int j = lf; j <= lr; j++)
                if(s[i][j] == '0') num++;
        if(!num) printf("0\n");
        else{
            for(int i = lo; i <= lu; i++){
                for(int j = lf; j <= lr; j++){
                    if(s[i][j] == '0'){
                        ans++;
                        dfs(i, j); // 第 i 行, 第 j 列
                    }
                    if(!num) break;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}

/*笔记
#a#a#b#a#a#b
#a#a#a#k#k#k
   L

p[k][i]: 第k行第i个位置的最大回文半径

min_p[i] = min(p[0][i], p[1][i], ..., p[m][i])

最大公共回文半径

【从右往左折】
如果 i+min_p[i]>=len 说明可以以i为轴对折, 令 len=i

【从左往右折】
左边要记一个 L 表示折到了哪里
如果 i-min_p[i]<=L 就可以折

【从上往下折】、【从下往上折】
*/

/*举例(翻转串 )
12345   0
54321   1
12345   2
54321   3
  |
  ^
5 1 5 1
4 2 4 2
3 3 3 3
2 4 2 4
1 5 1 5

3 2 1 0 (原)
0 1 2 3 (翻转后)
*/

//#1#1#