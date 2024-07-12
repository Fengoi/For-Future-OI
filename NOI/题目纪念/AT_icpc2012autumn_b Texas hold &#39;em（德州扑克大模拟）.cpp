#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
string me1, me2, ri1, ri2;
string yz1, yz2, yz3;
string fn[65]; lt num;
char se[10], su[20];

lt zh(char s){//转换
    if(s == '2') return 2; if(s == '3') return 3; if(s == '4') return 4;
    if(s == '5') return 5; if(s == '6') return 6; if(s == '7') return 7;
    if(s == '8') return 8; if(s == '9') return 9; if(s == 'T') return 10;
    if(s == 'J') return 11; if(s == 'Q') return 12; if(s == 'K') return 13; if(s == 'A') return 14;
    return 0;
}
bool cmp(lt a, lt b){ return a > b; }

bool sz(string a, string b, string c, string d, string e){//顺子
    lt g[16];
    memset(g, 0, sizeof(g));
    g[1] = zh(a[1]), g[2] = zh(b[1]), g[3] = zh(c[1]), g[4] = zh(d[1]), g[5] = zh(e[1]);
    sort(g+1, g+1+5, cmp);//排序
    if(g[1] == 14){
        if(g[2] == 13 && g[3] == 12 && g[4] == 11 && g[5] == 10) return true;
        else if(g[2] == 5 && g[3] == 4 && g[4] == 3 && g[5] == 2) return true;
        else return false;
    }
    else{
        for(int i = 2; i <= 5; i++){
            if(g[i-1] - g[i] != 1) return false;
        }
        return true;
    }
}

bool th(string a, string b, string c, string d, string e){//同花
    if(a[0] == b[0] && b[0] == c[0] && c[0] == d[0] && d[0] == e[0]) return true;
    else return false;
}

lt conths(string a, string b, string c, string d, string e){
    lt g[16];
    memset(g, 0, sizeof(g));
    g[1] = zh(a[1]), g[2] = zh(b[1]), g[3] = zh(c[1]), g[4] = zh(d[1]), g[5] = zh(e[1]);
    sort(g+1, g+1+5, cmp);//排序
    if(g[1] == 14 && g[2] == 13) return (lt)1e15;
    else if(g[1] == 14 && g[2] == 5) return (lt)9e14 + 5;
    else return (lt)9e14 + g[1] * 100;
}

lt conth(string a, string b, string c, string d, string e){
    lt g[16];
    memset(g, 0, sizeof(g));
    g[1] = zh(a[1]), g[2] = zh(b[1]), g[3] = zh(c[1]), g[4] = zh(d[1]), g[5] = zh(e[1]);
    sort(g+1, g+1+5, cmp);//排序
    
    return (lt)6e14 + g[1] * (lt)1e8 + g[2] * (lt)1e6 + g[3] * (lt)1e4 + g[4] * 100 + g[5];
}


lt consz(string a, string b, string c, string d, string e){
    lt g[16];
    memset(g, 0, sizeof(g));
    g[1] = zh(a[1]), g[2] = zh(b[1]), g[3] = zh(c[1]), g[4] = zh(d[1]), g[5] = zh(e[1]);
    sort(g+1, g+1+5, cmp);//排序

    if(g[1] == 14 && g[2] == 5) return (lt)5e14 + 1;
    else if(g[1] == 14 && g[2] == 13) return (lt)5e14 + 99999;
    else return (lt)5e14 + g[1];
}

lt ths(string a, string b, string c, string d, string e){//是否同花是否顺
    if(th(a, b, c, d, e) && sz(a, b, c, d, e)){
        return conths(a, b, c, d, e);
    }
    else if(th(a, b, c, d, e)){
        return conth(a, b, c, d, e);
    }
    else if(sz(a, b, c, d, e)){
        return consz(a, b, c, d, e);
    }
    else return 0;
}

lt congp(string a, string b, string c, string d, string e){
    lt g[16];
    memset(g, 0, sizeof(g));
    g[1] = zh(a[1]), g[2] = zh(b[1]), g[3] = zh(c[1]), g[4] = zh(d[1]), g[5] = zh(e[1]);
    sort(g+1, g+1+5, cmp);//排序
    
    return (lt)1e14 + g[1] * (lt)1e8 + g[2] * (lt)1e6 + g[3] * (lt)1e4 + g[4] * (lt)100 + g[5];
}

