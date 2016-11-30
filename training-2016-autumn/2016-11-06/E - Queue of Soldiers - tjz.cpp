#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001, maxm = 1030, mod = 1000000007, M = 1 << 15, M2 = 73741817;
const long double pi = acos(-1.0);
struct complex
{
	long double r, i;
	complex() {}
	complex(long double x, long double y) : r(x), i(y) {}
	friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
	friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
	friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
	complex conj() { return complex(r, -i); }
} X[maxm << 1], Y[maxm << 1];
int fact[maxn], iact[maxn];
int t, n, m, a[maxn], tot, que[maxn], cnt[maxm];
int f[2][maxm], g[maxm], cur, pre = 1;
void FFT(complex a[], int n, int flag)
{
	for(int i = 1, j = n >> 1, k; i < n - 1; ++i)
	{
		if(i < j)
			std::swap(a[i], a[j]);
		for(k = n >> 1; j >= k; k >>= 1)
			j -= k;
		if(j < k)
			j += k;
	}
	for(int i = 1; i < n; i <<= 1)
	{
		complex wn(cos(pi / i), flag * sin(pi / i));
		for(int j = 0; j < n; j += i << 1)
		{
			complex w(1, 0);
			for(int k = 0; k < i; ++k, w = w * wn)
			{
				complex t = w * a[j + k + i];
				a[j + k + i] = a[j + k] - t;
				a[j + k] = a[j + k] + t;
			}
		}
	}
	if(flag == -1)
		for(int i = 0; i < n; ++i)
			a[i].r /= n;
}
void polyMul(int f[], int g[], int h[])
{
	int len;
	for(len = 1; len < m << 1; len <<= 1);
	for(int i = 0; i < len; ++i)
		X[i] = i <= m ? complex(f[i] >> 15, g[i] >> 15) : complex(0, 0);
	FFT(X, len, 1);
	for(int i = 0; i < len; ++i)
	{
		int j = (len - i) & (len - 1);
		Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
	}
	FFT(Y, len, -1);
	for(int i = 0; i <= m; ++i)
		h[i] = (LL)(Y[i].r + 0.5) % mod * M2 % mod;
	for(int i = 0; i < len; ++i)
		X[i] = i <= m ? complex(f[i] & (M - 1), g[i] & (M - 1)) : complex(0, 0);
	FFT(X, len, 1);
	for(int i = 0; i < len; ++i)
	{
		int j = (len - i) & (len - 1);
		Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
	}
	FFT(Y, len, -1);
	for(int i = 0; i <= m; ++i)
		h[i] = (h[i] + (LL)(Y[i].r + 0.5)) % mod;
	for(int i = 0; i < len; ++i)
		X[i] = i <= m ? complex(f[i] >> 15, g[i] & (M - 1)) : complex(0, 0);
	FFT(X, len, 1);
	for(int i = 0; i < len; ++i)
	{
		int j = (len - i) & (len - 1);
		Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
	}
	FFT(Y, len, -1);
	for(int i = 0; i <= m; ++i)
		h[i] = (h[i] + ((LL)(Y[i].r + 0.5) << 15)) % mod;
	for(int i = 0; i < len; ++i)
		X[i] = i <= m ? complex(f[i] & (M - 1), g[i] >> 15) : complex(0, 0);
	FFT(X, len, 1);
	for(int i = 0; i < len; ++i)
	{
		int j = (len - i) & (len - 1);
		Y[i] = (X[i] * X[i] - (X[j] * X[j]).conj()) * complex(0, -0.25);
	}
	FFT(Y, len, -1);
	for(int i = 0; i <= m; ++i)
		h[i] = (h[i] + ((LL)(Y[i].r + 0.5) << 15)) % mod;
}
int C(int n, int m)
{
	return (LL)fact[n] * iact[m] % mod * iact[n - m] % mod;
}
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		memcpy(que, a, n * sizeof(int));
		sort(que, que + n);
		tot = unique(que, que + n) - que;
		memset(cnt, 0, tot * sizeof(int));
		for(int i = 0; i < n; ++i)
			++cnt[lower_bound(que, que + tot, a[i]) - que];
		memset(f[cur], 0, (m + 1) * sizeof(int));
		f[cur][0] = 1;
		for(int i = 0, c = 0; i < tot; c += cnt[i++])
		{
			pre ^= 1;
			cur ^= 1;
			g[0] = 1;
			for(int j = 1; j <= m; ++j)
				g[j] = j <= cnt[i] && c > 0 ? C(j + c - 1, j) : 0;
			polyMul(f[pre], g, f[cur]);
		}
		printf("Case %d: %d\n", Case, f[cur][m]);
	}
	return 0;
}
