#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,SZ=1e6+5;
namespace AC{
	struct edge{
		int nxt,to;
	}e[N<<1];
	int amt,head[N],tr[N][26],tot,idx[N],fail[N],val[N],cnt[N],fd[N];
	queue<int> q;
	void add(int x,int y){
		e[++amt].to=y; e[amt].nxt=head[x]; head[x]=amt;
	}
	void insert(char *s,int c){
		int p=0;
		for(int i=0;s[i];++i){
			if(!tr[p][s[i]-'a']) tr[p][s[i]-'a']=++tot;
			p=tr[p][s[i]-'a'];
		}
		idx[p]=c; fd[c]=p;
	}
	void build(){
		for(int i=0;i<26;++i)
			if(tr[0][i]) q.push(tr[0][i]);
		while(!q.empty()){
			int u=q.front(); q.pop();
			for(int i=0;i<26;++i)
				if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
				else tr[u][i]=tr[fail[u]][i];
		}
	}
	void dfs(int u){
		for(int i=head[u];i;i=e[i].nxt)
		{
			dfs(e[i].to);
			val[u]+=val[e[i].to];
		}
	}
	void query(char *t){
		int p=0,res=0;
		for(int i=0;t[i];++i){
			p=tr[p][t[i]-'a'];
			val[p]++;
		}
		for(int i=1;i<=tot;++i)
			add(fail[i],i);
		dfs(0);
	}
}
char s[SZ],t[SZ];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%s",s),AC::insert(s,i);
	AC::build();
	scanf("%s",t);
	AC::query(t);
	for(int i=1;i<=n;++i)
		printf("%d\n",AC::val[AC::fd[i]]);
	return 0;
}
