#include<bits/stdc++.h>
using namespace std;
int n,m1,m2;
struct Plane{
    int id;
    int arrive,depart;
    bool operator < (const Plane & b) const{
        return depart > b.depart;
    }
}L1[100005],L2[100005];
int stp1[100005],stp2[100005];
int cnt1,cnt2;
int cnt[100005],cnti[100005],sum[100005],sumi[100005];
bool cmp(Plane a,Plane b){
    return a.arrive<b.arrive;
}

void work1(){//国内//统计stp1[i] 表示 飞机i 停靠的廊桥编号 以及cnt1数量
    priority_queue<Plane> T1;
    priority_queue<int> P1;
    for(int i=1;i<=n;i++)
        P1.push(-i);
    for(int i = 1 ; i <= m1 ; i++){
        //T1 表示正在停靠的飞机的集合
        //P1 表示空闲的廊桥编号集合
        //stp[i] 表示 飞机i 停靠的廊桥标号
        int st = L1[i].arrive;
        while(!T1.empty()&&T1.top().depart<st){
            P1.push(-stp1[T1.top().id]);
            T1.pop();
        }
        if(!P1.empty()){
            T1.push((Plane){i,L1[i].arrive,L1[i].depart});
            stp1[i]=-P1.top();
            cnt1++;
            P1.pop();
        }
        else{
            stp1[i]=-1;
        }
    }
}

void work2(){//国际//统计stp2[i] 表示 飞机i 停靠的廊桥编号 以及cnt2数量
    priority_queue<Plane> T2;
    priority_queue<int> P2;
    for(int i=1;i<=n;i++){
        P2.push(-i);
    }
    for(int i = 1 ; i <= m2 ; i++){
        //T2 表示正在停靠的飞机的集合
        //P2 表示空闲的廊桥编号集合
        //stp[i] 表示 飞机i 停靠的廊桥标号
        int st = L2[i].arrive;
        while(!T2.empty()&&T2.top().depart<st){
            P2.push(-stp2[T2.top().id]);
            T2.pop();
        }
        if(!P2.empty()){
            T2.push((Plane){i,L2[i].arrive,L2[i].depart});
            stp2[i]=-P2.top();
            P2.pop();
            cnt2++;
        }
        else{
            stp2[i]=-1;
        }
    }
}

void statistics(){//国内
    for(int i=1;i<=m1;i++){
        if(stp1[i]!=-1){
            cnt[stp1[i]]++;
        }
    }
    sum[1]=cnt[1];
    for(int c=2;c<=n;c++){
        sum[c]=sum[c-1]+cnt[c];
    }
}

void statistics_i(){
    for(int i=1;i<=m2;i++){
        if(stp2[i]!=-1){
            cnti[stp2[i]]++;
        }
    }
    sumi[1]=cnti[1];
    for(int c=2;c<=n;c++){
        sumi[c]=sumi[c-1]+cnti[c];
    }
}

int main(){
    // n1: 国内廊桥数量
    // m1: 国内飞机数量
    // n2: 国际廊桥数量
    // m2: 国际飞机数量
    //输入
    cin>>n>>m1>>m2;
    for(int i=1;i<=m1;i++){
        int a,b;
        cin>>a>>b;
        L1[i]={i,a,b};
    }
    sort(L1+1,L1+1+m1,cmp);
    /*for(int i=1;i<=m1;i++){
        cout<<L1[i].arrive<<" ";
    }
    cout<<endl;*/
    for(int i=1;i<=m2;i++){
        int a,b;
        cin>>a>>b;
        L2[i]={i,a,b};
    }
    sort(L2+1,L2+1+m2,cmp);
    /*for(int i=1;i<=m2;i++){
        cout<<L2[i].arrive<<" ";
    }
    cout<<endl;*/

    if(1){//注释
        int six=1;
        /*如果只有一架飞机
        int cnt=0;
        for(int i=1;i<=n;i++){
            P.push(-i);
        }
        for(int i = 1 ; i <= m1 ; i++){
            //T 表示正在停靠的飞机的集合
            //P 表示空闲的廊桥编号集合
            //stp[i] 表示 飞机i 停靠的廊桥标号
            int st = L[i].arrive;
            while(T.top().depart<st){
                P.push(stp[T.top().id]);
                T.pop();
            }
                if(!P.empty()){
                T.push((Plane){i,L[i].arrive,L[i].depart});
                stp[i]=-P.top();
                  P.pop();
               cnt++;
            }
            else{
                stp[i]=-1;
            }
        }
        */
    }
    
    //现在是国内以及国际

    work1();
    work2();
    /*
    cout<<endl;
    for(int i=1;i<=m1;i++){
        cout<<stp1[i]<<" ";
    }
    cout<<endl;
    for(int i=1;i<=m2;i++){
        cout<<stp2[i]<<" ";
    }
    cout<<endl;*/

    // stp1[i]: 国内的i号飞机停靠的廊桥;stp2[i]: 国际的i号飞机停靠的廊桥
    // cnt[c]: 数组stp的桶，表示stp=c的国内飞机有几个
    // sum[c] = cnt[1] + cnt[2] + ... + cnt[c]
    // cnti 与 sumi 表示国际的
    statistics();//统计
    statistics_i();

    int ans=0;
    for(int n1=0;n1<=n;n1++){
        int n2=n-n1;
        //cout<<sum[n1]<<" "<<sumi[n2]<<endl;
        ans=max(ans,sum[n1]+sumi[n2]);
    }
    cout<<ans;
    return 0;
}
/*
总结一下有原始代码以后有三个问题：
1.i和1再一次完美错过与搞混，while循环的条件中应当有非空判断，间接导致死循环！
2.忘记了优先队列取栈顶最大值应当在输入时取负
3.默认以为输入的顺序就是先进先出
·总结：过几天的考试，细节一定注意！！！for循环可以学会事先存好！！！一定事先想好可能的思路中的Bug与输入的特殊情况！！！务必读懂读透题目！！！学会自己测样例与查过！！！
*/