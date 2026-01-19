const int SZ=5e5+5;
int tot,lc[SZ],rc[SZ],sz[SZ],rd[SZ],v[SZ],rt[2];
inline void update(int x){
	sz[x]=sz[lc[x]]+sz[rc[x]]+1;
}
inline void newnode(int &p,int val){
	p=++tot; rd[p]=rand(); v[p]=val; sz[p]=1;
}
inline void split(int now,int val,int &x,int &y){
	if(!now){
		x=y=0; return;
	}
	if(v[now]<=val){
		x=now;
		split(rc[now],val,rc[x],y);
	}
	else{
		y=now;
		split(lc[now],val,x,lc[y]);
	}
	update(now);
}
int merge(int a,int b){
	if(!a || !b) return a+b;
	if(rd[a]>rd[b]){
		rc[a]=merge(rc[a],b);
		update(a);
		return a;
	}
	else{	
		lc[b]=merge(a,lc[b]);
		update(b);
		return b;
	}
}
int x,y,z;
void Ins(int &p,int val){
	split(p,val,x,y);
	newnode(z,val);
	p=merge(merge(x,z),y);
}
void Del(int &p,int val){
	split(p,val,x,z);
	split(x,val-1,x,y);
	y=merge(lc[y],rc[y]);
	p=merge(merge(x,y),z);
}
int ans;
inline void Kth(int &p,int val){
	split(p,val-1,x,y);
	ans=sz[x]+1;
	p=merge(x,y);
	return;
} 
int Val(int p,int k){
	if(k==sz[lc[p]]+1) return v[p];
	if(k<=sz[lc[p]]) Val(lc[p],k);
	else Val(rc[p],k-sz[lc[p]]-1);
}
inline void Pre(int &p,int val){
	split(p,val-1,x,y);
	ans=Val(x,sz[x]);
	p=merge(x,y);
	return;
}
inline void Nxt(int &p,int val){
	split(p,val,x,y);
	ans=Val(y,1);
	p=merge(x,y);
	return;
}
