#include<bits/stdc++.h>
using namespace std;
int lg2(int x) { return 31 - __builtin_clz(x); }

template <typename T>
class SparseTable {
  using VT = vector<T>;
  using VVT = vector<VT>;
  using func_type = function<T(const T &, const T &)>;

  VVT ST;

  static T default_func(const T &t1, const T &t2) { return min(t1, t2); }

  func_type op;

 public:
  SparseTable(const vector<T> &v, func_type _func = default_func) {
    op = _func;
    int n = v.size(), l = lg2(n);
    ST.assign(l + 1, VT(n, 1e9));
    for (int i = 0; i < n; ++i) {
      ST[0][i] = v[i];
    }
    for (int j = 1; j <= l; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        ST[j][i] = op(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T query(int l, int r) {
    int q = lg2(r - l + 1);
    return op(ST[q][l], ST[q][r - (1 << q) + 1]);
  }
};
const int N=1500005;
char s[N];
int tot, rk[N * 2], oldrk[N], sa[N * 2], cnt[N], height[N * 2];
void SA() {
  int n, m, p;
  n = m = p = 0;
  n = tot;
  m = 128;
  vector<int> id(N, 0);
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
  for (int i = 1, k = 0; i <= n; ++i) {
    if (rk[i] == 0) continue;
    if (k) --k;
    while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
    height[rk[i]] = k;
  }

}
string str[N];
int suf[N],id[N],len[N];
signed main(){
  int m,q;
  cin>>m>>q;
  for(int i=1;i<=m;++i){
    cin>>str[i];
    suf[i]=tot+1;
    for(int j=0;j<str[i].size();++j) s[++tot]=str[i][j];
    s[++tot]='#';
    len[i]=str[i].size();
  }
 // for(int i=1;i<=tot;++i)
  //  cout<<s[i];cout<<"\n";
  SA();

  vector<int> h(tot);
  for(int i=0;i<tot;++i) h[i]=height[i+1];
  SparseTable<int> st(h);
  auto query = [&](int l, int r) -> int {
    if(l>r) return 1e9;
    return st.query(l-1, r-1);
  };
  while(q--){
    int K,L;
    cin>>K>>L;
    for(int i=1;i<=K;++i)
      cin>>id[i];
    sort(id+1,id+K+1,[](int a,int b){
      return rk[suf[a]]<rk[suf[b]];
    });
    int ans=0;
    for(int i=1;i<=K;++i){
      if(i+L-1>K) continue;
      int l=1;
      int x=id[i],y=id[i-1];
      if(i>1) l=query(rk[suf[y]]+1,rk[suf[x]])+1;
      if(i+L<=K) l=max(l,query(rk[suf[x]]+1,rk[suf[id[i+L]]])+1);
      l=min(l,len[x]+1);
      int r=len[x];
      y=id[i+L-1];
      r=min(r,query(rk[suf[x]]+1,rk[suf[y]]));
      ans+=max(r-l+1,0);
    }
    cout<<ans<<"\n";
  }
  return 0;
}
