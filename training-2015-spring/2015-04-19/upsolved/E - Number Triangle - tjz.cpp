#include <cstdio>
const int maxn = 2001, maxm = 2001001, mod = 1000000007;
typedef long long LL;
int t, n, fact[maxm], inv[maxm], f[maxn];
int C(int n, int m)
{
	return (LL)fact[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxm; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	inv[1] = 1;
	for(int i = 2; i < maxm; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	inv[0] = 1;
	for(int i = 2; i < maxm; ++i)
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
		f[i] = (LL)f[i - 1] * C(i * (i + 1) / 2 - 1, i - 1) % mod * fact[i] % mod;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
