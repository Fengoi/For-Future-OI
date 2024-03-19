# [ SNCPC2019 ] Paper-cutting【保姆级】

## 前言
- 这是本蒻蒟第一次写题解。
- 本题非常考验循环后的 `清零` 操作，请做完后认真检查！

## 前置知识（真！）
[【模版】manacher](https://www.luogu.com.cn/problem/P3805)

## 解决问题 O(T* n* m)

### 简化题目
```
给定一个 01 矩阵，上下左右尽量对折，最终剩下的区块计算有多少个 0 的连通块 ( 只允许"上下左右"连通 ) 。
```

### Think-1 折
本题的所提到的 `对折` 的本质其实就是 `回文字符串` 的一半部分被 `对折`。

因此，诸位想到的 `第一步` 一定是将矩阵从“上下左右”疯狂对折，没错，你是正确的！

### Solve-1
如果你完成了 [【模版】manacher](https://www.luogu.com.cn/problem/P3805) ，那你应该知道有一个概念叫做 **回文半径** 。

这里我们用 `p[i]` 来表示：位置的最大回文半径，就是以i位置为中心，向左右对称扩展，最多能扩展几格。

模版题中的样例只有一行，而我们这里是一个 **矩形** ，是有多行的字符串！

这时，我们引入一个新的概念： `min_p[i]`。

`min_p[i]` 表示：第 `i` 列的最大公共回文半径。

求解这个数组时，请不要开二维数组，一是空间，二是时间，因此，我们可以在每次进入 `Mnancher()` 函数时，将定义为 **全局变量** 每次都取 **min** 。

#### Partial Code
```cpp
const int N = 1e6 + 10;
int min_p[N*2], min_pt[N*2];//因为 上下 左右 均翻折，故设置两个！！！

void manacher(string s, int min_p[]){
    //...  Part Of Mnancher

    for(int i = 0; i <= 2*len; i++) 
        min_p[i] = min(min_p[i], p[i]);
    
    /* 
    memset(mncs, '\0', sizeof(char) * (len*2+1)); 
    memset(p, 0, sizeof(int) * (len*2+1)); 
    --清空操作
    这里我放到了主函数，请注意！
    */
}
```

有了它，你便可以，你便可以愉快地进行翻折的操作！

#### 先上代码！
```cpp
//从右往左翻
lr = csl-1;// csl 表示右边界
for(int i = csl-1; i >= 0; i--){
    if(i+min_p[i] >= lr && i % 2 == 0 /* 保证折的位置是'#',因为折不可以折数字！ */) lr = i;
} lr--;//让它变成数字位置
```

关键：

$$
i \pm min_p[i] \geq l（l指折的位置）
$$

只要 **i** 所在位置的回文半径 **超过** 了上一次折的边界，那么，这个位置也就是 **折** 的位置，记得进行 **上下左右** 四次！

又因为 `min_p` 数组是建立在 **Manacher** 算法中创建的加了 **#** 的字符串数组下进行，所以 `i % 2 == 0` 一定是 **#** 号的位置（折纸位置）！

又所以，最后我们 **求得了** ：
`lr`（右边折后位置），`lf`（左边折后位置），`lo`（上边折后位置），`lu`（下边折后位置）。

- 注：记得将他们转化成原数组的位置！！！

### Think-2 找
那么，诸位接下来的 **第一反应** 一定是 `bfs` ！

```
从 折后区间 的开始位置找 0 ，找到就看它 连着 几个 0 ，然后打标记
```

### Solve
那我们不如优化一下，就像 **种萝卜** 一样，在 `bfs` 的过程中，遇到 `0` 我们就把它变成 `1` ！

#### Partial Code
```cpp
const int dx[4] = {1, 0, -1, 0}; // 移列
const int dy[4] = {0, -1, 0, 1}; // 移行

void dfs(int i, int j){// 第 i 行, 第 j 列
    s[i][j] = '1';  num--;  if(!num) return ;
    for(int c = 0; c < 4; c++){
        if(i + dy[c] >= lo && i + dy[c] <= lu && j + dx[c] >= lf && j + dx[c] <= lr && s[i + dy[c]][j + dx[c]] == '0') 
            { dfs(i + dy[c], j + dx[c]); }
    }
    return ;
}
```

如果看到这里，我相信，你一定懂得一二了！！！

## 猜你心，解你疑
**Q：** 是否考虑对折部分的长度大小，优先折大的 `min_p[i]` 。
- 答：多虑了。如果倒着想，最后折出来的区间一定是 **唯一** 的！所以顺序是无所谓的！

- 总结：无论你心中的折的顺序的之类的问题，请明白：
```
最后折出来的区间一定是 唯一 的！
```

## 特别注意！！！
- 如果你是正常的 `memset` ，一定会出现 **TLE**，以为 `2*N` 太大了，会有许多的 **浪费清空** ！！！

可以像这样：
```cpp
memset(min_p, 0x3f, sizeof(int) * (2*m+1));
```

不为难你，我告诉你清空的变量：`ans`， `min_p`， `p`， `mncs` （其中 `p` 和 `mncs` 是每次 `Manacher` 都要清空！！！）

## Code
```cpp
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
```