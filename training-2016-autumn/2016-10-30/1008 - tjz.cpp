#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110, maxd = 6;
struct Trie
{
	int nxt[maxd], fail, idx;
} e[maxn];
int t, n, m, tot, que[maxn], L, R, sz;
long double f[maxn][maxn], ans[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		memset(e + (tot++), 0, sizeof e[0]);
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
		{
			int rt = 0;
			for(int j = 1; j <= m; ++j)
			{
				int x;
				scanf("%d", &x);
				if(!e[rt].nxt[--x])
				{
					e[rt].nxt[x] = tot;
					memset(e + (tot++), 0, sizeof e[0]);
				}
				rt = e[rt].nxt[x];
			}
			e[rt].idx = i;
		}
		L = R = 0;
		for(int i = 0; i < maxd; ++i)
			if(e[0].nxt[i])
				que[R++] = e[0].nxt[i];
		for( ; L < R; ++L)
		{
			int u = que[L];
			for(int i = 0; i < maxd; ++i)
				if(e[u].nxt[i])
				{
					int v = e[u].nxt[i], w = e[u].fail;
					que[R++] = v;
					for( ; w && !e[w].nxt[i]; w = e[w].fail);
					if(e[w].nxt[i])
						w = e[w].nxt[i];
					e[v].fail = w;
				}
		}
		sz = 0;
		for(int i = 0; i < tot; ++i)
		{
			if(e[i].idx)
				continue;
			for(int j = 0; j < tot; ++j)
				f[sz][j] = 0;
			f[sz][i] += (long double)maxd;
			for(int j = 0; j < maxd; ++j)
			{
				int u = i;
				for( ; u && !e[u].nxt[j]; u = e[u].fail);
				if(e[u].nxt[j])
					u = e[u].nxt[j];
				f[sz][u] -= (long double)1;
			}
			++sz;
		}
		R = 0;
		for(int i = 0; i < tot; ++i)
		{
			if(e[i].idx)
				continue;
			int k = R;
			for(int j = R + 1; j < sz; ++j)
				if(fabs(f[k][i]) < fabs(f[j][i]))
					k = j;
			for(int j = 0; j < tot; ++j)
				swap(f[R][j], f[k][j]);
			for(int j = 0; j < sz; ++j)
			{
				if(R == j)
					continue;
				long double sei = f[j][i] / f[R][i];
				for(int k = 0; k < tot; ++k)
					f[j][k] -= sei * f[R][k];
			}
			++R;
		}
		for(int i = 0; i < tot; ++i)
			if(e[i].idx)
				ans[e[i].idx] = -f[0][i] / f[0][0];
		for(int i = 1; i <= n; ++i)
			printf("%.6f%c", (double)ans[i], " \n"[i == n]);
	}
	return 0;
}
/*
10 10
6 3 2 5 1 3 6 3 1 3
1 6 3 6 3 6 1 6 4 2
1 1 1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 2 2 2
3 3 3 3 3 3 3 3 3 3
4 4 4 4 4 4 4 4 4 4
5 5 5 5 5 5 5 5 5 5
6 6 6 6 6 6 6 6 6 6
1 2 3 4 5 6 1 2 3 4
5 6 1 2 3 4 5 6 1 2
*/
