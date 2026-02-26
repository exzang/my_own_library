#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
struct edge
{
	int next,to,val;
}e[maxn];
int flow,cnt=-1,head[maxn],cur[maxn],dist[maxn],hash[maxn],last[maxn],n;
void add(int x,int y,int z)
{
	e[++cnt].to=y; e[cnt].val=z; e[cnt].next=head[x]; head[x]=cnt;
}
void bfs(int t)
{
	queue<int> q;
	q.push(t);
	for(int i=1;i<=n;++i)
		dist[i]=n;
	for(int i=1;i<=n;++i)
		cur[i]=head[i];
	dist[t]=0;
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		for(int i=head[now];i!=-1;i=e[i].next)
		{
//			cout<<now<<" "<<e[i].to<<" "<<i<<" "<<head[now]<<" "<<e[i].next<<" "<<endl;
			if(dist[e[i].to]==n && e[i^1].val)
				dist[e[i].to]=dist[now]+1,q.push(e[i].to);			
		}

	}
	for(int i=1;i<=n;++i)
		hash[dist[i]]++;
}
int maxflow(int s,int t)
{
	int ans=0x3f3f3f3f,now=t;
	while(now!=s)
	{
		ans=min(ans,e[last[now]].val);
		now=e[last[now]^1].to;
	}
	now=t;
	while(now!=s)
	{
		e[last[now]].val-=ans;
		e[last[now]^1].val+=ans;
		now=e[last[now]^1].to;
	}
	return ans;
}
void isap(int s,int t)
{
	int now=s;
	bfs(t);
	while(dist[s]<n)
	{
//		cout<<now<<endl;
		if(now==t)
		{
			flow+=maxflow(s,t);
			now=s;
		}
		int flag=0;
		for(int i=cur[now];i!=-1;i=e[i].next)
			if(e[i].val>0 && dist[now]==dist[e[i].to]+1)
			{
//				cout<<now<<" "<<e[i].to<<" "<<i<<" "<<e[i].next<<" "<<e[i].val<<endl;
				flag=1;
				last[e[i].to]=i;
				cur[now]=i;
				now=e[i].to;
				break;
			}
	//	if(now==3) break;
		if(!flag)
		{
			int minn=n-1;
			for(int i=head[now];i!=-1;i=e[i].next)
				if(e[i].val) minn=min(minn,dist[e[i].to]);
			hash[dist[now]]--;
			if(hash[dist[now]]==0) break;
			dist[now]=minn+1;
			cur[now]=head[now];
			hash[dist[now]]++;
			if(now!=s) now=e[last[now]^1].to;
		}
	}
}
int main()
{
	memset(head,-1,sizeof(head));
	int m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;++i)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z); add(y,x,0);
	}
	isap(s,t);
	cout<<flow;
	return 0;
}