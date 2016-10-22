#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 101, INF = 0x3f3f3f3f;
const LL INF2 = 0x3f3f3f3f3f3f3f3fLL;
int n, m, g[maxn][maxn], match[maxn];
LL lx[maxn], ly[maxn], ans;
bool impx[maxn], impy[maxn], sx[maxn], sy[maxn];
bool path(int u)
{
	sx[u] = 1;
	for(int v = 0; v < m; ++v)
	{
		if(sy[v] || lx[u] + ly[v] != g[u][v])
			continue;
		sy[v] = 1;
		if(match[v] == -1 || path(match[v]))
		{
			match[v] = u;
			return 1;
		}
	}
	return 0;
}
int main()
{
	int tp, vp, wp;
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		memset(impx, 0, sizeof impx);
		memset(impy, 0, sizeof impy);
		for(scanf("%d", &tp); tp--; )
		{
			scanf("%d", &vp);
			impx[--vp] = 1;
		}
		for(scanf("%d", &tp); tp--; )
		{
			scanf("%d", &vp);
			impy[--vp] = 1;
		}
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < m; ++j)
				g[i][j] = impx[i] || impy[j] ? -INF : 0;
			for(scanf("%d", &tp); tp--; )
			{
				scanf("%d%d", &vp, &wp);
				--vp;
				if(g[i][vp] < wp)
					g[i][vp] = wp;
			}
		}
		for( ; n < m; ++n)
			for(int i = 0; i < m; ++i)
				g[n][i] = impx[n] || impy[i] ? -INF : 0;
		for( ; m < n; ++m)
			for(int i = 0; i < n; ++i)
				g[i][m] = impx[i] || impy[m] ? -INF : 0;
		for(int i = 0; i < n; ++i)
		{
			lx[i] = -INF;
			for(int j = 0; j < m; ++j)
				lx[i] = max(lx[i], (LL)g[i][j]);
		}
		memset(ly, 0, sizeof ly);
		memset(match, -1, sizeof match);
		for(int i = 0; i < n; ++i)
			while(1)
			{
				memset(sx, 0, sizeof sx);
				memset(sy, 0, sizeof sy);
				if(path(i))
					break;
				LL dx = INF2;
				for(int j = 0; j < n; ++j)
				{
					if(!sx[j])
						continue;
					for(int k = 0; k < m; ++k)
						if(!sy[k] && dx > lx[j] + ly[k] - g[j][k])
							dx = lx[j] + ly[k] - g[j][k];
				}
				for(int j = 0; j < n; ++j)
					if(sx[j])
						lx[j] -= dx;
				for(int j = 0; j < m; ++j)
					if(sy[j])
						ly[j] += dx;
			}
		ans = 0;
		for(int i = 0; i < m; ++i)
			ans += g[match[i]][i];
		if(ans >= 0)
			printf("%lld\n", ans);
		else
			puts("-1");
	}
	return 0;
}
