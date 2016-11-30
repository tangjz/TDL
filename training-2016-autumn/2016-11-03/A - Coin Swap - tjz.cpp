#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 501, INF = 0x3f3f3f3f;
int t, n, m, col[2][maxn], g[maxn][maxn], que[maxn], dis[maxn], L, R, lx[maxn], ly[maxn], match[maxn], slack[maxn];
vector<int> e[maxn];
bool sx[maxn], sy[maxn];
bool path(int u)
{
	sx[u] = 1;
	for(int v = 1; v <= n; ++v)
	{
		if(sy[v])
			continue;
		int dt = lx[u] + ly[v] - g[u][v];
		if(!dt)
		{
			sy[v] = 1;
			if(match[v] == -1 || path(match[v]))
			{
				match[v] = u;
				return 1;
			}
		}
		else if(slack[v] > dt)
			slack[v] = dt;
	}
	return 0;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
		while(m-- > 0)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i = 0; i < 2; ++i)
			for(int j = 1; j <= n; ++j)
				scanf("%d", col[i] + j);
		for(int i = 1; i <= n; ++i)
		{
			L = R = 0;
			memset(dis + 1, -1, n * sizeof(int));
			dis[i] = 0;
			que[R++] = i;
			while(L < R)
			{
				int u = que[L++];
				for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
				{
					int v = *it;
					if(dis[v] == -1)
					{
						dis[v] = dis[u] + 1;
						que[R++] = v;
					}
				}
			}
			for(int j = 1; j <= n; ++j)
				g[i][j] = col[0][i] == col[1][j] ? -dis[j] : -INF;
		}
		for(int i = 1; i <= n; ++i)
		{
			match[i] = -1;
			lx[i] = -INF;
			ly[i] = 0;
			for(int j = 1; j <= n; ++j)
				lx[i] = max(lx[i], g[i][j]);
		}
		for(int i = 1; i <= n; ++i)
		{
			memset(slack + 1, 0x3f, n * sizeof(int));
			while(1)
			{
				memset(sx + 1, 0, n * sizeof(bool));
				memset(sy + 1, 0, n * sizeof(bool));
				if(path(i))
					break;
				int dx = INF;
				for(int j = 1; j <= n; ++j)
					if(!sy[j] && dx > slack[j])
						dx = slack[j];
				for(int j = 1; j <= n; ++j)
				{
					if(sx[j])
						lx[j] -= dx;
					if(sy[j])
						ly[j] += dx;
					else
						slack[j] -= dx;
				}
			}
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			ans += g[match[i]][i];
		printf("%d\n", -ans >> 1);
	}
	return 0;
}
