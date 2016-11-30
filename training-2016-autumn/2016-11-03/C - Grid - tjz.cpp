#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2510, maxm = maxn << 2, INF = 0x3f3f3f3f;
int t, n, m, a[maxn], N, M, S, T, lnk[maxn], level[maxn], que[maxn], L, R;
struct Edge
{
	int nxt, v, f;
} e[maxm << 1];
void addEdge(int u, int v, int c)
{
	e[M] = (Edge){lnk[u], v, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs()
{
	L = R = 0;
	memset(level, 0, N * sizeof(int));
	level[S] = 1;
	que[R++] = S;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].f && !level[e[it].v])
			{
				level[e[it].v] = level[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return level[T];
}
int dfs(int u, int lim)
{
	if(u == T || !lim)
		return lim;
	int ret = 0;
	for(int it = lnk[u], tmp; it != -1; it = e[it].nxt)
		if(e[it].f && level[e[it].v] == level[u] + 1
		&& (tmp = dfs(e[it].v, std::min(e[it].f, lim - ret))))
		{
			e[it].f -= tmp;
			e[it ^ 1].f += tmp;
			ret += tmp;
		}
	if(!ret)
		level[u] = 0;
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		N = n * m + 2;
		M = 0;
		S = N - 2;
		T = N - 1;
		memset(lnk, -1, N * sizeof(int));
		int sum = 0;
		for(int i = 0, idx = 0; i < n; ++i)
			for(int j = 0; j < m; ++j, ++idx)
			{
				scanf("%d", a + idx);
				sum += a[idx];
				if((i & 1) == (j & 1))
				{
					addEdge(S, idx, a[idx]);
					if(i > 0)
						addEdge(idx, idx - m, min(a[idx - m], a[idx]));
					if(j > 0)
						addEdge(idx, idx - 1, min(a[idx - 1], a[idx]));
				}
				else
				{
					addEdge(idx, T, a[idx]);
					if(i > 0)
						addEdge(idx - m, idx, min(a[idx - m], a[idx]));
					if(j > 0)
						addEdge(idx - 1, idx, min(a[idx - 1], a[idx]));
				}
			}
		int flow = 0;
		while(bfs())
			for(int tmp; (tmp = dfs(S, maxn)); flow += tmp);
		printf("%d\n", sum - flow);
	}
	return 0;
}
