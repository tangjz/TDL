#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned int UL;
const int maxn = 101, maxd = 21, maxs = 11, maxo = 1 << 16;
int lbt[maxo], c[maxd][maxd];
struct Bitset
{
	UL data[4];
	void reset()
	{
		memset(data, 0, sizeof data);
	}
	void reset(int x)
	{
		data[x >> 5] ^= 1U << (x & 31);
	}
	void set(int x)
	{
		data[x >> 5] |= 1U << (x & 31);
	}
	int lowbit()
	{
		for(int i = 0; i < 4; ++i)
			if(data[i])
				return (i << 5) + (data[i] & 65535 ? lbt[data[i] & 65535] : 16 + lbt[data[i] >> 16]);
		return -1;
	}
	bool operator == (const Bitset &t) const
	{
		for(int i = 0; i < 4; ++i)
			if(data[i] != t.data[i])
				return 0;
		return 1;
	}
	Bitset operator & (const Bitset &t) const
	{
		Bitset ret = *this;
		for(int i = 0; i < 4; ++i)
			ret.data[i] &= t.data[i];
		return ret;
	}
} e[maxn], msk[maxs], tmp;
int t, n, m, s, ans;
int dfs(int dep, int need)
{
	if(need == 0)
		return 1;
	int cnt = 0;
	bool flag = 1;
	tmp = msk[dep];
	for(int u = tmp.lowbit(); u != -1; ++cnt, tmp.reset(u), u = tmp.lowbit())
		flag &= (msk[dep] & e[u]) == msk[dep];
	if(cnt < need)
		return 0;
	if(flag)
		return c[need][cnt];
	int ret = 0;
	for(int u = msk[dep].lowbit(); u != -1; msk[dep].reset(u), u = msk[dep].lowbit())
	{
		msk[dep + 1] = msk[dep] & e[u];
		ret += dfs(dep + 1, need - 1);
	}
	return ret;
}
int main()
{
	lbt[0] = -1;
	for(int i = 1; i < maxo; ++i)
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	for(int i = 0; i < maxd; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &s);
		msk[0].reset();
		for(int i = 1; i <= n; ++i)
		{
			e[i].reset();
			msk[0].set(i);
		}
		for(int i = 1; i <= m; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if(u > v)
				swap(u, v);
			e[u].set(v);
		}
		ans = dfs(0, s);
		printf("%d\n", ans);
	}
	return 0;
}
