#include<bits/stdc++.h>
using namespace std;
inline int rd(){
	int x=0;char ch=getchar();bool f=0;
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=1;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return f?-x:x;
}
const int N=2e5+5;
struct node{
	int x,y;
}a[N];
node b[N];int tot=0;
bool cmp1(node i,node j){
	return i.x<j.x;
}
bool cmp2(node i,node j){
	return i.y<j.y;
}
long long ans=1e18;
long long dist(node i,node j){return 1ll*(i.x-j.x)*(i.x-j.x)+1ll*(i.y-j.y)*(i.y-j.y);}
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
	int mid=(l+r)/2,X=a[mid].x;
	solve(l,mid);solve(mid+1,r);
	merge(l,r);
	tot=0;
	for(int i=l;i<=r;++i)
		if(abs(a[i].x-X)<=ans) b[++tot]=a[i];
	for(int i=1;i<=tot;++i)
		for(int j=i-1;j>=1;--j)
			if(1ll*(b[i].y-b[j].y)*(b[i].y-b[j].y)>ans) break;
			else ans=min(ans,dist(b[i],b[j]));
}
signed main(){
//	freopen("P1429_6.in","r",stdin);
	int n;
	n=rd();
	for(int i=1;i<=n;++i)
		a[i].x=rd(),a[i].y=rd();
	sort(a+1,a+n+1,cmp1);
	solve(1,n);
	//cout<<ans<<endl;
	printf("%.4lf",sqrt(ans));
	return 0;
}
