# AC自动机

AC自动机 = 字典树 + fail数组

对所有模式串建立字典树

假设 p 是字典树上的一个节点

从根节点到 p 的路径上所有的字母拼起来一定是某个模式串的前缀，我们记这个前缀为 $S_p$，我们说它是 p 代表的字符串

`fail[p]=q`，其中 q 也是一个节点，q 代表的前缀也是 $S_p$ 的后缀，并且是最长的那个。用数学语言就是：

$$
\mathcal{P}(p)=\{q \;|\; q是节点，满足q\neq p，且 S_q 是 S_p 的后缀\}
$$

$$
fail[p]\in\mathcal{P}(p),\quad 且 \;|S_{fail[p]}| = \max_{q\in \mathcal{P}(p)} |S_q|
$$

特别地，如果 $\mathcal{P}(p)=\varnothing$，那么 $fail[p]=0$。

1. `fail` 数组有啥用
2. `fail` 数组怎么求

“`fail`树”：节点 `i` 的父亲是 `fail[i]`，是一棵以0为根节点的树。

```
fail[i]=j
fail[j]=i
这是不可能的
```

对于字典树上的一个节点 $p$，如果你想知道 $S_p$ 的后缀里面有哪些是某个模式串的前缀，你只需要在 `fail` 树上，从 $p$ 出发，一直往上跳就行了。（跳fail）

“是某个模式串的前缀”=“是字典树上某个节点表示的字符串”

对于给定的文本串 $T$，有多少个不同的模式串是 $T$ 的子串。$T$ 的子串一定是 $T$ 的某个前缀的后缀。

做法：枚举 $T$ 的前缀，然后看有哪些模式串是这个前缀的后缀。

如果我们从字典树的根出发，按照 $T$ 的字母依次选边走，每走到一个点 $p$，我们就考虑 $S_p$ 的后缀里包含了哪些模式串（跳fail）

```cpp
int ans = 0;

int cur = 0;
int n = strlen(T);
for(int i = 0; i < n; i++){
        int j = T[i] - 'a';
        //cur = ch[cur][j];
        while(cur && ch[cur][j]==0) cur = fail[cur];
        cur = ch[cur][j];
        //上述写法会灵活应用fail数组，我只需要保证0点到cur是T的子树就行，如果按上述“//”写法，会显得呆板，有漏掉情况的可能性！
        for(int p = cur; p; p = fail[p]){
            if(mark[p]){
                ans += mark[p];
                mark[p] = 0;
            }
        }
    }
```

- [简单版本的自己写的AC代码~](https://www.luogu.com.cn/record/141807990)

万一走不下去咋办？

```cpp
int mark[N]; //mark[p] 的意思是节点 p 表示了几个模式串
bool lazy[N]; //lazy[p] 表示本来要从 p 出发跳 fail 把所有的 mark 加起来，但我暂时懒得跳

int ans = 0;

int cur = 0;
int n = strlen(T);
for(int i = 0; i < n; i++){
    int j = T[i] -'a';
    while(cur && ch[cur][j]==0) cur = fail[cur];
    if(ch[cur][j])
        cur = ch[cur][j];
    else{
        // 这里说明 cur 一定是 0，且 0 往 j 是走不动的
        // 我们什么都不做。
    }
    lazy[cur] = true;
    // lazy[cur]=true 表示本应执行下面这段代码，但没有执行
    // 【简单版】的数据比较水，可以直接执行下面这段代码，不用 lazy 标记
    // for(int p = cur; p; p = fail[p]){
    //     if(mark[p]){
    //         ans += mark[p];
    //         mark[p] = 0;
    //     }
    // }
}
```

哪些 `mark` 是要被加进答案的？如果 $q$ 在 `fail` 树上的子树里有 `lazy` 标记，那么 `mark[q]` 就应该被加进答案！

```cpp
// tot 是字典的节点数量
vector<int> g[N];

for(int i = 1; i < tot; i++){
    g[fail[i]].push_back(i);
}
bool nonsense = dfs(0);

// dfs 遍历 fail 树
bool dfs(int u){
    // flag 表示 u 的子树里面有没有 lazy 标记，一开始只考虑自己
    bool flag = lazy[u];
    for(int v : g[u]){
        flag |= dfs(v);
    }
    // dfs 不会访问重复节点，所以下面加了 mark[u] 之后没必要把 mark[u] 置为 0
    if(flag) ans += mark[u];
    return flag;
}
```

上面的代码在模式串为：`aaaa...aaaa`，且 `T=aaaa...aaaa` 时会退化成 $O(n^2)$。

怎么求 fail 数组？回顾 KMP

```
            uv
####......####

我们在求 pi(v) 的时候，会从 pi(u) 开始考虑
```

```cpp
// 用 BFS 来遍历字典树
// 求 Fail 之前，已经建立好了字典树
void getFail(){
    queue<int> que;
    fail[0] = 0；
    for(int c = 0; c < 26; c++){
        int v = ch[0][c];
        if(v != 0) fail[v] = 0, que.push(v);
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int c = 0; c < 26; c++){
            int v = ch[u][c];
            if(v==0) continue;
            // 如果 fail[u] 往 c 走能走通，假设走到 q
            // 那么 fail[v] 就等于 q
            // 如果走不通，就顺着 fail[u] 往上跳，直到往 c 能走通为止
            int p = fail[u];
            while(p && ch[p][c]==0) p = fail[p];
            if(ch[p][c])
                fail[v] = ch[p][c];
            else{
                // 如果到了这里，说明顺着 fail[u] 往上跳，一直都没法往 c 走通，那么意味着 v 表示的字符串的后缀里，没有任何一个可能是其它节点表示的字符串。
                fail[v] = 0;
            }
            que.push(v);
        }
    }
}
```

我们归纳一下用 AC 自动机做匹配的流程：

1. 建立模式串们的字典树，并算好每个点的 `mark`
2. 用 `getFail` 求 `fail` 数组
3. 把 `T` 放到字典树上去跑，边打 `lazy` 标记
4. 把 `fail` 树建出来
5. 用 `dfs` 来把该加的 `mark` 加上去

注意：我的代码没有 `lazy` 标记。。。【简单版】的数据太水了，所以我过了。

【加强版】一定要用 `lazy`，但跟我们的 `lazy` 不一样，思路是一样的，也是用一个类似 `lazy` 的东西提前打标记，然后最后用一个 `dfs` 来处理。