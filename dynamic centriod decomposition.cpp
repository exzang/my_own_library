#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct edge{
	int nxt,to;
}e[N<<1];
int head[N],cnt;
void add(int x,int y){
	e[++cnt].to=y; e[cnt].nxt=head[x]; head[x]=cnt;
}
struct ST{
	int tot,dep[N],ver[N],val[N],f[N],p[N],ans[N][21],st[N][21];
	int ZQYAKHAOI[N];
	void dfs(int x){
		ver[++tot]=x; val[tot]=dep[x]; f[x]=tot; 
		for(register int i=head[x];i;i=e[i].nxt)
			if(!f[e[i].to]){
				dep[e[i].to]=dep[x]+1;
				dfs(e[i].to);
				ver[++tot]=x; val[tot]=dep[x];
			}
	}
	void solve(){
		dfs(1);
		p[0]=1;
		for(int i=1;i<=20;++i) p[i]=p[i-1]*2;
		for(int i=1;i<=tot;++i)
		ans[i][0]=ver[i],st[i][0]=val[i];
		for(int j=1;j<=20;++j)
			for(int i=1;i+p[j]-1<=tot;++i)
				if(st[i][j-1]>st[i+p[j-1]][j-1]) st[i][j]=st[i+p[j-1]][j-1],ans[i][j]=ans[i+p[j-1]][j-1];
				else st[i][j]=st[i][j-1],ans[i][j]=ans[i][j-1];
		ZQYAKHAOI[1]=0;
		for(int i=2;i<=tot;++i)
			ZQYAKHAOI[i]=ZQYAKHAOI[i>>1]+1;
	}
	int LCA(int x,int y){
		x=f[x]; y=f[y];
		if(x>y) swap(x,y);
		int k=ZQYAKHAOI[y-x+1];
		if(st[x][k]<st[y-p[k]+1][k]) return ans[x][k];
		else return ans[y-p[k]+1][k];
	}
	int dis(int x,int y){
		int k=LCA(x,y);
		return dep[x]+dep[y]-2*dep[k];
	}
}st;
int f[N],rt,mx[N],vis[N],sz[N];
void dfs(int x,int fath,int s){
	sz[x]=1; mx[x]=0;
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v] || v==fath) continue;
		dfs(v,x,s);
		sz[x]+=sz[v];
		mx[x]=max(mx[x],sz[v]);
	}
	mx[x]=max(mx[x],s-sz[x]);
	if(mx[rt]>mx[x]) rt=x;
}
struct bit{
	vector<int> s;
	void build(int x){
		s.resize(x,0);
	}
	void upt(int x,short c){
		++x;
		while(x<s.size()) s[x]+=c,x+=(x&-x);
	}
	int query(int x){
		++x; x=min(x,(int)s.size()-1);
		int res=0;
		while(x>0) res+=s[x],x-=(x&-x);
		return res;
	}
}T1[N],T2[N];
int fuck=0;
int n,v[N];
void solve(int x){
	int k;
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
		if(!vis[e[i].to]){
			int v=e[i].to;
			rt=0; mx[0]=N;
			dfs(v,x,sz[v]);
			T1[rt].build(sz[v]+2);
			T2[rt].build(sz[v]+2);
			k=rt,f[k]=x,solve(k);
		}
}
inline int dis(int x,int y){
	return st.dis(x,y);
}
void update(int x,int val){
	int k=x;
	for(;x;x=f[x]){
		T1[x].upt(dis(k,x),val-v[k]);
		if(f[x]) T2[x].upt(dis(k,f[x]),val-v[k]);
	}
	v[k]=val;
}
int Answer(int x,int k){
	int tmp=x,ans=0;
	for(int y=0;x;y=x,x=f[x]){
		ans+=T1[x].query(k-dis(x,tmp));
		if(y) ans-=T2[y].query(k-dis(x,tmp));
	}
	return ans;
}
inline int rd(){
	int x=0;char ch=getchar();bool f=0;
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=1;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return f?-x:x;
}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);putchar(x%10+'0');
}
void writeln(int x){write(x);puts("");}
int a[N];
signed main(){
	//freopen("P6329_1.in","r",stdin);
	//freopen("P6329_1.out","w",stdout);
	int q,u,v;
	n=rd(); q=rd();
	for(int i=1;i<=n;++i)
		a[i]=rd();
	for(int i=1;i<n;++i){
		u=rd(); v=rd();
		add(u,v);
		add(v,u);
	}
	st.solve();
	rt=0; mx[rt]=N;
	dfs(1,0,n);
	T1[rt].build(n+2);
	T2[rt].build(n+2);
	solve(rt);
	//cout<<fuck<<endl;
	for(int i=1;i<=n;++i)
		update(i,a[i]);
	int opt,ans=0;
	while(q--){
		//puts("TEST");
		opt=rd(); u=rd(); v=rd();
		u^=ans; v^=ans;
		if(opt==0) ans=Answer(u,v),writeln(ans);
		else update(u,v);
		//cout<<opt<<" "<<fuck<<endl;
	}
	return 0;
}
