#include<bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

struct Edge{
	int u,v,w;
}e[500005];
struct T{
	int v,w;
};
bool cmp(Edge a,Edge b){
	return a.w>b.w;
}
int fa[500005],depth[500005];
int jump[500005][25],minn[500005][25];
bool vis[500005];
vector<T> g[500005];

int find(int u){
    return (fa[u]==u) ? u: (fa[u]=find(fa[u]));
}
void merge(int u,int v){
    int x=find(u);
    int y=find(v);
    if(x==y) return ;
    fa[x]=y;
//    cout<<x<<" "<<y<<" "<<fa[x]<<endl;
}
bool judge(int u,int v){
    int x=find(u);
    int y=find(v);
    return x==y;
}

void dfs(int u){
	if(g[u].size()==0) return ;
	for(int i=0;i<g[u].size();i++){
		vis[g[u][i].v]=1;
		if(g[u][i].v==fa[u]) continue;
		fa[g[u][i].v]=u;
		minn[g[u][i].v][0]=g[u][i].w;
//		cout<<minn[g[u][i].v][0]<<endl;
		depth[g[u][i].v]=depth[u]+1;
//		cout<<"1"<<endl;
		dfs(g[u][i].v);
	}
}

int MaxInpath(int x,int y){
    if(depth[x] < depth[y]) swap(x,y);
    int ans=INT_MAX/2;
    int len=depth[x]-depth[y];
    for(int k=0;k<=20;k++){
        if(len&(1<<k)){
            ans=min(ans,minn[x][k]);
            x=jump[x][k];
        }
    }
    if(x==y) return ans;
    for(int k=19;k>=0;k--){
        if(jump[x][k]!=jump[y][k]){
            ans=min(ans,minn[x][k]);
            ans=min(ans,minn[y][k]);
            x=jump[x][k];
            y=jump[y][k];
        }
    }
    ans=min(ans,minn[x][0]);
    ans=min(ans,minn[y][0]);
    return ans;
}

int main(){
//	freopen("6.in","r",stdin);
//	freopen("6.out","w",stdout);
	int n,m;
    cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	int cnt=0;
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
        if(judge(e[i].u,e[i].v)) continue;
        cnt++;
        g[e[i].u].push_back((T){e[i].v,e[i].w});
        g[e[i].v].push_back((T){e[i].u,e[i].w});
        merge(e[i].u,e[i].v);
//        cout<<e[i].u<<":"<<fa[e[i].u]<<endl;
        if(cnt==n-1) break;
    }
    /*
    for(int i=1;i<=n;i++){
        cout<<fa[i]<<" ";
    }
    cout<<endl;
    */
    memset(minn,0x3f,sizeof(minn));
	fa[1]=1;
	vis[1]=1;
	dfs(1);
	
	for(int i=2;i<=n;i++){
		if(vis[i]==0){
			fa[i]=i;
			vis[i]=1;
			dfs(i);
//			cout<<"123456789456123456774845746544987456467564654"<<endl;
		}
	}
	
	/*
    for(int i=1;i<=n;i++){
    	cout<<fa[i]<<endl;
	}
	*/
    for(int i=1;i<=n;i++){
        jump[i][0]=fa[i];
    }
    for(int k=1;k<=19;k++){
        for(int i=1;i<=n;i++){
            jump[i][k]=jump[jump[i][k-1]][k-1];
            minn[i][k] = min(minn[i][k-1],minn[jump[i][k-1]][k-1]);
//            cout<<minn[i][k]<<endl;
        }
    }
	int q;
//	cout<<minn[4][0]<<endl;
    cin>>q;
    for(int i=1;i<=q;i++){
        int a,b;
        cin>>a>>b;
        if(!judge(a,b)) cout<<"-1"<<endl;
        else
            cout<<MaxInpath(a,b)<<endl;
    }
	return 0;
}