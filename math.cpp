LL Phi(LL n)
{
	LL ans=n;
	for(LL i=2;i*i<=n;++i)
	{
		if(n%i==0)
		{
			ans-=ans/i;
			while(n%i==0)	n/=i;
		}
	}
	if(n>1)	ans-=ans/n;
	return ans;
}

void exgcd(long long a,long long b){
	if(b==0){
		x=1; y=0;
		return;
	}
	exgcd(b,a%b);
	long long t=x;
	x=y; y=t-(a/b)*x;
}

vector<int> pri;
bool not_prime[N];
int phi[N];

void pre(int n) {
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!not_prime[i]) {
      pri.push_back(i);
      phi[i] = i - 1;
    }
    for (int pri_j : pri) {
      if (i * pri_j > n) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        phi[i * pri_j] = phi[i] * pri_j;
        break;
      }
      phi[i * pri_j] = phi[i] * phi[pri_j];
    }
  }
}

LL CRT(int k, LL* a, LL* r) {
  LL n = 1, ans = 0;
  for (int i = 1; i <= k; i++) n = n * r[i];
  for (int i = 1; i <= k; i++) {
    LL m = n / r[i], b, y;
    exgcd(m, r[i], b, y);  // b * m mod r[i] = 1
    ans = (ans + a[i] * m * b % n) % n;
  }
  return (ans % n + n) % n;
}
