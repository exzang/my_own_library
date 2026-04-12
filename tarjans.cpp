// 无向图 求图的割点 find cut vertices in undirected path
void dfs(int x){
	dfn[x]=low[x]=++tot;
	int len=e[x].size(),cnt=0;
	for(int i=0;i<len;++i)
	{
		if(!dfn[e[x][i]]){
			dfs(e[x][i]);
			low[x]=min(low[x],low[e[x][i]]);
			if(low[e[x][i]]>=dfn[x]){
				cnt++;
				if(x!=root || cnt>=2) flag[x]=1;
			}
		}
		else low[x]=min(low[x],dfn[e[x][i]]);
	}
}

// 求强连通分量 find strongly connected component in directed graph

void tarjan(int x){
	++tot;
	dfn[x]=low[x]=tot;
	S.push(x); inc[x]=1;
	int len=e[x].size();
	for(int i=0;i<len;++i)
		if(!dfn[e[x][i]])
		{
			tarjan(e[x][i]);
			low[x]=min(low[x],low[e[x][i]]);
		}
		else if(inc[e[x][i]]) low[x]=min(low[x],dfn[e[x][i]]);
	if(low[x]==dfn[x]){
		if(!S.empty()) ++cnt;
		while(!S.empty()){
			now=S.top(); S.pop();
			c[now]=cnt;
			w[cnt]+=a[now];
			inc[now]=0;
			if(now==x) break;		
		}
	}
}
