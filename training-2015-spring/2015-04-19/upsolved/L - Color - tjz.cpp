#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 210, maxd = 7, maxN = 610, maxM = 3610, INF = 0x3f3f3f3f;
int t, n, f[4], d[4], typ[maxn], g[maxn][maxd], ans;
int N, M, pre[maxN], level[maxN], que[maxN], L, R, S, T;
struct Edge
{
	int nxt, v, f;
} e[maxM << 1];
void AddEdge(int u, int v, int f)
{
	e[M] = (Edge){pre[u], v, f};
	pre[u] = M++;
	e[M] = (Edge){pre[v], u, 0};
	pre[v] = M++;
}
bool bfs()
{
	L = R = 0;
	memset(level, 0, N * sizeof(int));
	level[S] = 1;
	que[R++] = S;
	while(L < R)
	{
		int &u = que[L++];
		for(int it = pre[u]; it != -1; it = e[it].nxt)
		{
			int &v = e[it].v, &w = e[it].f;
			if(w && !level[v])
			{
				level[v] = level[u] + 1;
				que[R++] = v;
			}
		}
	}
	return level[T];
}
int dfs(int u, int lim)
{
	if(u == T || !lim)
		return lim;
	int ret = 0;
	for(int it = pre[u]; it != -1; it = e[it].nxt)
	{
		int &v = e[it].v, &w = e[it].f, k;
		if(level[v] == level[u] + 1 && (k = dfs(v, min(lim - ret, w))))
		{
			ret += k;
			e[it].f -= k;
			e[it ^ 1].f += k;
		}
	}
	if(!ret)
		level[u] = -1;
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d", &n);
		for(int i = 0; i < 4; ++i)
			scanf("%d", f + i);
		for(int i = 0; i < 4; ++i)
			scanf("%d ", d + i);
		for(int i = 1; i <= n; ++i)
		{
			char tmp[30];
			gets(tmp);
			if(tmp[0] == 'Y')
			{
				typ[i] = 0;
				ans += f[1] + f[2] + d[1] + d[2];
			}
			else
			{
				typ[i] = 1;
				ans += f[0] + f[3] + d[0] + d[3];
			}
			g[i][0] = 0;
			for(int j = 1, k; tmp[j]; j = k)
			{
				for( ; tmp[j] == ' '; ++j);
				for(k = j + 1; tmp[k] >= '0' && tmp[k] <= '9'; ++k);
				char ch = tmp[k];
				tmp[k] = '\0';
				sscanf(tmp + j, "%d", g[i] + (++g[i][0]));
				tmp[k] = ch;
			}
		}
		N = n * 3 + 2;
		M = 0;
		S = 0;
		T = N - 1;
		memset(pre, -1, N * sizeof(int));
		for(int i = 1; i <= n; ++i)
			if(!typ[i])
			{
				AddEdge(S, i, f[2]);
				AddEdge(i, T, f[1]);
				AddEdge(S, n + i, d[2]);
				AddEdge(n + i, i, INF);
				for(int j = 1; j <= g[i][0]; ++j)
					if(typ[g[i][j]])
						AddEdge(n + i, g[i][j], INF);
				AddEdge(i, n + n + i, INF);
				for(int j = 1; j <= g[i][0]; ++j)
					if(typ[g[i][j]])
						AddEdge(g[i][j], n + n + i, INF);
				AddEdge(n + n + i, T, d[1]);
			}
			else
			{
				AddEdge(S, i, f[3]);
				AddEdge(i, T, f[0]);
				AddEdge(S, n + i, d[3]);
				AddEdge(n + i, i, INF);
				for(int j = 1; j <= g[i][0]; ++j)
					if(!typ[g[i][j]])
						AddEdge(n + i, g[i][j], INF);
				AddEdge(i, n + n + i, INF);
				for(int j = 1; j <= g[i][0]; ++j)
					if(!typ[g[i][j]])
						AddEdge(g[i][j], n + n + i, INF);
				AddEdge(n + n + i, T, d[0]);
			}
		int res = 0, tmp;
		while(bfs())
			while((tmp = dfs(S, INF)))
				res += tmp;
		printf("%d\n", ans - res);
	}
	return 0;
}