lt xt(string a, string b, string c, string d, string e){// 算条子
    //HA D9 H3 H4 H5 DA C6
    lt g[30];
    memset(g, 0, sizeof(g));
    g[zh(a[1])]++, g[zh(b[1])]++, g[zh(c[1])]++, g[zh(d[1])]++, g[zh(e[1])]++;

    lt h[30]; //统计有几个"相同点数数目"相同的
    memset(h, 0, sizeof(h));
    for(int i = 2; i <= 14; i++){ 
        lt v = zh(su[i]);
        if(g[v]) h[g[v]]++;
    }
    if(h[4] == 1 && h[1] == 1){//四条
        lt w = 0;
        for(int i = 2; i <= 14; i++){
            lt v = zh(su[i]);
            if(g[v] == 4) w += v * 100;
            else if(g[v] == 1) w += v;
        }
        return (lt)8e14 + w;
    }
    if(h[3] == 1 && h[2] == 1){//满堂红
        lt w = 0;
        for(int i = 2; i <= 14; i++){
            lt v = zh(su[i]);
            if(g[v] == 3) w += v * 100;
            else if(g[v] == 2) w += v;
        }
        return (lt)7e14 + w;
    }
    if(h[3] == 1 && h[1] == 2){//三条
        lt w = 0, l = 1;
        for(int i = 14; i >= 2; i--){
            lt v = zh(su[i]);
            if(g[v] == 3) w += v * (lt)1e4;
            else if(g[v] == 1){
                if(l == 1) {w += v * 100; l++;}
                else w += v;
            }
        }
        return (lt)4e14 + w;
    }
    if(h[2] == 2 && h[1] == 1){//两对
        lt w = 0, l = 1;
        for(int i = 14; i >= 2; i--){
            lt v = zh(su[i]);
            if(g[v] == 2){
                if(l == 1) {w += v * 10000; l++;}
                else w += v * 100;
            }
            else if(g[v] == 1){
                w += v;
            }
        }
        return (lt)3e14 + w;
    }
    if(h[2] == 1 && h[1] == 3){//一对
        lt w = 0, l = 1;
        for(int i = 14; i >= 2; i--){
            lt v = zh(su[i]);
            if(g[v] == 2){
                w += v * (lt)1e6;
            }
            else if(g[v] == 1){
                if(l == 1) { w += v * (lt)1e4; l++; }
                else if(l == 2) { w += v * 100; l++; }
                else w += v;
            }
        }
        return (lt)2e14 + w;
    }
    if(h[1] == 5) return congp(a, b, c, d, e);

    return 0;
}

double ys(string me1, string me2, string ri1, string ri2, string yz1, string yz2, string yz3){
    lt lfns = 0;
    lt wn = 0;
    for(int i = 1; i <= num; i++){
        for(int j = i+1; j <= num; j++){
            if(fn[i] == me1 || fn[i] == me2 || fn[i] == ri1 ||
               fn[i] == ri2 || fn[i] == yz1 || fn[i] == yz2 || fn[i] == yz3){
                continue;
            }
            if(fn[j] == me1 || fn[j] == me2 || fn[j] == ri1 ||
               fn[j] == ri2 || fn[j] == yz1 || fn[j] == yz2 || fn[j] == yz3) continue;
            lfns++;
            lt ow = 0, oh = 0;
            string f[10];
            //算ow
            f[1] = me1, f[2] = me2, f[3] = yz1, f[4] = yz2,
            f[5] = yz3, f[6] = fn[i], f[7] = fn[j];

            lt j0, j1, j2, j3, j4;

            for(int i0 = 1; i0 <= 7; i0++){
                for(int i1 = i0+1; i1 <= 7; i1++){
                    for(int i2 = i1 + 1; i2 <= 7; i2++){
                        for(int i3 = i2 + 1; i3 <= 7; i3++){
                            for(int i4 = i3 + 1; i4 <= 7; i4++){
                                lt gh = max(ths(f[i0], f[i1], f[i2], f[i3], f[i4]), xt(f[i0], f[i1], f[i2], f[i3], f[i4]));
                                if(gh > ow) ow = gh;
                            }
                        }
                    }
                }
            }
            //算oh
            f[1] = ri1, f[2] = ri2;
            for(int i0 = 1; i0 <= 7; i0++){
                for(int i1 = i0+1; i1 <= 7; i1++){
                    for(int i2 = i1 + 1; i2 <= 7; i2++){
                        for(int i3 = i2 + 1; i3 <= 7; i3++){
                            for(int i4 = i3 + 1; i4 <= 7; i4++){
                                lt gh = max(ths(f[i0], f[i1], f[i2], f[i3], f[i4]), xt(f[i0], f[i1], f[i2], f[i3], f[i4]));
                                if(gh > oh) {oh = gh;}
                            }
                        }
                    }
                }
            }
            if(ow > oh) wn++;
        }
    }
    return (double)wn / (double)lfns;
}

