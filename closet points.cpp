#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct node{
	__int128 x,y;
}a[N];
node b[N];int tot=0;
bool cmp1(node i,node j){
	return i.x<j.x;
}
bool cmp2(node i,node j){
	return i.y<j.y;
}
__int128 ans=2e18;
__int128 dist(node i,node j){return 1ll*(i.x-j.x)*(i.x-j.x)+1ll*(i.y-j.y)*(i.y-j.y);}
node t[N];
void merge(int l,int r){
	int mid=(l+r)/2;
	int i=l,j=mid+1,k=l;
	while(i<=mid && j<=r)
		if(a[i].y<a[j].y) t[k++]=a[i++];
		else t[k++]=a[j++];
	while(i<=mid) t[k++]=a[i++];
	while(j<=r) t[k++]=a[j++];
	for(i=l;i<=r;++i)
		a[i]=t[i];
}
void solve(int l,int r){
	if(l==r) return;
	if(l+1==r) return (void)(merge(l,r),ans=min(ans,dist(a[l],a[r])));
	int mid=(l+r)/2;
  __int128 X=a[mid].x;
	solve(l,mid);solve(mid+1,r);
	merge(l,r);
	tot=0;
	for(int i=l;i<=r;++i){
    __int128 d=a[i].x-X;
    if(d<0) d=-d;
		if((d<=ans)) b[++tot]=a[i];
  }

	for(int i=1;i<=tot;++i)
		for(int j=i-1;j>=1;--j)
			if((b[i].y-b[j].y)*(b[i].y-b[j].y)>ans) break;
			else ans=min(ans,dist(b[i],b[j]));
}
signed main(){
//	freopen("P1429_6.in","r",stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);
	int n;
	cin>>n;
	for(int i=1,x;i<=n;++i) cin>>x,a[i].x=x+a[i-1].x;
  for(int i=1,x;i<=n;++i) cin>>x,a[i].y=x+a[i-1].y;
  a[++n]={0,0};
	sort(a+1,a+n+1,cmp1);
	solve(1,n);
	long long all=ans;
  cout<<all<<"\n";
	return 0;
}
