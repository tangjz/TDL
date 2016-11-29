#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 55, maxm = 1001;
struct Edge
{
	int nxt, to, flow;
} e[maxm << 3];
int T, n, m, s, t, tot, lis[maxn], ans;
int que[maxn], l, r, level[maxn];
void addedge(int u, int v, int f)
{
	e[tot] = (Edge){lis[u], v, f};
	lis[u] = tot++;
	e[tot] = (Edge){lis[v], u, 0};
	lis[v] = tot++;
}
bool bfs()
{
	l = r = 0;
	memset(level, 0, sizeof level);
	level[s] = 1;
	que[r++] = s;
	while(l < r)
	{
		int u = que[l++];
		for(int it = lis[u]; it != -1; it = e[it].nxt)
		{
			int &v = e[it].to, &w = e[it].flow;
			if(w && !level[v])
			{
				level[v] = level[u] + 1;
				que[r++] = v;
			}
		}
	}
//	for(int i = 1; i <= n; ++i)
//		printf("%d\n", level[i]);
	return level[t] != 0;
}
int dfs(int u, int lim)
{
	if(u == t || !lim)
		return lim;
	int tmp = 0;
	for(int it = lis[u]; it != -1; it = e[it].nxt)
	{
		int &v = e[it].to, &w = e[it].flow, k;
		if(level[v] == level[u] + 1 && (k = dfs(v, min(lim - tmp, w))))
		{
			tmp += k;
			e[it].flow -= k;
			e[it ^ 1].flow += k;
		}
	}
	return tmp;
}
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		tot = ans = 0;
		memset(lis, -1, sizeof lis);
		scanf("%d%d%d%d", &n, &m, &s, &t);
		for(int i = 0; i < m; ++i)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			ans += w;
			addedge(u, v, w * maxm - 1);
			addedge(v, u, w * maxm - 1);
		}
		int flow = 0;
		while(bfs())
		{
			int tmp;
			while((tmp = dfs(s, 0x3f3f3f3f)))
				flow += tmp;
		}
		if(!flow)
			puts("Inf");
		else
		{
			int cnt = maxm - flow % maxm;
			int Flow = flow / maxm + 1;
			printf("%.2f\n", (double)(ans - Flow) / cnt);
		}
	}
	return 0;
}