int main(){
    //预处理
    se[1] = 'S'; se[2] = 'H'; se[3] = 'D'; se[4] = 'C';
    su[2] = '2'; su[3] = '3'; su[4] = '4'; su[5] = '5'; 
    su[6] = '6'; su[7] = '7'; su[8] = '8'; su[9] = '9';
    su[10] = 'T'; su[11] = 'J'; su[12] = 'Q'; su[13] = 'K'; su[14] = 'A';
    for(int i = 1; i <= 4; i++){
        for(int j = 2; j <= 14; j++){
            fn[++num].resize(2);
            fn[num][0] = se[i]; fn[num][1] = su[j];
        }
    }
    //输入
    while(1){
        cin >> me1;
        if(me1[0] == '#') break;
        cin >> me2 >> ri1 >> ri2;
        cin >> yz1 >> yz2 >> yz3;
        printf("%.15lf\n", ys(me1, me2, ri1, ri2, yz1, yz2, yz3));
    }
    return 0;
}

/*
让我们来定义一下：
10000000   皇家同花顺：同花色的 A、K、Q、J 和 10。这是同花顺的特例。     5 + A、K、Q、J、T

9000000    同花顺：五张连续的牌，并且花色相同。                         5 + 连续                                                  th && sz

8000000    四条：四张相同点数的牌。                                    / + 5                                       tx

7000000    满堂红：三张相同点数的牌，加上一对其他点数的牌。              / + (3 + 2)                                 tx

6000000    同花：五张花色相同但不连续的牌。                             5 + /                                                     th

5000000    顺子：五张连续的牌，但是花色不同。                           / + 连续                                                   sz

4000000    三条：只要有三张相同点数的牌。                               / + 3 + 1 + 1                               tx

3000000    两对：两张相同点数的牌，和另外两张相同点数的牌。               / + (2 + 2 + 1)                             tx

2000000    一对：只是一对相同点数的牌。                                 / + (2 + 1 + 1 + 1)                         tx

1000000   高牌：任何其他牌。                                           / + (1 + 1 + 1 + 1 + 1)                     tx
*/

/*
皇家同花顺：平局。// 1e7

同花顺：比较最高点数的牌。// 9e6 + 最高点数

四条：比较四张牌，然后比较剩下的一张。// 8e6 + 四张点数*1000 + 剩下一张点数

满堂红：比较三张牌，然后比较一对。 // 7e6 + 三张牌的点数*1000 + 剩下一对点数

同花：逐张比较所有牌。//  6e6 + a1 * 1e4 + a2 * 1e3 + a3 * 1e2 + a4 * 10 + a5;

顺子：比较最高点数的牌。 // 特殊情况：5e6 + 1 || 5e6 + 999999   5e6 + 最高点数

三条：比较三张牌，然后比较剩下的两张。 // 4e6 + 三张 * 10000 + 较高者 * 100 + 较低者

两对：先比较较高等级的一对，然后比较较低等级的一对，最后比较最后一张。// 3e6 + 高等级 * 10000 + 低等级 * 100 + 最后一张

一对：比较该对，然后比较剩下的三张。// 2e6 + 对 * 10000 + a1 * 100 + a2 * 10 + a3

高牌：逐张比较所有牌。//  1e6 + a1 * 1e4 + a2 * 1e3 + a3 * 1e2 + a4 * 10 + a5;
*/