#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int N = 1000010;

char s[N];
int n;
int m, p, rk[N * 2], oldrk[N], sa[N * 2], id[N], cnt[N];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  m = 128;

  for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
  for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

  for (int w = 1;; w <<= 1, m = p) {  // m = p 即为值域优化
    int cur = 0;
    for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
    for (int i = 1; i <= n; i++)
      if (sa[i] > w) id[++cur] = sa[i] - w;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) cnt[rk[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];

    p = 0;
    memcpy(oldrk, rk, sizeof(oldrk));
    for (int i = 1; i <= n; i++) {
      if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
          oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
        rk[sa[i]] = p;
      else
        rk[sa[i]] = ++p;
    }

    if (p == n) break;  // p = n 时无需再排序
  }


  for (i = 1, k = 0; i <= n; ++i) {
  if (rk[i] == 0) continue;
  if (k) --k;
  while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
  height[rk[i]] = k;
}
  // note that LCP(sa[i],sa[j]) = min(height[i+1...j])
  return 0;
}


struct SuffixArray{
	char s[N+7];
	int m,c[N+7],tp[N+7],rk[N+7],sa[N+7];
	int h[N+7],st[N+7][20];
	void csort(){
		for(int i=0;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[rk[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[rk[tp[i]]]--]=tp[i];
	}
	void build(){
		memset(c,0,sizeof c);
		memset(tp,0,sizeof tp);
		memset(rk,0,sizeof rk);
		memset(sa,0,sizeof sa);
		memset(h,0,sizeof h);
		memset(st,0,sizeof st);
		for(int i=1;i<=n;i++) rk[i]=s[i],tp[i]=i;
		m=128,csort();
		for(int w=1,p=1,i;p<n;w<<=1,m=p){
			for(p=0,i=n-w+1;i<=n;i++) tp[++p]=i;
			for(i=1;i<=n;i++)if(sa[i]>w) tp[++p]=sa[i]-w;
			csort(),swap(rk,tp),rk[sa[1]]=p=1;
			for(i=2;i<=n;rk[sa[i]]=p,i++)
				if(tp[sa[i]]!=tp[sa[i-1]]||tp[sa[i]+w]!=tp[sa[i-1]+w]) p++;
		}
		for(int i=1,j,k=0;i<=n;h[rk[i++]]=k)
			for(k=k?k-1:k,j=sa[rk[i]-1];s[i+k]==s[j+k];k++);
		for(int i=1;i<=n;i++) st[i][0]=h[i];
		for(int w=1;w<=18;w++)
			for(int i=1;i+(1<<w)-1<=n;i++)
				st[i][w]=min(st[i][w-1],st[i+(1<<(w-1))][w-1]);
	}
	int Lcp(int a,int b){
		int l=rk[a],r=rk[b];
		if(l>r) swap(l,r); l++;
		int k=log2(r-l+1);
		return min(st[l][k],st[r-(1<<k)+1][k]);
	}
}a,b;


struct treap {
	int ls[N],rs[N],s[N],top,fa[N];
	void build() {
		if(n==1) return root=2,void();
		ls[2]=n+1,rs[2]=n+2,fa[ls[2]]=fa[rs[2]]=root=s[++top]=2;
		rep(i,3,n) {
			while(top&&h[s[top]]>h[i]) top--;
			if(top) ls[i]=rs[s[top]],fa[rs[s[top]]]=i,rs[s[top]]=i,fa[i]=s[top];
			else ls[i]=root,fa[root]=i,root=i;
			rs[i]=n+i,fa[rs[i]]=i,s[++top]=i;
		}
		rep(i,2,n+n) val[i]=(i>n?n-sa[i-n]+1:h[i])-h[fa[i]];
	}
	void prep(int x) {
		lct.sm(x)=val[x],lct.top(x)=pre[x];
		if(x>n) return;
		pre[ls[x]]=pre[rs[x]]=pre[x]+val[x];
		lct.fa(ls[x])=lct.fa(rs[x])=x;
		prep(ls[x]),prep(rs[x]);
	}
} trp;
