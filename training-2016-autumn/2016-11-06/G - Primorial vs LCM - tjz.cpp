#include <cmath>
#include <stdio.h>
typedef long long LL;
const int maxn = 10000001, mod = 1000000007;
int t, tot, prime[maxn], d[maxn], s[maxn];
LL n;
LL Pow(LL x, int k)
{
	LL ret = 1;
	for( ; k; k >>= 1, x = x * x)
		if(k & 1)
			ret = ret * x;
	return ret;
}
LL Root(LL x, int k)
{
	LL y = (LL)floor(exp(log(x) / k));
	for( ; Pow(y, k) > x; --y);
	for( ; exp(log(y + 1) * k) <= 1e15 && Pow(y + 1, k) <= x; ++y);
	return y;
}
int main()
{
	s[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		s[i] = s[i - 1];
		if(!d[i])
		{
			prime[tot++] = d[i] = i;
			s[i] = (LL)s[i - 1] * i % mod;
		}
		for(int j = 0, k = (maxn - 1) / i; prime[j] <= k; ++j)
		{
			d[i * prime[j]] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%lld", &n);
		int ans = 1;
		for(int i = 2; ; ++i)
		{
			LL cur = Root(n, i);
			if(cur == 1)
				break;
			ans = (LL)ans * s[(int)cur] % mod;
		}
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
