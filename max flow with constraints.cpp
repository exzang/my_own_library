#include <bits/stdc++.h>
using namespace std;

inline int read(){
    int d=0,f=0;char ch=getchar();
    while (!isdigit(ch)) f|=(ch=='-'),ch=getchar();
    while (isdigit(ch)) d=d*10+ch-'0',ch=getchar();
    return f?-d:d;
}

const int N=1005,M=N+10005,inf=2e9+7;

int n,m,h[N],idx,w[N],S,T,s,t;

struct Edge{int t,c,ne;}e[M<<1];
inline void add(int a,int b,int c) {
    e[idx]={b,c,h[a]};h[a]=idx++;
    e[idx]={a,0,h[b]};h[b]=idx++;
}

int q[N],hh,tt,d[N],cur[N];

inline bool bfs(){
    memset(d,0,sizeof(int)*(n+2));
    hh=0,tt=-1,q[++tt]=S,d[S]=1;
    while (hh<=tt){
        int u=q[hh++];
        for (int i=h[u];~i;i=e[i].ne){
            int v=e[i].t;
            if (!d[v]&&e[i].c){
                d[v]=d[u]+1,q[++tt]=v;
                if (v==T) return true;
            }
        }
    }
    return false;
}

int dfs(int u,int mf){
    if (u==T) return mf;
    int sum=0;
    for (int &i=cur[u];~i;i=e[i].ne){
        int v=e[i].t;
        if (d[v]==d[u]+1&&e[i].c){
            int f=dfs(v,min(e[i].c,mf));
            sum+=f,mf-=f;
            e[i].c-=f,e[i^1].c+=f;
            if (!mf) break;
        }
    }
    if (!sum) d[u]=0;
    return sum;
}

inline int Dinic(){
    int flow=0;
    while (bfs()){
        memcpy(cur,h,sizeof(int)*(n+2));
        flow+=dfs(S,inf);
    }
    return flow;
}

signed main(){
    n=read(),m=read(),s=read(),t=read(),S=0,T=n+1;

    memset(h,-1,sizeof(int)*(n+2));

    for (int i=1;i<=m;i++){
        int u=read(),v=read(),l=read(),r=read();
        add(u,v,r-l);
        w[u]-=l,w[v]+=l;
    }

    int sum=0;
    for (int i=1;i<=n;i++)
        if (w[i]>0) add(S,i,w[i]),sum+=w[i];
        else add(i,T,-w[i]);
    
    add(t,s,inf);
    int res=Dinic();
    if (res<sum) puts("N");
    else {
        int res=e[idx-1].c;S=s,T=t;
        e[idx-1].c=e[idx-2].c=0;
        printf("%d\n",Dinic()+res);
    }
    return 0;
}
