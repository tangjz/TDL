#include <stdio.h>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 501, maxm = 250001, maxk = 9, mod = 1000000007;
int c[maxm][maxk], cnt[maxn << 2 | 1];
int solve(int n, int m, int k) // n <= m
{
	assert(n <= m && m < maxn);
	//printf("solve (%d, %d, %d)\n", n, m, k);
	int ans = n * m * (LL)c[n * m][k] % mod;
	memset(cnt + 1, 0, (m << 2) * sizeof(int));
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			++cnt[n + m - 1 + std::min(i - 1, j - 1) + std::min(i - 1, m - j) + std::min(n - i, j - 1) + std::min(n - i, m - j)];
	for(int i = 1; i <= (m << 2); ++i)
	{
		if(!cnt[i])
			continue;
		//printf("%d : %d\n", i, cnt[i]);
		if((ans = (ans - (LL)cnt[i] * c[n * m - i][k]) % mod) < 0)
			ans += mod;
	}
	return ans;
}
int tot, mat[maxn][maxn];
inline int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int main()
{
	c[0][0] = 1;
	for(int i = 1; i < maxm; ++i)
	{
		c[i][0] = 1;
		for(int j = 1; j < maxk; ++j)
			if((c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod)
				c[i][j] -= mod;
	}
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	if(n > m)
		swap(n, m);
	int lim = k + 3, need = lim * lim;
	for(int i = 1; tot < maxn - 2; ++i)
		for(int j = 1; j <= i && tot < maxn - 2; ++j)
			if((j & 1) == (n & 1) && (i & 1) == (m & 1) && ((j << 1) < i) == ((n << 1) < m))
			{
				static int ipw[maxk + 3], jpw[maxk + 3];
				mat[tot][need] = solve(j, i, k);
				ipw[0] = jpw[0] = 1;
				for(int o = 1; o < lim; ++o)
				{
					ipw[o] = (LL)ipw[o - 1] * i % mod;
					jpw[o] = (LL)jpw[o - 1] * j % mod;
				}
				for(int p = 0, idx = 0; p < lim; ++p)
					for(int q = 0; q < lim; ++q, ++idx)
						mat[tot][idx] = (LL)jpw[p] * ipw[q] % mod;
				++tot;
			}
	for(int i = 0; i < need; ++i)
	{
		int k = -1;
		for(int j = i; j < tot; ++j)
			if(mat[j][i])
			{
				k = j;
				break;
			}
		if(k == -1)
		{
			printf("error %d %d\n", i / lim, i % lim);
		}
		assert(k != -1);
		if(i != k)
			for(int j = i; j <= need; ++j)
				swap(mat[i][j], mat[k][j]);
		int inver = mod_inv(mat[i][i]);
		if(inver > 1)
			for(int j = i; j <= need; ++j)
				mat[i][j] = (LL)mat[i][j] * inver % mod;
		for(int j = 0; j < tot; ++j)
		{
			if(i == j || !mat[j][i])
				continue;
			int sei = mat[j][i];
			for(k = i; k <= need; ++k)
				if((mat[j][k] = (mat[j][k] - (LL)mat[i][k] * sei) % mod) < 0)
					mat[j][k] += mod;
		}
	}
	static int npw[maxk + 3], mpw[maxk + 3];
	npw[0] = mpw[0] = 1;
	for(int o = 1; o < lim; ++o)
	{
		npw[o] = (LL)npw[o - 1] * n % mod;
		mpw[o] = (LL)mpw[o - 1] * m % mod;
	}
	int ans = 0;
	for(int p = 0, idx = 0; p < lim; ++p)
		for(int q = 0; q < lim; ++q, ++idx)
			ans = (ans + (LL)npw[p] * mpw[q] % mod * mat[idx][need]) % mod;
	printf("%d\n", ans);
	return 0;
}
