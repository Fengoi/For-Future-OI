// 单点加、区间求和

#include <bits/stdc++.h>
using namespace std;

const int N = 500005;
int sum[N*4], n;

// u: 当前节点编号
// [l,r]: 当前节点所表示的线段
// x: 要 +k 的位置
void add(int u, int l, int r, int x, int k){
    sum[u] += k;
    if(l==r) return;
    int mid = (l+r) / 2;
    if(x <= mid) add(u<<1, l, mid, x, k);
    else add(u<<1|1, mid+1, r, x, k);
}

// get_sum(u,l,r,x,y)
// 求的是 [l,r] 和 [x,y] 交集的和
// u: 当前节点编号
// [l,r]: 当前节点所表示的线段
// [x,y]: 求和区间
int get_sum(int u, int l, int r, int x, int y){
    // 如果当前节点完全落在求和区间内，直接返回sum
    if(x<=l && r<=y) return sum[u];
    int mid = (l+r) / 2;
    int res = 0;
    // 否则，说明当前节点不完全落在求和区间内，需要递归
    // 我们把 [l,r] 与 [x,y] 的交集 拆分成 “[l,mid] 与 [x,y] 的交集” + “[mid+1,r] 与 [x,y] 的交集”
    if(x <= mid) //这说明求和区间和左儿子表示的区间有交集
        res += get_sum(u<<1, l, mid, x, y);
    if(y > mid)  //这说明求和区间和右儿子表示的区间有交集
        res += get_sum(u<<1|1, mid+1, r, x, y);
    return res;
}

int main(){
    // 如果我现在有“让位置5加上9”的需求，应该：
    add(1, 1, n, 5, 9);

    // 如果我要询问 [4,7] 之间所有数的和，应该：
    cout << get_sum(1, 1, n, 4, 7) << endl;

    // get_sum(1, 1, 8, 4, 7)
    //                          1
    //           2                             3
    //      4         5                   6          7
    //     8 9      10 11               12 13      14 15
    // get_sum(1, 1, n, x, y) 访问的所有点数不超过 2*(log(n)+1)，复杂度是 O(log n)
    //   如果 左右儿子都有交集
    //   那么对于左儿子，要么左儿子的左儿子没有交集（所以不会进去）；要么左儿子的右儿子被完全包含（所以直接return）
    //       对于右儿子，要么右儿子的右儿子没有交集（所以不会进去）；要么右儿子的左儿子被完全包含（所以直接return）
}